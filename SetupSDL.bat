:: 
:: This batch script will automatically download and extract all the SDL2 development libraries
:: and place them in a single folder.
:: it was made for convenience sake and can be easily modified to download different versions
:: of the libraries.
:: Needs to be executed as administrator.
::
:: Won't work on Windows versions prior to Windows 10 build 17063 from the lack of the "tar" command.
::

@echo off
::Install directory
set "installdir=C:"
::Libraries type ("mingw" or "VC")
set "sdltype=mingw"
::Base library version
set "sdlbaseversion=2.26.4" 
::Image library version
set "sdlimageversion=2.6.3"
::Mixer library version
set "sdlmixerversion=2.6.3"
::TTF library version
set "sdlttfversion=2.20.2"


::Checks admin privileges
fsutil dirty query %systemdrive% >nul
if %errorlevel% NEQ 0 (
	echo This script needs to be run with administrator privileges to execute correctly.
	pause
	exit /b 1
)
 
::Download and extract SDL
echo [Downloading SDL2]
set "sdlbasename=SDL2-devel-%sdlbaseversion%-%sdltype%"
curl -L "https://github.com/libsdl-org/SDL/releases/download/release-%sdlbaseversion%/%sdlbasename%.zip" --output %installdir%\%sdlbasename%.zip
echo [Extracting SDL2]
tar -xf %installdir%\%sdlbasename%.zip -C %installdir%\
del %installdir%\%sdlbasename%.zip

::Download and extract SDL_image
echo [Downloading SDL2_image]
set "sdlimagename=SDL2_image-devel-%sdlimageversion%-%sdltype%"
curl -L "https://github.com/libsdl-org/SDL_image/releases/download/release-%sdlimageversion%/%sdlimagename%.zip" --output %installdir%\%sdlimagename%.zip
echo [Extracting SDL2_image]
tar -xf %installdir%\%sdlimagename%.zip -C %installdir%\
del %installdir%\%sdlimagename%.zip

::Download and extract SDL_mixer
echo [Downloading SDL2_mixer]
set "sdlmixername=SDL2_mixer-devel-%sdlmixerversion%-%sdltype%"
curl -L "https://github.com/libsdl-org/SDL_mixer/releases/download/release-%sdlmixerversion%/%sdlmixername%.zip" --output %installdir%\%sdlmixername%.zip
echo [Extracting SDL2_mixer]
tar -xf %installdir%\%sdlmixername%.zip -C %installdir%\
del %installdir%\%sdlmixername%.zip

::Download and extract SDL_ttf
echo [Downloading SDL2_ttf]
set "sdlttfname=SDL2_ttf-devel-%sdlttfversion%-%sdltype%"
curl -L "https://github.com/libsdl-org/SDL_ttf/releases/download/release-%sdlttfversion%/%sdlttfname%.zip" --output %installdir%\%sdlttfname%.zip
echo [Extracting SDL2_ttf]
tar -xf %installdir%\%sdlttfname%.zip -C %installdir%\
del %installdir%\%sdlttfname%.zip

::merge folders
echo [Merging folders]
::copying sdl_image
xcopy %installdir%\SDL2_image-%sdlimageversion% %installdir%\SDL2-%sdlbaseversion% /s /y
rmdir %installdir%\SDL2_image-%sdlimageversion% /s /Q
::copying sdl_mixer
xcopy %installdir%\SDL2_mixer-%sdlmixerversion% %installdir%\SDL2-%sdlbaseversion% /s /y
rmdir %installdir%\SDL2_mixer-%sdlmixerversion% /s /Q
::copying sdl_ttf
xcopy %installdir%\SDL2_ttf-%sdlttfversion% %installdir%\SDL2-%sdlbaseversion% /s /y
rmdir %installdir%\SDL2_ttf-%sdlttfversion% /s /Q

::rename folder to add the installation type
ren %installdir%\SDL2-%sdlbaseversion% SDL2-%sdlbaseversion%-%sdltype%

echo [SDL successfully installed]
pause


