Contents

Source Files          OpenGL1P.c, cpuid.c, cpuid.h 

Makefiles             Makefile
                      Makefile.include

Compiled Benchmark    OpenGL1Pi.bin 
Texture Images Used   benchmk.raw, opengl.raw, raspi.raw
Example Log File      OpenGL1Pi.txt

Images are 128 x 128 pixels x 3 bytes for RGB = 49152 bytes, no headers


Commands with LXTerminal pointing to directory containing above files.

Compile Commands  - Use the two cc extremely long (>512 charas) compile
                    commands and the cc link command in comments
                    at the start of  OpenGL1Pi.c
                     

Run Commands        ./OpenGL1Pi.bin W pppp, H pppp, R mm
                    where W can be W, w, Wide, width  etc.
                          H        H, h, high, Height etc.
                          R        R, r, RunTime,     etc.
                          pppp     pixels e.g W 1920, H 1080  
                                              W  160, H 80
R is for Reliability mode where mm can be added for running time
in minutes. This runs all 16 tests at maximum loading with textures.

June 2015 Version 1.2 - original counted number of frames twice,
doubling measured FPS.