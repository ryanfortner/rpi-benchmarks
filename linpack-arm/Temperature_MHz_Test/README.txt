This replaces RPiHeatMHz as temperature and CPU MHz
are measured.

See RPiHeatMHz.c for information on how to compile and run
and  RPiHeatMHz.txt for results log file. The program is 
run via a command in an LXTerminal window.
Revised Oct 2013 MHz details included
Revised July 2016 to use different CPU MHz function

 Run     command -  ./RPiHeatMHz passes nnn, seconds ttt
 
                    for ppp samples at sss second intervals
                    only needs first character p, P, s, S
 
 15 minutes test -  ./RPiHeatMHz passes 30, seconds 30
                    + new version example

 Default            ./RPiHeatMHz
                    10 samples at 1 second intervals  
