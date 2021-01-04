
The benchmarks can be compiled on a PC, for example using Linux Ubuntu via
Rasbian Toolchain or directly via a  Raspberry Pi Terminal command such as:

gcc  whets.c cpuidc.c -lm -O3 -march=armv6 -mfloat-abi=hard -mfpu=vfp -o whetstonePiA6

The commands are provided at the start of each C source code. The executables 
and compile time observed on the Raspberry Pi are:

Whetstone Benchmark        whetstonePiA6    10.2 seconds
Dhrystone Benchmark        dhrystonePiA6     8.6 seconds
Linpack Benchmark          linpackPiA6      15.1 seconds
  or at single precision   linpackPiSP
Livermore Loops Benchmark  liverloopsPiA6   35.8 seconds
Memory Speed               memspeedPiA6      9.0 seconds  
Bus Speed                  busspeedPiA6      9.0 seconds

Execute using a Terminal command, for example, ./whetstonePiA6
Results are displayed and save in text log files - see Example Logs.

Versions to use new ARM hardware options provided in the Raspberry 
Pi 2, benchmarks are named xxxxxxxPiA7 instead of PiA6.

Example RPi 2 compile times with gcc 4.8 are:
            liverloopsPiA7 13.2 seconds
            whetstonePiA7   3.9 seconds

Linux Intel folder contains executables to run on Intel CPUs via
Linux and are compiled from the same source codes. 

For details and example results on ARM and Intel processors see 
http://www.roylongbottom.org.uk/Raspberry Pi Benchmarks.htm

See also ReadMe.txt in Java, OpenGL, DriveSpeed, LanSpeed and 
Temperature_MHz_Test folders.

NOTE - After unzipping, the benchmark execution file Properties,
Permissions needs a “Make the file executable” selection.   

NEON benchmarks now included in NEON folder and added compile 
statements in Source Code folder. 

Roy Longbottom
March 2015

