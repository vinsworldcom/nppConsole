# Microsoft Developer Studio Project File - Name="nppConsole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=nppConsole - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nppConsole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nppConsole.mak" CFG="nppConsole - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nppConsole - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "nppConsole - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "nppConsole - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f nppConsole.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "nppConsole.exe"
# PROP BASE Bsc_Name "nppConsole.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "mk.bat"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "NppConsole.dll"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "nppConsole - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f nppConsole.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "nppConsole.exe"
# PROP BASE Bsc_Name "nppConsole.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "mk.bat log=yes"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "NppConsole.dll"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "nppConsole - Win32 Release"
# Name "nppConsole - Win32 Debug"

!IF  "$(CFG)" == "nppConsole - Win32 Release"

!ELSEIF  "$(CFG)" == "nppConsole - Win32 Debug"

!ENDIF 

# Begin Group "NppCommon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\NppCommon\Docking.h
# End Source File
# Begin Source File

SOURCE=..\NppCommon\Notepad_plus_msgs.h
# End Source File
# Begin Source File

SOURCE=..\NppCommon\Notepad_plus_rc.h
# End Source File
# Begin Source File

SOURCE=..\NppCommon\PluginInterface.h
# End Source File
# Begin Source File

SOURCE=..\NppCommon\Scintilla.h
# End Source File
# End Group
# Begin Group "make"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\makefile
# End Source File
# Begin Source File

SOURCE=.\mk.bat
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter "hxx"
# Begin Source File

SOURCE=..\include\resources.hxx
# End Source File
# Begin Source File

SOURCE=..\include\staticWnd.hxx
# End Source File
# End Group
# Begin Group "source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\main.cxx
# End Source File
# Begin Source File

SOURCE=..\source\staticWnd.cxx
# End Source File
# End Group
# Begin Group "resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\resources\NppConsole.ico
# End Source File
# Begin Source File

SOURCE=..\resources\NppConsole.manifest
# End Source File
# Begin Source File

SOURCE=..\resources\resources.rc
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\singl.hxx
# End Source File
# Begin Source File

SOURCE=..\..\Common\std.hxx
# End Source File
# End Group
# End Target
# End Project
