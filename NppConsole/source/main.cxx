/*
This file is part of Notepad++ console plugin.
Copyright ©2011 Mykhajlo Pobojnyj <mpoboyny@web.de>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

// main.cxx

#include "staticWnd.hxx"
#include "resources.hxx"


#define PLG_FUNCS_COUNT 4

HANDLE			g_hModule=NULL;
TCHAR			g_plgName[]=_T("NppConsole");
unsigned		g_showWndInd=0;
FuncItem		g_funcItem[PLG_FUNCS_COUNT]={0};
NppData			g_nppData={0};
tTbData			g_tbData = {0};

CStaticWnd		g_staticWnd;
TCHAR			g_savedCmd[MAX_PATH]={0};
TCHAR			g_savedLine[MAX_PATH]={0};
int				g_ctrlCaction = CStaticWnd::CTRL_C_IGNORE;

toolbarIcons	g_ToolBar={0};

extern "C" __declspec(dllexport) 
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  reasonForCall, LPVOID lpReserved )
{
	g_hModule = hModule;
	switch (reasonForCall) {
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_PROCESS_DETACH:
			if (g_ToolBar.hToolbarBmp) ::DeleteObject(g_ToolBar.hToolbarBmp);
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return TRUE;
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, 
							WPARAM wParam, LPARAM lParam)
{
	static LPCTSTR aboutText=_T("NppConsole is a workaround for windows console.\r\n")
		_T("After double click in the console window, it will activate the document")
		_T(" with the name found\r\nin the clicked line.\r\n")
		_T("The string after command line in the form ${hier are the parametrs}, will as parametrs\r\nfor command line interpreted.\r\n")
		_T("You can specify a pattern for line number to search after the file name. String ${LINE}\r\nis placeholder for found line number.")
		_T("\r\n\r\nWith best regards, M.Pobojnyj (mpoboyny@web.de)\r\n");
	static int xScreen=GetSystemMetrics(SM_CXSCREEN);
	static int yScreen=GetSystemMetrics(SM_CYSCREEN);

	switch (uMsg) {
        case WM_INITDIALOG :
		{
			HWND aboutWnd = GetDlgItem(hwndDlg, IDC_EDIT_ABOUT);
			IFR(!aboutWnd, TRUE);
			IFR(!SetWindowText(aboutWnd, aboutText), TRUE);
			SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_CMD), g_savedCmd);
			if (_tcslen(g_savedLine)) {
				SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_LINE), g_savedLine);
			}
			RECT wr={0};
			::GetWindowRect(hwndDlg, &wr);
			long w=wr.right-wr.left, h=wr.bottom-wr.top;
			::MoveWindow(hwndDlg, (xScreen-w)/2, (yScreen-h)/2, w, h, FALSE);
			HICON hIcon=(HICON) LoadImage((HINSTANCE)g_hModule, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, LR_SHARED);
			::SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			if (g_ctrlCaction == CStaticWnd::CTRL_C_IGNORE) {
				CheckDlgButton(hwndDlg, IDC_RADIO_IGN, BST_CHECKED);
			}
			else if (g_ctrlCaction == CStaticWnd::CTRL_C_PROCESS) {
				CheckDlgButton(hwndDlg, IDC_RADIO_PROCESS, BST_CHECKED);
			}
			else {
				CheckDlgButton(hwndDlg, IDC_RADIO_RESTR, BST_CHECKED);
			}
		}
			return TRUE;
		case WM_COMMAND : 
			switch (wParam) {
				case IDC_BUTTON_APPLY:
				{
					HKEY conKey=NULL;
					DWORD dispos=0;
					TCHAR cmd[MAX_PATH]={0};
					int cc=GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_LINE), cmd, MAX_PATH);
					IFR(ERROR_SUCCESS!=RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\NppConsole"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &conKey, &dispos), TRUE);
					if (ERROR_SUCCESS==RegSetValueEx(conKey, _T("LinePattern"), 0, REG_SZ, (LPBYTE)cmd, _tcslen(cmd)*sizeof(TCHAR))) {
						if (cc>0) memcpy(g_savedLine, cmd, MAX_PATH*sizeof(TCHAR));
						else memset(g_savedLine, 0, MAX_PATH*sizeof(TCHAR));
					}
					memset(cmd, 0, MAX_PATH*sizeof(TCHAR));
					cc=GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_CMD), cmd, MAX_PATH);
					if (ERROR_SUCCESS==RegSetValueEx(conKey, NULL, 0, REG_SZ, (LPBYTE)cmd, _tcslen(cmd)*sizeof(TCHAR))) {
						if (cc>0) memcpy(g_savedCmd, cmd, MAX_PATH*sizeof(TCHAR));
						else memset(g_savedCmd, 0, MAX_PATH*sizeof(TCHAR));
					}
					SLog("g_savedCmd: "<<g_savedCmd);
					SLog("g_savedLine: "<<g_savedLine);
					if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO_IGN)) {
						g_ctrlCaction = CStaticWnd::CTRL_C_IGNORE;
					}
					else if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO_PROCESS)) {
						g_ctrlCaction = CStaticWnd::CTRL_C_PROCESS;
					}
					else {
						g_ctrlCaction = CStaticWnd::CTRL_C_RECREATE;
					}
					if (ERROR_SUCCESS!=RegSetValueEx(conKey, _T("CtrlCAction"), 0, REG_DWORD, (LPBYTE)&g_ctrlCaction, sizeof(g_ctrlCaction))) {
						g_ctrlCaction = CStaticWnd::CTRL_C_IGNORE;
					}
					g_staticWnd.SetCtrlCAction(g_ctrlCaction);
					RegCloseKey(conKey);
					IFR(!g_staticWnd.Restart(g_savedCmd, g_savedLine), TRUE);
				}
					return TRUE;
				case IDOK :
				case IDCANCEL :
					::EndDialog(hwndDlg, IDOK);
					return TRUE;
				default:
					break;
			}
	}
	return FALSE;
}

void menuRestart()
{
    g_staticWnd.Restart(g_savedCmd, g_savedLine);
}

void AboutPlugin()
{
	DialogBoxParam((HINSTANCE)g_hModule,  MAKEINTRESOURCE(IDD_DIALOG_ABOUT), 
				g_nppData._nppHandle, DialogProc, 0);
}

void ShowPlugin()
{
	static bool wndFlag=false;
	IFV(!g_nppData._nppHandle);
	HMENU hMenu = ::GetMenu(g_nppData._nppHandle);
	UINT state = ::GetMenuState(hMenu, g_funcItem[g_showWndInd]._cmdID, MF_BYCOMMAND);
	if (state & MF_CHECKED) {
		g_staticWnd.Hide();
	}
	else {
		if (!wndFlag) {
			::SendMessage(g_nppData._nppHandle, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&g_tbData);
			wndFlag=true;
			
		}
		g_staticWnd.Show();
	}
	::SendMessage(g_nppData._nppHandle, NPPM_SETMENUITEMCHECK, g_funcItem[g_showWndInd]._cmdID, !(state&MF_CHECKED));
}

extern "C" __declspec(dllexport) 
void setInfo(NppData nppData)
{
	SLog(__FUNCTION__);
	char modName[MAX_PATH] = {0};
	g_nppData=nppData;
	HKEY conKey=NULL;
	TCHAR cmd[MAX_PATH]={0}, sysDir[MAX_PATH]={0};
	DWORD dispos=0, pdwType=0, pcbData=MAX_PATH*sizeof(TCHAR);
	IFV(ERROR_SUCCESS!=RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\NppConsole"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &conKey, &dispos));
	if (ERROR_SUCCESS!=RegQueryValueEx(conKey, NULL, 0, &pdwType, (LPBYTE)cmd, &pcbData)) {
		if (GetSystemDirectory(sysDir,MAX_PATH) && 0<_stprintf(cmd, _T("%s\\cmd.exe"), sysDir)) {
			RegSetValueEx(conKey, NULL, 0, REG_SZ, (LPBYTE)cmd, _tcslen(cmd)*sizeof(TCHAR));
		}
	}
	::memcpy(g_savedCmd, cmd, pcbData);
	pcbData=MAX_PATH*sizeof(TCHAR);
	if (ERROR_SUCCESS==RegQueryValueEx(conKey, _T("LinePattern"), 0, &pdwType, (LPBYTE)cmd, &pcbData)) {
		::memcpy(g_savedLine, cmd, pcbData);
	}
	pcbData = sizeof(g_ctrlCaction);
	pdwType = REG_DWORD;
	RegQueryValueEx(conKey, _T("CtrlCAction"), 0, &pdwType, (LPBYTE)&g_ctrlCaction, &pcbData);
	g_staticWnd.SetCtrlCAction(g_ctrlCaction);
	g_tbData.hClient=g_staticWnd.Create(g_nppData._nppHandle, g_savedCmd, g_savedLine);
	if (!g_tbData.hClient) {
		memset(cmd, 0, MAX_PATH*sizeof(TCHAR));
		if (GetSystemDirectory(sysDir,MAX_PATH) && 0<_stprintf(cmd, _T("%s\\cmd.exe"), sysDir)) {
			::memcpy(g_savedCmd, cmd, MAX_PATH*sizeof(TCHAR));
			g_tbData.hClient=g_staticWnd.Create(g_nppData._nppHandle, g_savedCmd, g_savedLine);
			RegSetValueEx(conKey, NULL, 0, REG_SZ, (LPBYTE)g_savedCmd, _tcslen(g_savedCmd)*sizeof(TCHAR));
		}
	}
	IFV(ERROR_SUCCESS!=RegCloseKey(conKey));
	IFV(!g_tbData.hClient);
	g_tbData.uMask = DWS_DF_CONT_BOTTOM | DWS_ICONTAB;
	::GetModuleFileNameA((HINSTANCE)g_hModule, modName, MAX_PATH);
	g_tbData.pszModuleName = modName;
    g_tbData.dlgID = g_showWndInd;
	g_tbData.pszName=g_plgName;	
	g_tbData.hIconTab = ( HICON )::LoadImage( (HINSTANCE)g_hModule,
		MAKEINTRESOURCE( IDI_APPICON ), IMAGE_ICON, 0, 0,
		LR_LOADMAP3DCOLORS | LR_LOADTRANSPARENT );

}

extern "C" __declspec(dllexport) 
const TCHAR * getName()
{
	return g_plgName;
}

extern "C" __declspec(dllexport) 
FuncItem * getFuncsArray(int *count)
{
	g_funcItem[2]._pFunc=menuRestart;
	_tcscpy(g_funcItem[2]._itemName, _T("Restart Console"));
	g_funcItem[2]._pShKey=NULL;

	g_funcItem[3]._pFunc=AboutPlugin;
	_tcscpy(g_funcItem[3]._itemName, _T("About..."));
	g_funcItem[3]._pShKey=NULL;

	g_funcItem[g_showWndInd]._pFunc=ShowPlugin;
	_tcscpy(g_funcItem[g_showWndInd]._itemName, _T("Show NppConsole"));
	g_funcItem[g_showWndInd]._pShKey=NULL;

	*count=PLG_FUNCS_COUNT;
	return g_funcItem;
}

extern "C" __declspec(dllexport) 
void beNotified(SCNotification *notifyCode)
{
	if (notifyCode->nmhdr.hwndFrom == g_nppData._nppHandle) {
		if (notifyCode->nmhdr.code == NPPN_TBMODIFICATION) {
			g_ToolBar.hToolbarBmp = (HBITMAP)::LoadImage((HINSTANCE)g_hModule, MAKEINTRESOURCE(IDB_TLB_IMG), IMAGE_BITMAP, 0, 0, (LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS));
			IFV(!g_ToolBar.hToolbarBmp);
			::SendMessage(g_nppData._nppHandle, NPPM_ADDTOOLBARICON, (WPARAM)g_funcItem[g_showWndInd]._cmdID, (LPARAM)&g_ToolBar);
		}
	}

}

extern "C" __declspec(dllexport) 
LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) 
BOOL isUnicode()
{
	return TRUE;
}
#endif //UNICODE
