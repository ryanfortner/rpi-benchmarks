Contents

Source Files - lanspeed.c, cpuidc.c, cpuidh.h -  compile on RPi using:
               cc  lanspeed.c cpuidc.c -lm -lrt -O3 -o LanSpeed
Benchmark    - LanSpeed for ARM/Raspberry Pi
Benchmark    - LanSpeedx86Win variation compiled for Windows based PC
Benchmark    - LanSpeedx86Lin compiled on PC with 32 bit Linux Ubuntu
               Change version in lanspeed.c from "RasPi" to "Intel" 
Script File  - runlan32 to run LanSpeedx86Lin
Example log  - lanSpeed.txt

Run time parameters  - ./LanSpeed
                     - ./LanSpeed MBytes xx, FilePath /dddd/dddd
                 or  - ./LanSpeed M xx, F /dddd/dddd

See http://www.roylongbottom.org.uk/Raspberry%20Pi%20Benchmarks.htm
for details on how to set up the LAN paths and for results.

Note: after unzipping benchmmark execution files need Properties,
Permission setting "Allow Executing".