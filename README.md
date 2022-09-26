# Perlin Noise Generator
![Perlin Noise](https://i.imgur.com/8yfVoB5.png)
# About

A Perlin Noise generator with a graphical interface that allows the user to change the noise size.
This is not a perfect implementation of Perlin Noise but rather an attempt to apply the theoretical concepts.

# Compiling


## On Linux

You need ``libsdl2-dev`` and ``libsdl2_image-dev`` installed on your system.
Enter the repository directory and type 

```
chmod +x ./compile.sh
./compile.sh
```
the executable named ``perlin`` will be generated.

## On Windows
Install [MinGW-32](https://sourceforge.net/projects/mingw/) and add the directory containing the gcc executable to the system path.

Download ``SDL2-devel-2.24.0-mingw.zip`` from [here](https://github.com/libsdl-org/SDL/releases).
Extract the contents and move the ``include`` folder and the ``lib``  folder to the repository directory.

Download ``SDL2_image.dll`` from [here](https://github.com/libsdl-org/SDL_image/releases)
and move it to the repository directory.

Open command line in the repository directory and run:
``compile.bat``

This will generate ``perlin.exe``



