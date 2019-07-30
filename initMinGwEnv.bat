@echo.
@set MINGW=C:/MinGW
@echo Setting up environment for using GCC from %MINGW%
@set PATH=%MINGW%/bin;%PATH%
@set INCLUDE=%MINGW%/include
@set LIBS=%MINGW%/lib
@set make=mingw32-make.exe
@set GCC=mingw32-gcc.exe
@set GXX=mingw32-g++.exe
@set RCC=windres
@set RM=del /q /f
@set MKDIR=mkdir
@set RMDIR=rmdir /s /q
@set MV=move /y
@set CP=copy /y
@set PWD=%cd%
@set LSF=dir /b
