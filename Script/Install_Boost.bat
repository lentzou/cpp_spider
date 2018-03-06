@echo off
Set "Name=boost"

Set "URL=https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.zip"

Set "MyDownload_Folder=%homepath%\MyDownload"

If Not Exist "%MyDownload_Folder%" MD "%MyDownload_Folder%"
Set "Setup_File=%MyDownload_Folder%\boost_1_65_1.zip"

Title Downloading Boost
Mode con cols=80 lines=3 & color 9E
echo(
echo     Please wait a while ! downloading "Boost" is in progress ...

Call :Download "%URL%" "%Setup_File%"

::set PATH=%PATH%;%cd%\7-Zip
::7z e "%Setup_File%" -o"%cd%\..\lib_windows\%Name%" -aoa

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
:Install_Silently <Setup_File> <Log>
msiexec.exe /i "%~1" /qn /L "%~2"
exit /b
::*********************************************************************************