@echo off
Set "Name=cmake"

Title Downloading Cmake
Mode con cols=80 lines=3 & color 9E
echo(
echo     Please wait a while ! downloading "Cmake" is in progress ...

Set "URL=https://cmake.org/files/v3.9/cmake-3.9.4.zip"

Set "MyDownload_Folder=%homepath%\MyDownload"

If Not Exist "%MyDownload_Folder%" MD "%MyDownload_Folder%"
Set "Setup_File=%MyDownload_Folder%\cmake-3.9.4.zip"

Call :Download "%URL%" "%Setup_File%"

set PATH=%PATH%;%cd%\7-Zip
7z e "%Setup_File%" -o"%cd%\..\lib_windows\%Name%" -aoa

Call :Clean %MyDownLoad_Folder%
Exit

::*********************************************************************************
:Download <url> <File>
Powershell.exe -command "(New-Object System.Net.WebClient).DownloadFile('%1','%2')"
exit /b
::*********************************************************************************
:Clean <Folder_Setup>
RD "%~1" /S /Q >nul
exit \b
::*********************************************************************************