
# Perlin Noise Generator
![Perlin Noise](https://i.imgur.com/8yfVoB5.png)
![Fractal Noise](https://i.imgur.com/5LcYaYX.png)
# About

A Perlin Noise generator with a graphical interface that allows the user to change the noise size.
This is not a perfect implementation of Perlin Noise but rather an attempt to apply the theoretical concepts.

# Compiling


## On Linux

You need ``libsdl2-dev`` and ``libsdl2_image-dev`` installed on your system.
Enter the repository directory and type 

```
chmod +x compile.sh
./compile.sh
```
the executable named ``perlin`` will be generated.

## On Windows

To compile you need to have installed [MinGW-32](https://sourceforge.net/projects/mingw/) and the SDL2 development libraries.
The repository contains ``SetupSDL.bat``, a script that will automatically download and install the libraries (Needs to be run as administrator).
The script will create the directory ``C:\SDL2-2.26.4-mingw``.

Copy ``C:\SDL2-2.26.4-mingw\i686-w64-mingw32\bin\SDL2.dll`` and ``C:\SDL2-2.26.4-mingw\i686-w64-mingw32\bin\SDL2_image.dll`` to the code directory.



Once everything is there open command prompt in the repository directory and run ``compile.bat``

This will generate ``perlin.exe``


