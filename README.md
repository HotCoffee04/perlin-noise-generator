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
chmod +x ./compile.sh
./compile.sh
```
the executable named ``perlin`` will be generated.

## On Windows

Install [MinGW-32](https://sourceforge.net/projects/mingw/) and add the directory containing the gcc executable to the system path.

Download ``SDL2-devel-2.24.0-mingw.zip`` from [here](https://github.com/libsdl-org/SDL/releases).
Extract the contents and move the ``include`` folder and the ``lib``  folder to the repository directory.
move from the bin folder ``SDL2.dll`` to the repository directory.

Download ``SDL2_image-devel-2.6.2-mingw.zip`` from [here](https://github.com/libsdl-org/SDL_image/releases)
ad do the exact same you did for the other SDL zip:
Move the ``include`` and ``lib`` folders and the ``SDL2_image.dll`` file to the repository directory.

Once everything is there open command prompt in the repository directory and run:
``compile.bat``

This will generate ``perlin.exe``



