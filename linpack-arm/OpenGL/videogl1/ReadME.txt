Raspberry Pi OpenGL GLUT Benchmark

After booting Raspbian-jessie on a Raspberry Pi 2, freeglut software was installed via:

sudo apt-get install freeglut3
sudo apt-get install freeglut3-dev

My OpenGL benchmark runs via Windows and Linux. The latter is described in the following that also includes results. 

http://www.roylongbottom.org.uk/linux%20opengl%20benchmarks.htm  

NOTE: In 1992, I approved a request from  a Quality Engineer at  Canonical, to use this OpenGL benchmark in the testing framework of the Unity desktop software. 

Following slight modifications for obtaining configuration details, the benchmark was correctly compiled (within a day), using the following command:

gcc ogl1.c cpuidc.c -lrt  -lm -O3 -lglut -lGLU -lGL -o videogl32

The benchmark has six tests, as shown in the results, that are displayed (if visible) and saved in log file videogl.txt. 

Default ./videogl32 runs in full screen mode but can also has run time parameters to use other sizes and avoid other details, as in script file runit, containing the following

./videogl32 Width 320, Height 240, NoEnd
./videogl32 Width 640, Height 480, NoHeading, NoEnd
./videogl32 Width 1024, Height 768, NoHeading, NoEnd
./videogl32 NoHeading

Default running time is 5 Seonds per test. This can be increased by another parameter, such as:

./videogl32 Width 1024, Height 768, Seconds 20, NoHeading, NoEnd

First results from this were extremely slow:

 #####################################################################

 GLUT OpenGL Benchmark 32 Bit Version 1, Mon Apr 18 10:01:21 2016

          Running Time Approximately 5 Seconds Each Test

 Window Size  Coloured Objects  Textured Objects  WireFrm  Texture
    Pixels        Few      All      Few      All  Kitchen  Kitchen
  Wide  High      FPS      FPS      FPS      FPS      FPS      FPS

   320   240      9.5      5.4      7.1      3.7      1.5      1.1
   640   480      3.5      2.9      2.8      1.9      1.3      0.7
  1024   768      1.5      1.3      1.3      1.3      1.0      0.4
  1824   984      0.7      0.6      0.6      0.5      0.7      0.2

                   End at Mon Apr 18 10:04:58 2016


Next, via sudo raspi-config. I enabled the experimental desktop GL driver. Then the results were as follows,  

 #####################################################################

 GLUT OpenGL Benchmark 32 Bit Version 1, Mon Apr 18 10:18:33 2016

          Running Time Approximately 5 Seconds Each Test

 Window Size  Coloured Objects  Textured Objects  WireFrm  Texture
    Pixels        Few      All      Few      All  Kitchen  Kitchen
  Wide  High      FPS      FPS      FPS      FPS      FPS      FPS

   320   240     49.4     49.4     39.9     24.9     10.0      7.1
   640   480     50.0     49.4     30.1     23.8     10.0      7.1
  1024   768     47.2     45.4     24.7     23.3     10.0      7.0
  1920  1080     18.5     18.2     16.5     15.5      9.8      7.0

                   End at Mon Apr 18 10:20:48 2016

These speeds appear to be limited by Wait For Vertical Blank or VSYNC. This can be overcome using command export vblank_mode=0. After adding this at the start of runit script file, results were:

 #####################################################################

 GLUT OpenGL Benchmark 32 Bit Version 1, Tue Apr 19 09:02:30 2016

          Running Time Approximately 5 Seconds Each Test

 Window Size  Coloured Objects  Textured Objects  WireFrm  Texture
    Pixels        Few      All      Few      All  Kitchen  Kitchen
  Wide  High      FPS      FPS      FPS      FPS      FPS      FPS

   320   240    210.3    114.4     52.6     32.5     12.1      7.8
   640   480    115.0     89.5     48.5     30.6     11.9      7.7
  1024   768     47.9     46.7     37.5     28.3     11.6      7.6
  1920  1080     20.6     18.6     16.8     15.9     11.4      7.4

                   End at Tue Apr 19 09:04:45 2016

PROBLEMS

With and without VSYNC there is some tearing of textures in the last test.

The Terminal display of results is spoiled, on using the vblank command, with the following message on each screen size change. The log file is not affected.
 
  320   240ATTENTION: default value of option vblank_mode overridden by environment
   210.3    114.4     52.6     32.5     12.1      7.8 


OTHER FUNCTION - Reliability Tests 

A single test (1 to 6) can be run for extended periods as follows:

./videogl32 Wide 1024, High 768, Test 6, Minutes 20

or down to

./videogl32 W 1024 H 768 T 6 M 20

FPS speeds are logged and displayed every 30 seconds 

RPIHeatMHz program is also included to log CPU MHz and temperature. This can be run via a local Terminal or remotely, in my case via Putty.exe on a Windows PC. See example in RPIHeatMHz.txt.


OTHER FUNCTION - Zoom and Rotation Speed

On running tests 5 or 6 for extended periods, Zoom in and out is provided  by up/down keys and rotation speeds via left/right keys.


LOG FILE

An example log file is included, mainly to show configuration details obtained.

IMAGES USED

In order to run, the .bmp images must be in the same folder as the compiled videogl32.

Different anf larger .bmp image files can be used, but withthe same names. Following are results where 12 KB images were increased to 192 KB (64 x 64 pixels to 256 x 256), showing impact on textured tests.

 #####################################################################

 GLUT OpenGL Benchmark 32 Bit Version 1, Tue Apr 19 13:30:49 2016

          Running Time Approximately 5 Seconds Each Test

 Window Size  Coloured Objects  Textured Objects  WireFrm  Texture
    Pixels        Few      All      Few      All  Kitchen  Kitchen
  Wide  High      FPS      FPS      FPS      FPS      FPS      FPS

   320   240    213.4    110.6     39.5     12.4     11.7      2.6
   640   480    111.1     84.1     34.0     12.1     11.9      2.5
  1024   768     49.1     47.0     27.7     11.0     11.7      2.4
  1920  1080     20.2     17.3     15.7      9.3     11.5      2.2

                   End at Tue Apr 19 13:33:07 2016


Roy Longbottom
April 2016
