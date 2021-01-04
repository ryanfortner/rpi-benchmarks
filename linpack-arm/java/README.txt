WHETSTONE BENCHMARK JAVA VERSIONS

JDK needed to compile class files and/or JRE to run them.

Off Line Version
The class file was produced using JDK 1.6 via Linux Ubuntu 10.04 
- command javac whetstc.java
It can be executed via the command java whetstc and results 
are saved in whets.txt. See example for 3 GHz Phenom speed.

java > whetstone > whetstc.class
java > whetstone > whets.txt
java > source code > whetstone-off-line > whetstc.java

Online Applet Version
The class file was produced using JDK 1.6 via Linux Ubuntu 10.04
- javac whets2.java
It is executed via opening whetjava2.htm. Use screen copy function
for a copy of results. See screenShot.gif for 3 GHz Phenom speed.
 
java > whetstone > whets2.class
java > whetstone > whetjava2.htm
java > whetstone > screenShot.gif
java > source code > whetstone-on-line > whets2.java

Both Versions Produced By JDK 7 On Raspberry Pi

java > whetstone > fromJDK7 
       whetjava2.htm, whets2.class, whetstc.class
WARNING - this might not run under JRE 6 but it does on 
the Pi that also has JRE 7.

#######################################################################
JAVADRAW BENCHMARK

java > javadraw > JavaDrawPC.class - Produced via JDK 6 and Linux
java > javadraw > JavaDrawPi.class - Produced bb JDK 7 on Raspberry Pi

Three images used:

java > javadraw > bground.png 
java > javadraw > bground1.png
java > javadraw > sweep.png

java > javadraw >JavaDraw.txt - example log


Two source files - identical code but different Class and file names
and version title:

java > javadraw > JavaDrawPC.java
java > javadraw > JavaDrawPi.java