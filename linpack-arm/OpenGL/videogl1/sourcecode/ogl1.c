/*

gcc ogl1.c cpuidc.c -lrt  -lm -O3 -lglut -lGLU -lGL -o videogl32

*/

 #include <GL/glut.h>
 #include <stdio.h>
 #include "cpuidh.h"
 #include <math.h>
 #include <string.h>

 #include <malloc.h>
 #include <time.h>



 #define BOOL     int
 #define TRUE     1
 #define FALSE    0

 // #define version  "64 Bit Version 1"
 #define version  "32 Bit Version 1"

 double eyeX = 0;
 double eyeY = 0;
 double eyeZ = 3.5;  // 5 larger image
 double eyeMoZ = 3.5;

 double upX = 0;
 double upY = 1;
 double upZ = 0;

 double eMod1 = 10.0;
 double eMod2 = 11.0;
 double eMod3 = 12.0;
 double eMod4 = 13.0;
 
 double whichWay1 = 1;
 double whichWay2 = -1;
 double whichWay3 = 1;
 double whichWay4 = -1;
 double whichWay5 = -1;

 double centreX = 2.5;  // + left
 double centreY = -3; // - up
 double centreZ = 0;

 double runSecs = 5.0;
 double runMins = 0.0;
 double frameCount = 0.0;
 double tempCount = 0.0;
 double fps = 0.0;
 double runSecs2 = 0.5;
 double dispSecs = 0.5;
 double tempSecs = 0.0;

 int  loopDraw  = 0;
 int  screenWide = 640;
 int  screenHigh = 480;
 int  tex1Width =  64;
 int  tex1Height = 64;
 int  tex2Width =  32;
 int  tex2Height = 32;
 int  objectNumMajor = 24;
 int  objectNumMinor = 32;
 int  flyers = 10;
 int  oneTest = 0;
 int  repeats = 1;
 int  repCount = 1;


 BOOL useTexture  = FALSE;
 BOOL chgTex      = TRUE;
 BOOL useVertexArray = TRUE;
 BOOL allObjects = TRUE;
 BOOL halfObject = FALSE;
 BOOL doTime = TRUE;
 BOOL calibrate = TRUE;
 BOOL shadeIt = FALSE;
 BOOL doHandle = FALSE;
 BOOL noHeading = FALSE;
 BOOL noEnd = FALSE;

 float  degree = 1.0f;
 float  aspect;
 float  leftRight = 0.0;
 float  foreBack  = 0.0;

 float    wall1r, wall1g, wall1b;
 float    framer, frameg, frameb;
 float    fram2r, fram2g, fram2b;
 float    floorr, floorg, floorb;
 float    ceilr, ceilg, ceilb;
 float    winr, wing, winb;
 float    woodr, woodg, woodb;
 float    doorr, doorg, doorb;
 float    plinr, pling, plinb;
 float    cdorr, cdorg, cdorb;
 float    wtopr, wtopg, wtopb;
 float    wedgr, wedgg, wedgb;
 float    tlegr, tlegg, tlegb;
 float    tedgr, tedgg, tedgb;
 float    ctopr, ctopg, ctopb;
 float    clegr, clegg, clegb;
 float    handr, handg, handb;
 float    highM;
 float    wideM, deepM, wideMa;
 float    deepMa, deepMb, deepMc;
 float    wideL, inLS, deepLS, thickTB;
 float    floorUp, inset, handleUp;
 float    wide2, wide2a, wide2b, wide2c, wide2d; 
 float    wallR, wallL, wallF, wallB;
 float    shelfHi;
 float    upBarIn;
 float    rotator = 0;
 float    rotate2;
 float    viewSide;
 float    angleX = 0;
 float    chairHi;
 float    cbackHi;
 float tile5W = 12.0f;
 float tile5H = 12.0f;
 float tile6W = 7.87f;
 float tile6H = 7.87f;
 float tile7W = 7.87f;
 float tile7H = 2.5f;
 float tile8W = 7.87f;
 float tile8H = 7.87f;
 float fromLorF;
 float fromLorFa;
 float fromWall;
 float winBup = 42;
 float frontLAlign;
 float bakRAlign;
 float newFL;
 float newBR;
 float upAlign;
 float downAlign;
 float roomWidth;
 float roomDepth;
 float roomHight;

 int cFloor = 0;
 int cLeft = 1;
 int cRight = 2;
 int cBack = 3;
 int cFront = 4;
 int cBase = 1;
 int cWall = 2;
 int cFull = 3;
 int cDoor = 1;
 int noBottom = 1;
 int glassIn = 2;
 int shelfIn = 4;
 int backIn = 8;
 int noTop  = 16;
 int upBar = 32;
 int newTop = 64;
 int noEdge = 0;
 int edge   = 1;
 int useTile5 = 5;
 int useTile6 = 6;
 int useTile7 = 7;
 int useTile8 = 8;
 int lines = 0;
 int alignFrontL = 1;
 int alignBakR = 2;
 int alignUp = 4;
 int alignDown = 8;


 #if !defined(M_PI)
 #define M_PI 3.14159265F
 #endif

 char title[200];
 char testTitle[40];


 unsigned char *myTile[11];
 unsigned char *mem;

 unsigned int  abwide[20];
 unsigned int  abhigh[20];

 GLenum glErr;

 FILE    *outfile;
 FILE    *infile;

 char    timeday[30];
 void local_time();

 void sidex(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void sidey(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void facex(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void facey(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void flatx(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void flaty(float x1, float x2, float y1,
           float y2, float z1, float z2);

 void frontView(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void rearView(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void leftView(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void rightView(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void centreView(float x1, float x2, float y1,
           float y2, float z1, float z2);
 void lastView(float x1, float x2, float y1,
           float y2, float z1, float z2);

 void boxA(float ri, float le, float to,
           float bo, float fr, float ba);

 void roomWalls(float x1, float x2, float y1,
               float y2, float z1, float z2,
               float wallL, float wallR,
               float wallF, float wallB);

 void holeA(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill, int paint);

 void frameW(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);

 void plynth(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);

 void workTop(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill,
           int alignD, int alignW);
 void table(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);
 void chair(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);

 void door(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);

 void tileSurface(float h1, float h2, float na,
           float fix, float w1, float w2, float tileHigh,
           float tileWide, int alignW, int alignH, int tileData, int surface);

 void door2(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);

 void door3(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill);



// Texture for Tunnel Walls

unsigned char carve[] =
{
    3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,
    4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,4,3,4,1,4,
    3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,4,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,4,4,
    0,0,4,3,4,3,1,3,4,0,4,3,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,4,3,4,3,1,3,4,0,4,3,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    1,1,1,1,1,1,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,
    4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,4,3,4,1,4,
    3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,1,1,1,1,1,1,1,1,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,0,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,0,0,0,0,0,0,0,0,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,1,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,0,4,3,4,3,1,3,4,0,4,3,4,3,1,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,4,4,
    3,0,3,4,3,4,1,4,3,0,3,4,3,4,1,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,4,4,
    0,0,4,3,4,3,1,3,4,0,4,3,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,4,3,4,3,1,3,4,0,4,3,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    3,4,3,4,3,4,1,4,3,0,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,3,4,3,4,3,1,3,4,0,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    1,1,1,1,1,1,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
    4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,
};

int carveRGB[5][3] =
{
    {0, 0, 0,},
    {255, 255,},
    {0, 0, 0,},
    {125, 91, 32,},
    {125, 125, 0,},
};

void setCarveTexture(void)
{
   int i;
   int p = 0;
    
    for (i=0; i<tex1Height*tex1Width; ++i)
    {
        myTile[10][p+0] = (char)carveRGB[carve[i]][0];
        myTile[10][p+1] = (char)carveRGB[carve[i]][1];
        myTile[10][p+2] = (char)carveRGB[carve[i]][2];
        myTile[10][p+3] = (unsigned char)255;
        p += 4;   
    }
}

 typedef struct _SPHERE
 {
    GLfloat fXr, fYr, fZr;
 } SPHERE;

 SPHERE sphere1;
 SPHERE sphere2;

BOOL loadBMP(char abmp[100], int f)
{
       
   FILE *fr1;
   int g;
   char buf1[60];  
        
   fr1 = fopen(abmp, "rb");
   if (fr1 == NULL)
   {
      printf ("\n Cannot open %s file \n\n", abmp);
      printf(" Press Enter\n");
      g  = getchar();
      exit (0);
   }

   if (fread(buf1, 54, 1, fr1) == 0)
   {
      printf ("\n Error reading %s file headers \n\n", abmp);
      printf(" Press Enter\n");
      g  = getchar();
      exit (0);
   }
    

    abwide[f] = (abs)(buf1[18]+256*buf1[19]);
    abhigh[f] = (abs)(buf1[22]+256*buf1[23]);

    
   if ( abhigh[f] * abwide[f] > 65536)
   {
      printf ("\n %s file too many pixels\n\n", abmp);
      printf(" Press Enter\n");
      g  = getchar();
      exit (0);
   }
    
   if (fread(myTile[f], abhigh[f] * abwide[f] * 3, 1, fr1) == 0)
   {
      printf ("\n Error reading %s file\n\n", abmp);
      printf(" Press Enter\n");
      g  = getchar();
      exit (0);
   }
   fclose (fr1);

    return TRUE;
} // loadBMP



void changeSize(int w, int h) {

        // Prevent a divide by zero, when window is too short
        // (you cant make a window of zero width).
        if (h == 0)
                h = 1;
        float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);

        // Reset Matrix
        glLoadIdentity();

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

        // Set the correct perspective.
        gluPerspective(45.0f, ratio, 0.1f, 100.0f);

        // Get Back to the Modelview
        glMatrixMode(GL_MODELVIEW);

} // changeSize

void drawSphere(int test)
{
    struct vertex {
        GLfloat t[2];
        GLfloat n[3];
        GLfloat v[3];
    };

    int numVerts = (objectNumMajor+1) * (objectNumMinor+1);
    int numStrips = halfObject ? objectNumMajor / 2 : objectNumMajor;
    int numPerStrip = 2 * (objectNumMinor+1);
    int numElements = (objectNumMajor+1) * numPerStrip;

    static struct vertex *vertexArray, *v;
    static GLuint *elementArray, *e;
    static int numMajor;
    static int numMinor;
    int i, j;

    if (!vertexArray || numMajor!=objectNumMajor
                                         || numMinor!=objectNumMinor)
    {
        float radius = 2.5F; // 0.6F;
        double majorStep = 2.0F*M_PI / objectNumMajor;
        double minorStep = M_PI / objectNumMinor;

        if (vertexArray) free(vertexArray);
        vertexArray = (struct vertex *)
                calloc(numVerts, sizeof(struct vertex));

        if (elementArray) free(elementArray);
        elementArray = (GLuint *)
                calloc(numElements, sizeof(GLuint));

        numMajor = objectNumMajor;
        numMinor = objectNumMinor;

        v = vertexArray;
        e = elementArray;
        for (i=0; i<=numMajor; ++i) {
            double a = i * majorStep;
            GLfloat x = (GLfloat) cos(a);
            GLfloat y = (GLfloat) sin(a) * 1.4f;

            for (j=0; j<=numMinor; ++j) {
                double b = j * minorStep;
                GLfloat c = (GLfloat) sin(b);
                GLfloat r = c * radius;
                GLfloat z = (GLfloat) cos(b);

                v->t[0] = -i/(GLfloat) numMajor;
                v->t[1] = j/(GLfloat) numMinor;

                v->n[0] = x*c;
                v->n[1] = y*c;
                v->n[2] = z;

                v->v[0] = x*r;
                v->v[1] = y*r;
                v->v[2] = z*radius;

                v++;

                *e++ = (i+1) * (numMinor+1) + j;
                *e++ = i * (numMinor+1) + j;
            }
        }
    }
    if (useVertexArray)
    {
        glInterleavedArrays(GL_T2F_N3F_V3F, 0, vertexArray);

        for (i=0, e=elementArray; i<numStrips; ++i, e+=numPerStrip)
        {
            if (test == 0)
            {
                glDrawElements(GL_TRIANGLE_STRIP, numPerStrip,
                                                GL_UNSIGNED_INT, e);
            }
            else
            {
                glDrawElements(GL_LINE_STRIP, numPerStrip, GL_UNSIGNED_INT, e);
            }
        }
    }
    else
    {
        for (i=0, e=elementArray; i<numStrips; ++i, e+=numPerStrip)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (j=0; j<numPerStrip; ++j)
            {
                v = &vertexArray[e[j]];

                glTexCoord2fv(v->t);
                glNormal3fv(v->n);
                glVertex3fv(v->v);
            }
            glEnd();
        }
    }
    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
//        Msg2("GL ERROR drawSphere", glErr);
        exit(2);
    }
} // drawSphere




void draw_scene(void)
{
    int i, j, k, f;
    float px, py, pz, pi;
    float z1, z2, x1, x2, y1, y2;
    float w1;
    float g1;
    float ff;
    float xpos[4] = { 2.5, 2.5,-2.5,-2.5 };
    float ypos[4] = { 2.5,-2.5, 2.5,-2.5 };

    GLfloat light0Pos2[4] = { 0.7F, 0.7F, 0.8F, 0.0F };
    GLfloat light0Pos[4] = { 0.70F, 0.70F, 0.8F, 0.0F };

    GLfloat matAmb[4] = { 0.01F, 0.01F, 0.01F, 1.00F };
    GLfloat matDiff[4] = { 0.65F, 0.05F, 0.20F, 0.60F };

    GLfloat matSpec[4] = { 0.50F, 0.50F, 0.50F, 1.00F };
    GLfloat matShine = 20.00F;

    aspect = (float)screenWide / (float)screenHigh;

    if (loopDraw == 0)
    {
        allObjects = FALSE;
        useTexture = FALSE;
        sprintf (testTitle, " Few Objects, No Textures,");
    }
    if (loopDraw == 1)
    {
        allObjects = TRUE;
        useTexture = FALSE;
        sprintf (testTitle, " All Objects, No Textures,");
    }
    if (loopDraw == 2)
    {
        allObjects = FALSE;
        useTexture = TRUE;
        sprintf (testTitle, " Few Objects, With Textures,");
    }
    if (loopDraw == 3)
    {
        allObjects = TRUE;
        useTexture = TRUE;
        sprintf (testTitle, " All Objects, With Textures,");
    }
    if (loopDraw == 4)
    {
        useTexture = FALSE;
        sprintf (testTitle, " WireFrame Kitchen,");
    }
    if (loopDraw == 5)
    {
        useTexture = TRUE;
        sprintf (testTitle, " Tiled Kitchen,");
    }
    if (doTime)
    {
        start_time();
        doTime = FALSE;
    }   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, matShine);

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glEnable( GL_DITHER );

    glEnable(GL_DEPTH_TEST);

    glClearColor( 0.0F, 0.0F, 1.0F, 1.0F );


    if (loopDraw < 4)
    {
        // *****  Tunnel *****

        glPushMatrix();
        glPushAttrib(GL_TEXTURE_BIT); // tunnel
        {   
             glShadeModel( GL_FLAT );
            
             glMatrixMode( GL_PROJECTION );
             glLoadIdentity();
             gluPerspective(45, 1, 0.01, 150);
        
             gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, upX, upY, upZ);
             
             glMatrixMode( GL_MODELVIEW );
             // *****  Tunnel Wall Texture *****
    
             if (useTexture)
             {

                glTexEnvi(GL_TEXTURE_ENV,
                                        GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_T, GL_REPEAT);   
                glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[4], abhigh[4], 0,
                                           GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[4]); // GL_BGR GL_RGBA
                glEnable(GL_TEXTURE_2D);
             }
             else
             {
                 // ***** Tunnel Wall Carve Pattern *****
                 
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_T, GL_REPEAT);   
                glTexImage2D(GL_TEXTURE_2D, 0, 4, tex1Width, tex1Height,
                               0, GL_RGBA, GL_UNSIGNED_BYTE, myTile[10]);      
                glEnable(GL_TEXTURE_2D);
             }

             glBegin(GL_QUADS);
             {
              // ***** Right Wall *****
        
              glNormal3f( 0.0F, 0.0F, 1.0F);
              glTexCoord2f( 12.0F, 3.0F);glVertex3f( 0.24F,-0.32F,-1.0F); 
              glTexCoord2f(  0.0F, 3.0F);glVertex3f( 0.24F,-0.32F, 3.0F);
              glTexCoord2f(  0.0F, 0.0F);glVertex3f( 0.24F, 0.32F, 3.0F); 
              glTexCoord2f( 12.0F, 0.0F);glVertex3f( 0.24F, 0.32F,-1.0F);
        
              // ***** Left Wall *****
        
              glNormal3f( 0.0F, 0.0F, 1.0F);
              glTexCoord2f( 12.0F, 3.0F);glVertex3f(-0.24F,-0.32F, 3.0F); 
              glTexCoord2f(  0.0F, 3.0F);glVertex3f(-0.24F,-0.32F,-1.0F);
              glTexCoord2f(  0.0F, 0.0F);glVertex3f(-0.24F, 0.32F,-1.0F); 
              glTexCoord2f( 12.0F, 0.0F);glVertex3f(-0.24F, 0.32F, 3.0F);
             }
             glEnd();
    
             glDisable(GL_TEXTURE_2D);
             
             // ***** Ceiling Tiles *****
    
             if (useTexture)
             {
                glTexEnvi(GL_TEXTURE_ENV,
                                        GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_T, GL_REPEAT);   
                glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[3], abhigh[3], 0,
                                           GL_RGB, GL_UNSIGNED_BYTE, myTile[3]);
                glEnable(GL_TEXTURE_2D);
             }

             glBegin(GL_QUADS);
             {  
              j=0;
              for (i=0; i<4; i++)
              {       
                  x1 = 0.24f - (float)i * 0.12f;
                  x2 = x1 - 0.12f;
        
                  for (k=0; k<27; k++)
                  {
                      if (j == 0)
                      {
                          glColor3f(0.5F, 0.5F, 0.5F);
                          j = 1;
                      }
                      else
                      {
                          glColor3f(0.6F, 0.6F, 0.2F);
                          j = 0;
                      }
                      z1 = -1.0f + (float)k * 0.15f;
                      z2 = z1 + 0.15f;
        
                      glNormal3f( 0.0F, 0.0F, 1.0F);
                      glTexCoord2f(1.0F,1.0F); glVertex3f(x1, 0.32F, z2);
                      glTexCoord2f(0.0F,1.0F); glVertex3f(x2, 0.32F, z2);
                      glTexCoord2f(0.0F,0.0F); glVertex3f(x2, 0.32F, z1); 
                      glTexCoord2f(1.0F,0.0F); glVertex3f(x1, 0.32F, z1);
                  }
              }    
             }    
             glEnd();
             if (useTexture)
             {
                 glDisable(GL_TEXTURE_2D);
             }
    
            // ***** Floor Tiles *****
    
             if (useTexture)
             {
                glTexEnvi(GL_TEXTURE_ENV,
                                        GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_T, GL_REPEAT);   
                glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[3], abhigh[3], 0,
                                           GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[3]); // GL_BGR GL_RGBA
                glEnable(GL_TEXTURE_2D);
             }

             glBegin(GL_QUADS);
             {    
              j=0;
              for (i=0; i<4; i++)
              {       
                  x1 = 0.24f - (float)i * 0.12f;
                  x2 = x1 - 0.12f;
        
                  for (k=0; k<27; k++)
                  {
                      if (j == 0)
                      {
                          glColor3f(0.3F, 0.25F, 0.25F);
                          j = 1;
                      }
                      else
                      {
                          glColor3f(0.15F, 0.35F, 0.35F);
                          j = 0;
                      }
                      z1 = -1.0f + (float)k * 0.15f;
                      z2 = z1 + 0.15f;
        
                      glNormal3f( 0.0F, 0.0F, 1.0F);
                      glTexCoord2f(1.0F,1.0F); glVertex3f(x1,-0.32F, z1);
                      glTexCoord2f(0.0F,1.0F); glVertex3f(x2,-0.32F, z1);
                      glTexCoord2f(0.0F,0.0F); glVertex3f(x2,-0.32F, z2); 
                      glTexCoord2f(1.0F,0.0F); glVertex3f(x1,-0.32F, z2);   
                  }
              }    
             }    
             glEnd();

             if (useTexture)
             {
                 glDisable(GL_TEXTURE_2D);
             }


          if (allObjects)
          {
             // ***** Tunnel Flyers Texture *****
       
             glPushMatrix();  // flyers
             { 
              for (f=0; f<flyers; f++)
              {
                 if (useTexture)
                 {
                     if (chgTex)
                     {
                        glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[0], abhigh[0], 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[0]); // GL_BGR GL_RGBA
                        chgTex = FALSE;
                     }
                     else
                     {                
                        glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[1], abhigh[1], 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[1]); // GL_BGR GL_RGBA
                        chgTex = TRUE;
                     }
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);            
                     glEnable(GL_TEXTURE_2D);
                 }
        
              // ***** Flyers *****
    
                  ff = (float)(f+1)/(float)flyers;
                  glColor3f(1.0f, 0.5f*ff, 1.0f-ff);   
                  glRotatef(sphere2.fXr/(float)(f+2), 0.01f, 0.0f, 1.0f);
                
                  glBegin(GL_QUADS);
                  {
                     px = -0.1f;
                     py = 0.1f;
                     pz = -0.5f + 2.5f*ff;
                     pi = 0.05f;
                     glNormal3f( 0.0F, 0.0F, 1.0F);
                     glTexCoord2f(1.0F, 1.0F); glVertex3f(px, py,  pz);
                     glTexCoord2f(0.0F, 1.0F); glVertex3f(px-pi, py,  pz);
                     glTexCoord2f(0.0F, 0.0F); glVertex3f(px-pi, py-pi,  pz);
                     glTexCoord2f(1.0F, 0.0F); glVertex3f(px, py-pi,  pz);
                   
                  }
                  glEnd();
              }
    
              if (useTexture)
              {
                  glDisable(GL_TEXTURE_2D);
              }
             }
             glPopMatrix();  // flyers   
          }    
        }
        glPopAttrib();   // tunnel
        glPopMatrix();

        // ***** Back Scene *****
    
          if (allObjects)
          {
            // ***** Cubes ******
          
            glPushMatrix();
            glPushAttrib(GL_TEXTURE_BIT);  // cubes
            {      
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective(45, 1, 0.01, 150);
                gluLookAt(eyeX, eyeY, eyeZ-30, 0, 0, 0, upX, upY, upZ);
                
                glMatrixMode( GL_MODELVIEW );
                glLoadIdentity();
                           
                glShadeModel( GL_SMOOTH );
    
                // ***** Cube Texture *****
    
                if (useTexture)
                {            
                    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                    glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D,
                                       GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D,
                                           GL_TEXTURE_WRAP_T, GL_REPEAT);   
                    glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[3], abhigh[3], 0,
                                           GL_RGB, GL_UNSIGNED_BYTE, myTile[3]);
    
                    glEnable(GL_TEXTURE_2D);
                }
                w1 = 1.0;
                z1 = 5.5; // 0.5;
                z2 = z1 - w1;
                
                glRotatef(sphere1.fYr/3, 0.5f, 0.0f, 0.0f);
                glRotatef(sphere1.fZr/3, 0.0f, 0.0f, 1.0f);
     
                // **** 4 Cubes *****
                
                for (i=0; i<20; i++)
                {
                    glColor3f(1.0f, 1.0f/(float)i, 0.0f);
                    
                    x1 = xpos[i];
                    y1 = ypos[i];
                    x2 = x1 - w1;
                    y2 = y1 - w1;
                    
                    glRotatef(sphere1.fYr/(i+3), 0.0f, 1.0f, 0.0f);
      
                    glBegin(GL_QUADS);
                    glNormal3f( 0.0F, 0.0F, 1.0F);
                    glTexCoord2f( 1.0F, 1.0F); glVertex3f( x1, y1, z1);
                    glTexCoord2f( 0.0F, 1.0F); glVertex3f( x2, y1, z1);
                    glTexCoord2f( 0.0F, 0.0F); glVertex3f( x2, y2, z1);
                    glTexCoord2f( 1.0F, 0.0F); glVertex3f( x1, y2, z1);
                
                    glNormal3f( 0.0F, 0.0F, -1.0F);
                    glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z2);
                    glTexCoord2f( 0.0F, 1.0F); glVertex3f( x2, y1, z2);
                    glTexCoord2f( 0.0F, 0.0F); glVertex3f( x1, y1, z2);
                    glTexCoord2f( 1.0F, 0.0F); glVertex3f( x1, y2, z2);
                
                    glNormal3f( 0.0F, 1.0F, 0.0F);
                    glTexCoord2f( 1.0F, 1.0F); glVertex3f( x1, y1, z1);
                    glTexCoord2f( 0.0F, 1.0F); glVertex3f( x1, y1, z2);
                    glTexCoord2f( 0.0F, 0.0F); glVertex3f( x2, y1, z2);
                    glTexCoord2f( 1.0F, 0.0F); glVertex3f( x2, y1, z1);
                
                    glNormal3f( 0.0F, 1.0F, 0.0F);
                    glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z2);
                    glTexCoord2f( 0.0F, 1.0F); glVertex3f( x1, y2, z2);
                    glTexCoord2f( 0.0F, 0.0F); glVertex3f( x1, y2, z1);
                    glTexCoord2f( 1.0F, 0.0F); glVertex3f( x2, y2, z1);
                
                    glNormal3f( 1.0F, 0.0F, 0.0F);
                    glTexCoord2f( 1.0F, 1.0F); glVertex3f( x1, y1, z1);
                    glTexCoord2f( 0.0F, 1.0F); glVertex3f( x1, y2, z1);
                    glTexCoord2f( 0.0F, 0.0F); glVertex3f( x1, y2, z2);
                    glTexCoord2f( 1.0F, 0.0F); glVertex3f( x1, y1, z2);
                
                    glNormal3f( 1.0F, 0.0F, 0.0F);
                    glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z2);
                    glTexCoord2f( 0.0F, 1.0F); glVertex3f( x2, y2, z1);
                    glTexCoord2f( 0.0F, 0.0F); glVertex3f( x2, y1, z1);
                    glTexCoord2f( 1.0F, 0.0F); glVertex3f( x2, y1, z2);
                   glEnd();
                }
    
                if (useTexture)
                {            
                    glDisable(GL_TEXTURE_2D);
                }
            }    
            glPopAttrib(); // cubes
            glPopMatrix();
          }

          // ***** Eggs *****
           
         glPushMatrix();
         glPushAttrib(GL_TEXTURE_BIT);  // eggs
         {
                 if (useTexture)
                 {
                     glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[2], abhigh[2], 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[2]); // GL_BGR
                     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);            
                     glEnable(GL_TEXTURE_2D);
                 }
    
            // ***** Egg 1 *****
            
            glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
            glRotatef(sphere1.fYr, 0.0f, 1.0f, 0.0f);
            glRotatef(sphere1.fZr, 0.0f, 0.0f, 1.0f);
        
            glMatrixMode( GL_PROJECTION );
            glLoadIdentity();
        
            gluPerspective(120, aspect, 0.01, 150);
        
            glLightfv(GL_LIGHT0, GL_POSITION, light0Pos2);
    
            if (allObjects)
            {       
                gluLookAt(eyeX, eyeY, eyeZ-eMod1, centreX, centreY, centreZ, upX, upY, upZ);
            }
            else
            {
                gluLookAt(eyeX, eyeY, eyeZ-eMod1, 0, 0, centreZ, upX, upY, upZ);
            }
    
            glMatrixMode( GL_MODELVIEW );
            glColor3f(1.0F, 0.0F, 0.0F);
            drawSphere(0);

            if (allObjects)
            {
                glShadeModel(GL_FLAT);
            
                // ***** Egg 2 *****
    
                glRotatef(sphere1.fXr*2, 1.0f, 0.0f, 0.0f);
                glRotatef(0, 0.0f, 1.0f, 0.0f);
                glRotatef(sphere1.fZr, 0.0f, 0.0f, 1.0f);
            
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective(110, aspect, 0.01, 150);
        
                gluLookAt(eyeX, eyeY, eyeZ-eMod2, -centreX,
                                       -centreY, centreZ, upX, upY, upZ);
                glMatrixMode( GL_MODELVIEW );
                glColor3f(0.0F, 1.0F, 0.0F);
                drawSphere(0);
                    
                glShadeModel( GL_SMOOTH );
            
                // ***** Egg 3 *****
    
                glRotatef(0, 1.0f, 0.0f, 0.0f);
                glRotatef(sphere1.fYr*1.5f, 0.0f, 1.0f, 0.0f);
                glRotatef(sphere1.fZr, 0.0f, 0.0f, 1.0f);
            
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective(130, aspect, 0.01, 150);
        
                gluLookAt(eyeX, eyeY, eyeZ-eMod3,
                              -centreX, centreY, centreZ, upX, upY, upZ);
                glMatrixMode( GL_MODELVIEW );
                glColor3f(1.0F, 1.0F, 0.0F);
                drawSphere(0);    
        
                // ***** Egg 4 *****
                
                glRotatef(sphere1.fXr, 1.0f, 0.0f, 0.0f);
                glRotatef(sphere1.fYr, 0.0f, 1.0f, 0.0f);
                glRotatef(sphere1.fZr*2, 0.0f, 0.0f, 1.0f);
                
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective(140, aspect, 0.01, 150);
        
                gluLookAt(eyeX, eyeY, eyeZ-eMod4, centreX,
                                       -centreY, centreZ, upX, upY, upZ);
                glMatrixMode( GL_MODELVIEW );
                glColor3f(0.0F, 1.0F, 1.0F);
                drawSphere(0);
            }
            if (useTexture)
            {            
                glDisable(GL_TEXTURE_2D);
            }           
            
         }
         glPopAttrib();  // eggs
         glPopMatrix();         
    }
    else
    {
        if (loopDraw == 5)
        {
            // ***** Outside grass and sky *****
            
            glPushMatrix();
            glPushAttrib(GL_TEXTURE_BIT);
    
            // ***** Texture *****
            
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST );
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
                glTexImage2D( GL_TEXTURE_2D, 0, 3, abwide[9], abhigh[9],
                                     0, GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[9] ); // GL_BGR
    
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective(45, 1, 0.01, 150);
                gluLookAt(eyeX, eyeY, eyeMoZ, 0, 0, 0, upX, upY, upZ);
                glMatrixMode( GL_MODELVIEW );
                glLoadIdentity();          
                glShadeModel( GL_SMOOTH );
    
                glEnable( GL_TEXTURE_2D );
                glBegin( GL_QUADS );
                glNormal3f( 0.0f, 0.0f, 1.0f);
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -70.0f, -70.0f,  -140.0f );
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  70.0f, -70.0f,  -140.0f );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  70.0f,  70.0f,  -140.0f );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -70.0f,  70.0f,  -140.0f );
                glEnd();
                glDisable(GL_TEXTURE_2D);
    
            glPopAttrib();
            glPopMatrix();
        }
        lines = 0;
        if (leftRight == 0)
        {
           angleX = degree * 1.1;
        }
        else
        {  
            angleX = degree + leftRight;
            if (fabs(angleX) < 0.1) angleX = 0;
        }

        rotator = rotator + angleX;
      
        if (rotator > 360)
        {
            rotator = 0;
        } 
        if (rotator < -360)
        {
            rotator = 0;
        } 
        rotate2 = rotator;
        if (rotator < 0) rotate2 = 360 + rotator;
        if (rotate2 > 315)
        {
            viewSide = (float)cFront;
        }
        else if (rotate2 > 225)
        {
            viewSide = (float)cRight;
        }
        else if (rotate2 > 135)
        {
            viewSide = (float)cBack;
        }
        else if (rotate2 > 45)
        {
            viewSide = (float)cLeft;
        }
        else
        {
            viewSide = (float)cFront;
        }
        if (loopDraw > 4)
        {
            glClearColor( 0.9F, 0.9F, 1.0F, 1.0F );
        }
        else
        {
            glClearColor( 0.0F, 0.0F, 0.0F, 1.0F ); // ############ ##############
        }
        glRotatef(angleX, 0.0f, 1.0f, 0.0f);
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();    
        gluPerspective(90, aspect, 0.01, 5000);
        gluLookAt(0, 10.0, 50.0 + foreBack * 8, 0, 0.1, -100, 0, 1, 0); // 180+ not 50
        glMatrixMode( GL_MODELVIEW );               // -100

        glShadeModel( GL_SMOOTH );

        glColor4f(0.0F, 0.0F, 1.0F, 1.0f);

        roomWidth = 144; //144; // room width
        roomDepth = 180; // 180; // room depth
        roomHight = 96;  // room high
        wallR = 12; // right wall thickness
        wallL = 6;  // left wall thickness
        wallB = 12; // back wall thickness
        wallF = 6;  // front wall thickness
        x1 = roomWidth/2;    // right
        y1 = roomHight/2;    // top
        z1 = roomDepth/2;    // front
        x2 = x1 - roomWidth; // left
        y2 = y1 - roomHight; // bottom
        z2 = z1 - roomDepth; // back
        g1 = 0.5;     // gap

        // RGB Colours

        wall1r = 1.0f; wall1g = 1.0f; wall1b = 0.5f;
        doorr  = 0.6f; doorg  = 0.2f; doorb  = 0.0f;
        framer = 1.0f; frameg = 1.0f; frameb = 1.0f;
        fram2r = 1.0f; fram2g = 1.0f; fram2b = 1.0f;
        floorr = 1.0f; floorg = 0.7f; floorb = 0.4f;
        ceilr  = 0.9f; ceilg  = 1.0f; ceilb  = 0.9f;
        winr   = 0.6f; wing   = 0.6f; winb   = 1.0f;
        woodr  = 1.0f; woodg  = 0.7f; woodb  = 0.0f;
        plinr  = 0.3f; pling  = 0.3f; plinb  = 0.3f;
        cdorr  = 1.0f; cdorg  = 0.85f; cdorb = 0.66f;
        wtopr  = 0.6f; wtopg  = 1.0f; wtopb  = 0.9f;
        wedgr  = 1.0f; wedgg  = 0.85f; wedgb = 0.66f;
        tlegr  = 1.0f; tlegg  = 0.9f; tlegb  = 0.7f;
        tedgr  = 1.0f; tedgg  = 0.9f; tedgb  = 0.75f;
        ctopr  = 0.5f; ctopg  = 0.8f; ctopb  = 0.8f;
        clegr  = 1.0f; clegg  = 0.85f; clegb  = 0.66f;
        handr  = 1.0f; handg  = 1.0f;  handb  = 0.80f;


        if (viewSide == cRight)
        {
            rightView(x1, x2, y1, y2, z1, z2);
            frontView(x1, x2, y1, y2, z1, z2);
            centreView(x1, x2, y1, y2, z1, z2);
            rearView(x1, x2, y1, y2, z1, z2);
            leftView(x1, x2, y1, y2, z1, z2);
        }
        else if (viewSide == cLeft)
        {
            leftView(x1, x2, y1, y2, z1, z2);
            frontView(x1, x2, y1, y2, z1, z2);
            centreView(x1, x2, y1, y2, z1, z2);
            rearView(x1, x2, y1, y2, z1, z2);
            rightView(x1, x2, y1, y2, z1, z2);
        }
        else if (viewSide == cFront)
        {
            frontView(x1, x2, y1, y2, z1, z2);
            centreView(x1, x2, y1, y2, z1, z2);
            leftView(x1, x2, y1, y2, z1, z2);
            rightView(x1, x2, y1, y2, z1, z2);
            rearView(x1, x2, y1, y2, z1, z2);
        }
        else if (viewSide == cBack)
        {
            rearView(x1, x2, y1, y2, z1, z2);
            centreView(x1, x2, y1, y2, z1, z2);
            leftView(x1, x2, y1, y2, z1, z2);
            rightView(x1, x2, y1, y2, z1, z2);
            frontView(x1, x2, y1, y2, z1, z2);
        }
        lastView(x1, x2, y1, y2, z1, z2);

        shadeIt = FALSE;

        // room
        glColor3f(wall1r, wall1g, wall1b);

        sidex(0, x2, y1, y2, z1, z2); // left wall
        sidey(0, x1, y1, y2, z1, z2); // right wall
        facey(x1, x2, y1, y2, z1, 0); // front wall
        facex(x1, x2, y1, y2, z2, 0); // back wall

        if (useTexture) shadeIt = TRUE;

        glColor3f(ceilr, ceilg, ceilb);
        flaty(x1, x2, y1, 0, z1, z2); // ceiling

        // Floor
        if (useTexture) tileSurface(x1, x2, y1, y2, z1, z2, 12, 12,
                                        (int)tile5W, (int)tile5H, useTile5, 0);
        
        shadeIt = FALSE;
        glColor4f(1.0F, 1.0F, 1.0F, 1.0f);
        roomWalls(x1, x2, y1, y2, z1, z2, wallL, wallR, wallF, wallB);
    }
    
    sphere1.fXr += degree*6;
    sphere1.fYr += degree*8;
    sphere1.fZr += degree/2;

    sphere2.fXr += degree;
    sphere2.fYr += degree*1.1;

    eyeZ = eyeZ + degree/40 * whichWay5;

    eMod1 = eMod1 + degree/4.0 * whichWay1;
    eMod2 = eMod2 + degree/3.5 * whichWay2;
    eMod3 = eMod3 + degree/4.5 * whichWay3;
    eMod4 = eMod4 + degree/5.0 * whichWay4;

    if (eyeZ > eyeMoZ)
    {
        eyeZ = eyeMoZ;
        whichWay5 = - 1.0;
    }
    if (eyeZ < 0.001)
    {
        eyeZ = 0.001;
        whichWay5 = 1.0;
    }   
    if (eMod1 > 18)
    {
        whichWay1 = - 1.0;
    }
    if (eMod1 < 10)
    {
        whichWay1 = 1.0;
    }
    if (eMod2 > 17)
    {
        whichWay2 = - 1.0;
    }
    if (eMod2 < 11)
    {
        whichWay2 = 1.0;
    }

    if (eMod3 > 19)
    {
        whichWay3 = - 1.0;
    }
    if (eMod3 < 12)
    {
        whichWay3 = 1.0;
    }

    if (eMod4 > 14)
    {
        whichWay4 = - 1.0;
    }
    if (eMod4 < 10)
    {
        whichWay4 = 1.0;
    }
    glutSwapBuffers();
    frameCount = frameCount + 1;
    tempCount = tempCount + 1;
    end_time();
    if (!calibrate)
    {
        if (secs > dispSecs)
        {
            fps = tempCount / (secs - tempSecs);
            if (runMins > 0.0)
            {
                 sprintf (title, " Pass %d of %d %s %d x %d, Running at %d FPS",
                         repCount, repeats, testTitle, screenWide, screenHigh, (int)fps);
            }
            else
            {
                 sprintf (title, " OpenGL Benchmark -%s %d x %d, Running at %d FPS",
                         testTitle, screenWide, screenHigh, (int)fps);
            } 
            glutSetWindowTitle(title);    
            tempSecs = secs;
            dispSecs = dispSecs + 0.5;
            tempCount = 0.0;
        }
    }
    if (secs > runSecs2)
    {
        if (calibrate)
        {
            degree = 25.0 / frameCount;
            if (degree > 5.0) degree = 5.0;
            sprintf (title, " OpenGL Benchmark -%s %d x %d, Initial FPS = %d",
                      testTitle, screenWide, screenHigh, (int)(frameCount/secs)); 
            glutSetWindowTitle(title);
            if (runMins > 0.0)
            {
                printf(" %s Test for %d minutes\n\n", testTitle, (int)runMins);
                fprintf(outfile, " %s Test for %d minutes\n\n", testTitle, (int)runMins);
            }   
            frameCount = 0.0;
            calibrate = FALSE;
            doTime = TRUE;
            runSecs2 = runSecs;
            tempSecs = 0.0;
            tempCount = 0.0;
        }
        else if (runMins > 0.0)
        {
            fps = frameCount / secs;
            printf (" Test %d %s %d seconds, %d FPS\n", loopDraw+1, testTitle, (int)secs, (int)fps);
            fprintf (outfile, " Test %d %s %d seconds, %d FPS\n", loopDraw+1, testTitle, (int)secs, (int)fps);
            repCount = repCount + 1;
            if (repCount < repeats + 1)
            {
                frameCount = 0.0;
                doTime = TRUE;
                runSecs2 = runSecs;
                tempSecs = 0.0;
                tempCount = 0.0;         
                dispSecs = 0.5;
            }
            else
            {
               loopDraw = 6;
            }
        }
        else
        {
            fps = frameCount / secs;
            if (oneTest == 1)
            {
                printf(" %s %d FPS, %d seconds", testTitle, (int)fps, (int)runSecs);
                fprintf(outfile, " %s %d FPS, %d seconds", testTitle, (int)fps, (int)runSecs);
            }
            else
            {
                printf(" %8.1f", fps);
                fprintf(outfile, " %8.1f", fps);
            }
            fflush (outfile);
            fflush (stdout);
            runSecs2 = 0.5;
            dispSecs = 0.5;
            frameCount = 0.0;
            degree = 1.0;
            calibrate = TRUE;
            doTime = TRUE;
            tempSecs = 0.0;
            tempCount = 0.0;
            if (oneTest == 0)
            {
                loopDraw = loopDraw + 1;
            }
            else
            {
                loopDraw = 6;
            }
        }
        if (loopDraw == 6)
        {
            if (noEnd == FALSE)
            {
                printf ("\n\n");
                fprintf (outfile, "\n\n");
                local_time();
                fprintf (outfile, "                   End at %s\n", timeday);
                fprintf(outfile, "\n");
            }
            else
            {
                printf (" \n");
                fprintf (outfile, "\n");
            }
            fflush (outfile);
            fflush (stdout);
            fclose (outfile);
            free(mem);    
            exit(0);
        }
    }

} // draw_scene

void processNormalKeys(unsigned char key, int x, int y)
{
        if (key == 27)
                exit(0);
}

void processSpecialKeys(int key, int x, int y)
{
        switch(key)
        {
                case GLUT_KEY_UP :
                       foreBack = foreBack - 1;
                       break;
                case GLUT_KEY_DOWN :
                       foreBack = foreBack + 1;
                       break;
                case GLUT_KEY_LEFT :
                       leftRight = leftRight - 0.1;
                       break;
                case GLUT_KEY_RIGHT :
                       leftRight = leftRight + 0.1; 
                       break;
        }
}


void init(void)
{
    sphere1.fXr = 0.0f;
    sphere1.fYr = 0.0f;
    sphere1.fZr = 0.0f;

    setCarveTexture();

    loadBMP("opengl.bmp", 0);
    loadBMP("linux.bmp",  1);
    loadBMP("linuxc.bmp", 2);
    loadBMP("screen.bmp", 3);
    loadBMP("rock.bmp", 4);
    loadBMP("tile1.bmp", 5);
    loadBMP("tile4.bmp", 6);
    loadBMP("tile3.bmp", 7);
    loadBMP("tile5.bmp", 8);
    loadBMP("grass.bmp", 9);

    glEnable(GL_CULL_FACE);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel( GL_SMOOTH ); 

    aspect = (float)screenWide / (float)screenHigh;

}



void main(int argc, char **argv)
{
    int  i, g;
    int  param1;
    char doit[100];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    screenWide = glutGet(GLUT_SCREEN_WIDTH);
    screenHigh = glutGet(GLUT_SCREEN_HEIGHT);

    for (i=1; i<13; i=i+1)
    {
       if (argc > i)
       {
          switch (toupper(argv[i][0]))
          {
                case 'W':
                param1 = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   i = i + 1;
                   if (param1 > 0)
                   {
                      screenWide = param1;
                   }
                }
                break;
                
                case 'H':
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   i = i + 1;
                   if (param1 > 0)
                   {
                      screenHigh = param1;
                   }
                }
                break;

                case 'S':
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   i = i + 1;
                   if (param1 > 0)
                   {
                      runSecs = (double)param1;
                   }
                }
                break;

                case 'M':
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   i = i + 1;
                   if (param1 > 0)
                   {
                      runMins = (double)param1;
                   }
                }
                break;

                case 'T':
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   i = i + 1;
                   if (param1 < 1) param1 = 1;
                   if (param1 > 0)
                   {
                      loopDraw = param1 - 1;
                      if (loopDraw > 5) loopDraw = 5;
                      oneTest = 1;
                   }
                }
                break;

                case 'N':
                   sscanf(argv[i],"%3s", doit);
                   if (strcmp(doit,  "NoH") == 0) noHeading = TRUE;
                   if (strcmp(doit,  "NoE") == 0) noEnd = TRUE;
                   if (strcmp(doit,  "NOH") == 0) noHeading = TRUE;
                   if (strcmp(doit,  "NOE") == 0) noEnd = TRUE;
                break;
          }
       }
    }
    if (runMins > 0.0)
    {
        noHeading = FALSE;
        noEnd = FALSE;
        runSecs = 30;
        repeats = (int)(runMins * 2.0);
   
        if (oneTest == 0)
        {
            loopDraw = 3;
        }
    }
    outfile = fopen("videogl.txt","a+");
    if (outfile == NULL)
    {
        printf ("Cannot open results file \n\n");
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }
    if (noHeading == FALSE)
    {
        fprintf (outfile, " #####################################################################\n\n");
        printf (" #####################################################################\n\n");
        fflush(outfile);
        fflush(stdout);
        getDetails();
        printf("\nFrom File /proc/cpuinfo\n");
        printf("%s\n", configdata[0]);
        printf("\nFrom File /proc/version\n"); 
        printf("%s\n", configdata[1]);
       
        fprintf(outfile, "\nFrom File /proc/cpuinfo\n");
        fprintf(outfile, "%s\n", configdata[0]);
        fprintf(outfile, "\nFrom File /proc/version\n"); 
        fprintf(outfile, "%s\n", configdata[1]);
        fflush(outfile);
        fflush(stdout);

       
       local_time();
       if (runMins > 0.0)
       {
            printf(" ##########################################\n"); 
            printf(" GLUT OpenGL Reliability Test %s, %s\n", version, timeday);
            fprintf(outfile, " #####################################################################\n\n");
            fprintf(outfile, " OpenGL Reliability Test %s, %s\n", version, timeday);
            printf(" Display %d x %d", screenWide, screenHigh);      
            fprintf(outfile, " Display %d x %d", screenWide, screenHigh);
       }
       else if (oneTest == 1)
       {
            printf(" ##########################################\n"); 
            printf(" GLUT OpenGL Benchmark %s, %s\n", version, timeday);
            fprintf(outfile, " #####################################################################\n\n");
            fprintf(outfile, " OpenGL Benchmark %s, %s\n", version, timeday);
       }
       else
       {
            printf(" ##########################################\n"); 
            printf(" GLUT OpenGL Benchmark %s, %s\n", version, timeday);
            printf("          Running Time Approximately %d Seconds Each Test\n\n", (int)runSecs); 
            printf(" Window Size  Coloured Objects  Textured Objects  WireFrm  Texture\n");
            printf("    Pixels        Few      All      Few      All  Kitchen  Kitchen\n");
            printf("  Wide  High      FPS      FPS      FPS      FPS      FPS      FPS\n\n");
            fprintf(outfile, " #####################################################################\n\n");
            fprintf(outfile, " GLUT OpenGL Benchmark %s, %s\n", version, timeday);
            fprintf(outfile, "          Running Time Approximately %d Seconds Each Test\n\n", (int)runSecs); 
            fprintf(outfile, " Window Size  Coloured Objects  Textured Objects  WireFrm  Texture\n");
            fprintf(outfile, "    Pixels        Few      All      Few      All  Kitchen  Kitchen\n");
            fprintf(outfile, "  Wide  High      FPS      FPS      FPS      FPS      FPS      FPS\n\n");
       }
       fflush(outfile);
       fflush(stdout);
    }
    if (runMins == 0.0)
    {
        printf("%6d%6d", screenWide, screenHigh);      
        fprintf(outfile, "%6d%6d", screenWide, screenHigh);
    }
    fflush (outfile);
    fflush (stdout);

    mem = (unsigned char *)malloc(196608*11);
    if (mem == NULL)
    {
        printf ("\nmalloc Failed\n\n");
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }
    for (i=0; i<11; i++)
    {
        myTile[i] = (unsigned char *)mem + 196608 * i;
    }

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(screenWide, screenHigh);
    sprintf (title, " OpenGL Benchmark at %d x %d", screenWide, screenHigh); 
    glutCreateWindow(title);
 
    // register callbacks
    glutDisplayFunc(draw_scene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(draw_scene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    init();
    glutMainLoop();

}


void sidey(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
     x1 = x1;
                 
     glPushMatrix();
      if (shadeIt)
      {
          glBegin(GL_QUADS);
      }
      else
      {
          glBegin(GL_LINE_STRIP);
      }           
      glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
      glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z2);
      glTexCoord2f( 0.0F, 1.0F); glVertex3f( x2, y2, z1);
      glTexCoord2f( 0.0F, 0.0F); glVertex3f( x2, y1, z1);
      glTexCoord2f( 1.0F, 0.0F); glVertex3f( x2, y1, z2);
      glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z2);
      glEnd();
      lines = lines + 4;        
    glPopMatrix();
}

void sidex(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
     x1 = x1;
                 
     glPushMatrix();
      if (shadeIt)
      {
          glBegin(GL_QUADS);
      }
      else
      {
          glBegin(GL_LINE_STRIP);
      }           
      glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
      glTexCoord2f(1.0F,1.0F); glVertex3f(x2, y2, z1);
      glTexCoord2f(0.0F,1.0F); glVertex3f(x2, y2, z2);
      glTexCoord2f(0.0F,0.0F); glVertex3f(x2, y1, z2); 
      glTexCoord2f(1.0F,0.0F); glVertex3f(x2, y1, z1);   
      glTexCoord2f(1.0F,1.0F); glVertex3f(x2, y2, z1);
      glEnd();
      lines = lines + 4;        
    glPopMatrix();
}

void facey(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
     z2 = z2;

     glPushMatrix();
      if (shadeIt)
      {
          glBegin(GL_QUADS);
      }
      else
      {
          glBegin(GL_LINE_STRIP);
      }           
      glNormal3f( 0.0F, 1.0F, 0.0F);
      glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z1);
      glTexCoord2f( 0.0F, 1.0F); glVertex3f( x2, y1, z1);
      glTexCoord2f( 0.0F, 0.0F); glVertex3f( x1, y1, z1);
      glTexCoord2f( 1.0F, 0.0F); glVertex3f( x1, y2, z1);
      glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y2, z1);
      glEnd();
      lines = lines + 4;
    glPopMatrix();
}           

void facex(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
     z2 = z2;
     
     glPushMatrix();
      if (shadeIt)
      {
          glBegin(GL_QUADS);
      }
      else
      {
          glBegin(GL_LINE_STRIP);
      }           
      glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
      glTexCoord2f(1.0F,1.0F); glVertex3f(x1, y1, z1);
      glTexCoord2f(0.0F,1.0F); glVertex3f(x2, y1, z1);
      glTexCoord2f(0.0F,0.0F); glVertex3f(x2, y2, z1); 
      glTexCoord2f(1.0F,0.0F); glVertex3f(x1, y2, z1);   
      glTexCoord2f(1.0F,1.0F); glVertex3f(x1, y1, z1);
      glEnd();
      lines = lines + 4;        
    glPopMatrix();
}           


void flatx(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
     y2 = y2;
     glPushMatrix();
      if (shadeIt)
      {
          glBegin(GL_QUADS);
      }
      else
      {
          glBegin(GL_LINE_STRIP);
      }                      
      glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
      glTexCoord2f(1.0F,1.0F); glVertex3f(x1, y1, z1);
      glTexCoord2f(0.0F,1.0F); glVertex3f(x1, y1, z2);
      glTexCoord2f(0.0F,0.0F); glVertex3f(x2, y1, z2); 
      glTexCoord2f(1.0F,0.0F); glVertex3f(x2, y1, z1);   
      glTexCoord2f(1.0F,1.0F); glVertex3f(x1, y1, z1);
      glEnd();
      lines = lines + 4;
    glPopMatrix();
}

void flaty(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
     y2 = y2;
     glPushMatrix();
      if (shadeIt)
      {
          glBegin(GL_QUADS);
      }
      else
      {
          glBegin(GL_LINE_STRIP);
      }                      
      glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
      glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y1, z2);
      glTexCoord2f( 0.0F, 1.0F); glVertex3f( x1, y1, z2);
      glTexCoord2f( 0.0F, 0.0F); glVertex3f( x1, y1, z1);
      glTexCoord2f( 1.0F, 0.0F); glVertex3f( x2, y1, z1);
      glTexCoord2f( 1.0F, 1.0F); glVertex3f( x2, y1, z2);
      glEnd();
      lines = lines + 4;
    glPopMatrix();
}

void boxA(float ri, float le, float to,
           float bo, float fr, float ba)
{
    glPushMatrix();

    if (shadeIt)
    {
      glBegin(GL_QUADS);
    }
    else
    {
      glBegin(GL_LINE_STRIP);
    }
    if (doHandle) glColor3f(handr*0.9f, handg*0.9f, handb*0.9f);                                   
    glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( ri, to, fr);
    glTexCoord2f( 0.0F, 1.0F); glVertex3f( le, to, fr);
    glTexCoord2f( 0.0F, 0.0F); glVertex3f( le, bo, fr);
    glTexCoord2f( 1.0F, 0.0F); glVertex3f( ri, bo, fr);
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( ri, to, fr);
    if (doHandle) glColor3f(handr, handg, handb);                                   
    glEnd();
    lines = lines + 4;
    if (shadeIt)
    {
      glBegin(GL_QUADS);
    }
    else
    {
      glBegin(GL_LINE_STRIP);
    }                                   
    if (doHandle) glColor3f(handr*0.9f, handg*0.9f, handb*0.9f);                                   
    glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 0.8
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( le, bo, ba);
    glTexCoord2f( 0.0F, 1.0F); glVertex3f( le, to, ba);
    glTexCoord2f( 0.0F, 0.0F); glVertex3f( ri, to, ba);
    glTexCoord2f( 1.0F, 0.0F); glVertex3f( ri, bo, ba);
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( le, bo, ba);
    if (doHandle) glColor3f(handr, handg, handb);                                   
    glEnd();
    lines = lines + 4;
    if (shadeIt)
    {
      glBegin(GL_QUADS);
    }
    else
    {
      glBegin(GL_LINE_STRIP);
    }                                   
    glNormal3f( 0.0F,  1.0F, 0.0F); // 0 2 0
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( ri, to, fr);
    glTexCoord2f( 0.0F, 1.0F); glVertex3f( ri, to, ba);
    glTexCoord2f( 0.0F, 0.0F); glVertex3f( le, to, ba);
    glTexCoord2f( 1.0F, 0.0F); glVertex3f( le, to, fr);
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( ri, to, fr);
    glEnd();
    lines = lines + 4;
    if (shadeIt)
    {
      glBegin(GL_QUADS);
    }
    else
    {
      glBegin(GL_LINE_STRIP);
    }                                   
    glNormal3f( 0.0F, 1.0F, 0.0F); // 0 1 0
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( le, bo, ba);
    glTexCoord2f( 0.0F, 1.0F); glVertex3f( ri, bo, ba);
    glTexCoord2f( 0.0F, 0.0F); glVertex3f( ri, bo, fr);
    glTexCoord2f( 1.0F, 0.0F); glVertex3f( le, bo, fr);
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( le, bo, ba);
    glEnd();

    lines = lines + 4;
    if (shadeIt)
    {
      glBegin(GL_QUADS);
    }
    else
    {
      glBegin(GL_LINE_STRIP);
    }                                   
    glNormal3f( 0.0F, 1.0F, 0.0F); // 1 0 0
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( ri, to, fr);
    glTexCoord2f( 0.0F, 1.0F); glVertex3f( ri, bo, fr);
    glTexCoord2f( 0.0F, 0.0F); glVertex3f( ri, bo, ba);
    glTexCoord2f( 1.0F, 0.0F); glVertex3f( ri, to, ba);
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( ri, to, fr);
    glEnd();
    lines = lines + 4;
    if (shadeIt)
    {
      glBegin(GL_QUADS);
    }
    else
    {
      glBegin(GL_LINE_STRIP);
    }                                   
    glNormal3f( 0.0F, 1.0F, 0.0F); // 1 0 0
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( le, bo, ba);
    glTexCoord2f( 0.0F, 1.0F); glVertex3f( le, bo, fr);
    glTexCoord2f( 0.0F, 0.0F); glVertex3f( le, to, fr);
    glTexCoord2f( 1.0F, 0.0F); glVertex3f( le, to, ba);
    glTexCoord2f( 1.0F, 1.0F); glVertex3f( le, bo, ba);
    glEnd();
    lines = lines + 4;

    glPopMatrix();
}

void roomWalls(float x1, float x2, float y1,
               float y2, float z1, float z2,
               float wallL, float wallR,
               float wallF, float wallB)
{
    // right wall
    sidex(0, x1+wallR, y1, y2, z1, z2);
    facex(x1, x1+wallR, y1, y2, z1, 0);
    facex(x1, x1+wallR, y1, y2, z2, 0);

    // left wall
    sidex(0, x2-wallL, y1, y2, z1, z2);
    facex(x2, x2-wallL, y1, y2, z1, 0);
    facex(x2, x2-wallL, y1, y2, z2, 0);

    // front wall
    sidex(0, x2-wallL, y1, y2, z1+wallF, z1);
    sidex(0, x1+wallR, y1, y2, z1+wallF, z1);
    facex(x1+wallR, x2-wallL, y1, y2, z1+wallF, 0);

    // back wall
    sidex(0, x2-wallL, y1, y2, z2-wallB, z2);
    sidex(0, x1+wallR, y1, y2, z2-wallB, z2);
    facex(x1+wallR, x2-wallL, y1, y2, z2-wallB, 0);

}               



void holeA(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill, int paint)
{
    float side1, side2;
    float up1, up2;
    float back1, back2;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;

    y1 = y1;
    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = 0;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = 0;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1;
    }
    side1 = x2 + newLorF;
    side2 = x2 + newLorF + wideM;
    up1 =   y2 + floorUp;
    up2 =   y2 + floorUp  +highM;
    back1 = z1 + newIn + deepM;
    back2 = z1 + newIn;

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

    if (paint & 1)
    {
        glColor3f(wall1r*0.65f, wall1g*0.65f, wall1b*0.65f);
    }
    sidex(0, side2, up1, up2, back1, back2); // R
    sidex(0, side1, up1, up2, back2, back1); // L
    if (paint & 2)
    {
        glColor3f(wall1r*0.6f, wall1g*0.6f, wall1b*0.6f);
    }
    else if (paint & 8)
    {
        if (useTexture) shadeIt = TRUE;
        glColor3f(ceilr, ceilg, ceilb);
    }
    flatx(side1, side2, up2, 0, back1, back2); // T
    shadeIt = FALSE;
    if (fill != noBottom)
    {
        if (paint & 4)
        {
           glColor3f(wall1r*0.7f, wall1g*0.7f, wall1b*0.7f);
        }
        flatx(side1, side2, up1, 0, back2, back1); // B
    }
    glPopMatrix();

} // holeA


void frameW(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{
    float side1, side2, side3, side4, side5, side6;
    float up1, up2, up3, up4, up5, up6;
    float back1, back2, back3, back4;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;
    float newBar = 0;
    float newWide2 = 0;

    y1 = y1;
    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = inset;
        newBar = upBarIn;
        newWide2 = wide2;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = inset;
        newBar = wideM - upBarIn - 2 * wide2;
        newWide2 = -wide2;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1 + inset;
        newBar = wideM - upBarIn - 2 * wide2;
        newWide2 = -wide2;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1 + inset;
        newBar = upBarIn;
        newWide2 = wide2;        
    }
    side1 = x2 + newLorF;
    side2 = x2 + newLorF + wide2;
    side3 = x2 + newLorF + wideM - wide2;
    side4 = x2 + newLorF + wideM;
    side5 = side2 + newBar;
    side6 = side5 + newWide2;
    up1   = y2 + floorUp;
    up2   = y2 + floorUp + highM;
    up3   = y2 + floorUp + wide2;
    up4   = y2 + floorUp + highM - wide2;
    up5   = up1 + shelfHi;
    up6   = up3 + shelfHi;
    back1 = z1 + newIn;
    back2 = z1 + newIn+deepM;
    back3 = z1 + newIn+deepM*2/3;
    back4 = back2;
    
    if (fill & noBottom) up3 = up1;
    
    if (fill & newTop)
    {
        up4 = y2 + floorUp + highM - deepLS;
    }
    
    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

    if (fill & shelfIn)
    {
       glColor3f(framer*0.95f, frameg*0.95f, frameb*0.95f); // 0.7
       flatx(side3, side2, up6, 0, back2, back1);
    }
    if (fill & upBar)
    {
       glColor3f(framer*0.9f, frameg*0.9f, frameb*0.9f); // 0.65
       sidey(0, side6, up3, up4, back2, back1);
       sidex(0, side5, up3, up4, back2, back1);
    }
    glColor3f(framer*0.9f, frameg*0.9f, frameb*0.9f);  // 0.65
    sidey(0, side4, up1, up2, back2, back1); // right out
    sidex(0, side1, up1, up2, back2, back1); // left out
    sidex(0, side2, up4, up3, back2, back1); // left
    sidey(0, side3, up4, up3, back2, back1); // right
        
    glColor3f(framer*0.95f, frameg*0.95f, frameb*0.95f); // 0.7
    if (!(fill & noBottom))
    {
       flatx(side3, side2, up3, 0, back2, back1); // bottom
    }
    if (fill & !noTop)
    {
       glColor3f(framer*0.85f, frameg*0.85f, frameb*0.85f); // 0.6
       flaty(side3, side2, up4, 0, back4, back1); // top
    }    

    glColor3f(framer, frameg, frameb);
    if (fill & upBar)
    {
glColor3f(ceilr, ceilg, ceilb);
       boxA(side5, side6, up3, up4, back2, back1);
    }
    boxA(side1, side2, up1, up2, back2, back1); // right
    boxA(side3, side4, up1, up2, back2, back1); // left
               
    if (!(fill & noTop))
    {
       boxA(side3, side2, up2, up4, back4, back1); // top
    }
    if (!(fill & noBottom))
    {
       boxA(side3, side2, up1, up3, back2, back1);
    }
    if (fill & shelfIn)
    {
       boxA(side3, side2, up5, up6, back2, back1);
    }
    if (fill & glassIn)  // ############ ############## Use unfilled space
    {
//      glColor3f(winr, wing, winb);
//      facey(side3, side2, up4, up3, back3, 0);
    } 
    if (fill & backIn)
    {
      glColor3f(framer*0.8f, frameg*0.8f, frameb*0.8f); // 0.5
    } 
    glPopMatrix();

} // frameW

void door2(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{
    framer = doorr;
    frameg = doorg;
    frameb = doorb;

    if (useTexture) shadeIt = TRUE;
    
    frameW(x1, x2, y1, y2, z1, z2, type, fill);

    shadeIt = FALSE;

    framer = fram2r;    
    frameg = fram2g;
    frameb = fram2b;
}

void door3(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{
    float hi, wi, fl, ff, ins;
    
    if (useTexture) shadeIt = TRUE;
    doHandle = TRUE;
    hi = highM;
    wi = wideM;
    fl = floorUp;
    ff = fromLorF;
    ins = inset;
    glColor3f(handr, handg, handb);
    deepM = -0.5;
    wideM = 0.5;
    highM = 4.0;
    fromLorF = fromLorF + 2;
    floorUp = floorUp + handleUp;
    inset = inset - 0.75f;
    door(x1, x2, y1, y2, z1, z2, type, 0);

    inset = inset + 0.75f;
    deepM = -0.75;
    wideM = 0.5;
    highM = 0.5;
    door(x1, x2, y1, y2, z1, z2, type, 0);
    floorUp = floorUp + 3.5f;
    door(x1, x2, y1, y2, z1, z2, type, 0);
    highM = hi;
    wideM = wi;
    floorUp = fl;
    fromLorF = ff;
    inset = ins;
    doHandle = FALSE;

    if (useTexture) shadeIt = TRUE;

    framer = cdorr / 1.1f;
    frameg = cdorg / 1.1f;
    frameb = cdorb / 1.1f;
    wide2 = wide2a;
    deepM = deepMa;
    frameW(x1, x2, y1, y2, z1, z2, type, fill);
    wideM = wideM - 2 * wide2;
    highM = highM - 2 * wide2;
    fromLorF = fromLorF + wide2;
    floorUp = floorUp + wide2;
    framer = cdorr / 1.05f;
    frameg = cdorg / 1.05f;
    frameb = cdorb / 1.05f;
    wide2 = wide2b;
    deepM = deepMb;
    frameW(x1, x2, y1, y2, z1, z2, type, fill);
    wideM = wideM - 2 * wide2;
    highM = highM - 2 * wide2;
    fromLorF = fromLorF + wide2;
    floorUp = floorUp + wide2;
    framer = cdorr;
    frameg = cdorg;
    frameb = cdorb;
    wide2 = wide2c;
    deepM = deepMc;
    frameW(x1, x2, y1, y2, z1, z2, type, fill);
    wideM = wideM - 2 * wide2;
    highM = highM - 2 * wide2;
    fromLorF = fromLorF + wide2;
    floorUp = floorUp + wide2;
    framer = cdorr / 1.05f;
    frameg = cdorg / 1.05f;
    frameb = cdorb / 1.05f;
    wide2 = wide2b;
    deepM = deepMb;
    frameW(x1, x2, y1, y2, z1, z2, type, fill);
    wideM = wideM - 2 * wide2;
    highM = highM - 2 * wide2;
    fromLorF = fromLorF + wide2;
    floorUp = floorUp + wide2;
    framer = cdorr / 1.08f;
    frameg = cdorg / 1.08f;
    frameb = cdorb / 1.08f;
    wide2 = wide2d;
    deepM = deepMa;
    frameW(x1, x2, y1, y2, z1, z2, type, fill);
    wideM = wideM - 2 * wide2;
    highM = highM - 2 * wide2;
    fromLorF = fromLorF + wide2;
    floorUp = floorUp + wide2;
    deepM = deepMc;
    glColor3f(cdorr, cdorg, cdorb); 
    door(x1, x2, y1, y2, z1, z2, type, 0);

    shadeIt = FALSE;

    framer = fram2r;    
    frameg = fram2g;
    frameb = fram2b;

} // door3

void door(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{
    float side1, side2, side3, side4, up1, up2;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;
    y1 = y1;

    if (useTexture) shadeIt = TRUE;

    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = inset;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = inset;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1 + inset;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1 + inset;
    }

    side1  = x2 + newLorF; 
    side2  = x2 + newLorF + wideM;
    up2    = y2 + floorUp + highM;
    up1    = y2 + floorUp;
    side3  = z1 + newIn;
    side4  = z1 + newIn + deepM;

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

   if (fill == 0)
   {
       boxA(side1, side2, up2, up1, side3, side4);            
   }
   else
   {
      facex(side2, side1, up1, up2, side3, 0);
   }
   glPopMatrix();

   shadeIt = FALSE;


} // door

void plynth(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{

    float side1, side2, side3, side4;
    float up1, up2;
    float back1, back2, back3, back4;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;
    fill = fill;
    y1 = y1;

    if (useTexture) shadeIt = TRUE;

    glColor3f(plinr, pling, plinb);

    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = inset;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = inset;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1 + inset;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1 + inset;
    }

    side1 = x2 + newLorF;
    side2 = x2 + newLorF + wide2;
    side3 = x2 + newLorF + wideM - wide2;
    side4 = x2 + newLorF + wideM;
    up1   = y2;
    up2   = y2 + floorUp;
    back1 = z1 + newIn;
    back2 = z1 + newIn+deepM;
    back3 = back1 + wide2;
    back4 = back2 - wide2;

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

    boxA(side1, side2, up1, up2, back2, back1); // right
    boxA(side3, side4, up1, up2, back2, back1); // left           
    boxA(side3, side2, up1, up2, back3, back1); // front
    boxA(side3, side2, up1, up2, back4, back2); // back
 
    glPopMatrix();

    shadeIt = FALSE;

} // plynth

void workTop(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill, int alignD, int alignW)
{
    float side1, side2, side3, side4, up1, up2;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;
    y1 = y1;

    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = inset;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = inset;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1 + inset;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1 + inset;
    }

    side1  = x2 + newLorF; 
    side2  = x2 + newLorF + wideM;
    up2    = y2 + floorUp + highM;
    up1    = y2 + floorUp;
    side3  = z1 + newIn;
    side4  = z1 + newIn + deepM;

    if (useTexture) shadeIt = TRUE;

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

    if (fill != edge)
    {
       glPushMatrix();
       if (useTexture) tileSurface(side2, side1, up2, up2, side4,
                 side3, tile8W, tile8H, alignD, alignW, useTile8, 0); 
       shadeIt = FALSE;
       glColor3f(wedgr, wedgg, wedgb);
       boxA(side1, side2, up2, up1, side3, side4);     
       glPopMatrix();
    }
    else
    {
       glPushMatrix();
       glColor3f(wedgr*0.9f, wedgg*0.9f, wedgb*0.9f);
       facex(side1, side2, up2, up1, side3, 0);
       glColor3f(wedgr, wedgg, wedgb);
       flatx(side1, side2, up2, 0, side3, side4);
       shadeIt = FALSE;
       boxA(side1, side2, up2, up1, side3, side4);
       glPopMatrix();
    }

    glPopMatrix();

} // workTop


void table(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{
    float side1, side2, side3, side4, up1, up2;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;
    int types;
    float temp, temp2, temp3;
    fill = fill;

    if (useTexture) shadeIt = TRUE;
    
    deepM = 35;
    fromWall = fromWall + deepM;
    floorUp = 28.5;
    highM = 1.5;
    wideM = 52;
    inset = -fromWall;
    wideL = 2.5; 
    inLS  = 1.5;
    deepLS = 4.0;
    thickTB = 0.75;

    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = inset;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = inset;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1 + inset;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1 + inset;
    }
    up2    = y2 + floorUp + highM;
    up1    = y2 + floorUp;

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

    glPushMatrix(); // top
    side1  = x2 + newLorF + thickTB; 
    side2  = x2 + newLorF + wideM - thickTB;
    side3  = z1 + newIn + thickTB;
    side4  = z1 + newIn + deepM - thickTB;
    if (useTexture) tileSurface(side2, side1, up2, up2, side4,
                        side3, 7.87f, 7.87f, 0, 0, useTile8, 0); 
    shadeIt = FALSE;
    glColor3f(tedgr, tedgg, tedgb);
    boxA(side1, side2, up2, up1, side3, side4);
    if (useTexture) shadeIt = TRUE;            
    glPopMatrix();

    glPushMatrix(); // face1
    side1  = x2 + newLorF;
    side2  = x2 + newLorF + wideM;
    side3  = z1 + newIn;
    side4  = z1 + newIn + thickTB;
    glColor3f(tedgr*0.9f, tedgg*0.9f, tedgb*0.9f);
    facex(side1, side2, up2, up1, side3, 0);
    glColor3f(tedgr, tedgg, tedgb);
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    glPushMatrix(); // face2
    side3  = z1 + newIn + deepM;
    side4  = z1 + newIn + deepM - thickTB;
    glColor3f(tedgr*0.9f, tedgg*0.9f, tedgb*0.9f);
    facey(side1, side2, up2, up1, side3, 0);
    glColor3f(tedgr, tedgg, tedgb);
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    glPushMatrix(); // side1
    side1  = x2 + newLorF; 
    side2  = x2 + newLorF + thickTB;
    side3  = z1 + newIn + thickTB;
    side4  = z1 + newIn + deepM - thickTB;
    glColor3f(tedgr*0.9f, tedgg*0.9f, tedgb*0.9f);
    sidex(0, side2, up2, up1, side3, side4);
    glColor3f(tedgr, tedgg, tedgb);
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    glPushMatrix(); // side2
    side1  = x2 + newLorF + wideM; 
    side2  = x2 + newLorF + wideM - thickTB;
    glColor3f(tedgr*0.9f, tedgg*0.9f, tedgb*0.9f);
    sidey(0, side2, up2, up1, side3, side4);
    glColor3f(tedgr, tedgg, tedgb);
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    framer = tlegr;
    frameg = tlegg;
    frameb = tlegb;
    
    // legs + across
    temp = newIn + deepM - inLS - wideL;
    temp2 = deepM;
    temp3 = wideM;
    fromLorF = newLorF + inLS;
    wideM = wideM - 2 * inLS;
    highM = floorUp;
    floorUp = 0;
    wide2 = wideL;
    inset = newIn + inLS;
    deepM = wideL;
    types = noBottom + newTop;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);
    inset = temp;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);

    // across/back
    side1 = x2 + newLorF + inLS;
    side2 = side1 + deepLS;
    side3  = z1 + newIn + inLS + wideL;
    side4  = z1 + newIn + temp2 - inLS - wideL;
    up1 = y2 + highM - deepLS;
    up2 = y2 + highM;

    glPushMatrix();
    glColor3f(tlegr, tlegg, tlegb);
    boxA(side1, side2, up2, up1, side3, side4);            
    side1 = x2 + newLorF + temp3 - inLS;
    side2 = side1 - deepLS;
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    framer = fram2r;    
    frameg = fram2g;
    frameb = fram2b;
    
    glPopMatrix();
    
    shadeIt = FALSE;

} // Table

void chair(float x1, float x2, float y1,
           float y2, float z1, float z2, int type, int fill)
{
    float side1, side2, side3, side4, up1, up2;
    float angle = 0;
    float newLorF = 0;
    float newIn = 0;
    int types;
    float temp, temp2, temp3;
    fill = fill;

    if (useTexture) shadeIt = TRUE;

    deepM = 16;
    fromWall = fromWall + deepM;
    floorUp = 18.0;
    highM = 0.75;
    wideM = 18;
    chairHi = 14;
    cbackHi = 10;
    inset = -fromWall;
    wideL = 1.0; 
    deepLS = 1.5;

    if (type == cFront)
    {
        angle = 0;
        newLorF = fromLorF;
        newIn = inset;
    }
    else if (type == cBack)
    {
        angle = 180;
        newLorF = x1 - x2 - fromLorF - wideM;
        newIn = inset;
    }
    else if (type == cLeft)
    {
        angle = 270;
        newLorF = z1 - x2 - fromLorF - wideM;
        newIn = x1 - z1 + inset;
    }
    else if (type == cRight)
    {
        angle = 90;
        newLorF = z2 - x2 + fromLorF;
        newIn = x1 - z1 + inset;
    }

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);

    framer = clegr;    
    frameg = clegg;
    frameb = clegb;

    glPushMatrix(); // back
    temp = highM;
    temp3 = deepM;
    highM = chairHi;
    fromLorF = newLorF;
    wide2 = wideL;
    inset = newIn + deepM - wideL;
    deepM = wideL;
    types = noBottom + noTop;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);
    glPopMatrix();
    highM = temp;
    deepM = temp3;
    
    glPushMatrix();
    up1 = y2 + floorUp + chairHi - cbackHi;
    up2 = y2 + floorUp + chairHi;
    side1  = x2 + newLorF + wideL; 
    side2  = x2 + newLorF + wideM - wideL;
    side3  = z1 + newIn + deepM - wideL;
    side4  = z1 + newIn + deepM;
    glColor3f(ctopr*0.9f, ctopg*0.9f, ctopb*0.9f);
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();
    
    up2    = y2 + floorUp + highM;
    up1    = y2 + floorUp;

    glPushMatrix(); // seat
    side1  = x2 + newLorF + thickTB; 
    side2  = x2 + newLorF + wideM - thickTB;
    side3  = z1 + newIn + thickTB;
    side4  = z1 + newIn + deepM - thickTB;
    glColor3f(ctopr, ctopg, ctopb);
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    // legs + across
    temp = newIn + deepM - wideL;
    temp2 = deepM;
    temp3 = wideM;
    fromLorF = newLorF;
    highM = floorUp;
    floorUp = 0;
    wide2 = wideL;
    inset = newIn;
    deepM = wideL;
    types = noBottom + newTop;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);
    inset = temp;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);

    // across/back
    side1 = x2 + newLorF;
    side2 = side1 + deepLS;
    side3  = z1 + newIn + wideL;
    side4  = z1 + newIn + temp2 - wideL;
    up1 = y2 + highM - deepLS;
    up2 = y2 + highM;
    
    glPushMatrix();
    glColor3f(clegr, clegg, clegb);
    boxA(side1, side2, up2, up1, side3, side4);            
    side1 = x2 + newLorF + temp3;
    side2 = side1 - deepLS;
    boxA(side1, side2, up2, up1, side3, side4);            
    glPopMatrix();

    framer = fram2r;    
    frameg = fram2g;
    frameb = fram2b;
    
    glPopMatrix();

    shadeIt = FALSE;

} // Chair


void tileSurface(float h1, float h2, float na,
           float fix, float w1, float w2, float tileHigh,
           float tileWide, int alignW, int alignH, int tileData, int surface)
{
    float ha, hb, wa, wb;
    int i, k;
    int noHigh, noWide;
    int noHighx, noWidex;
    float yHigh, wWide;
    float th1, th2, th3, tw1, tw2, tw2a, tw3;
    float hStart, hEnd, hRem;
    float wStart, wEnd, wRem, w1a;
    na = na;
    
    yHigh = h1 - h2;
    wWide = w1 - w2;
   
    noHigh = (int)(yHigh / tileHigh);
    noWide = (int)(wWide / tileWide);
    noHighx = noHigh - 1;
    noWidex = noWide - 1;
    w1a = w1;

    wStart = 1.0f;
    wEnd  =  0.0f;
    tw2a = 0;
    if (alignW == 0)
    {
        wRem = (wWide - (float) noWide * tileWide) / 2;
        if (wRem > 0)
        {
            wStart = wRem / tileWide;
            wEnd  = 1 - wStart;
            noWide = noWide + 2;
            if (wStart < 0.5 && noWide > 2)
            {
                wStart = wStart + 0.5f;
                wEnd = wEnd - 0.5f;
                noWide = noWide - 1;
            }
            noWidex = noWide - 1;
        }
        newFL = 1 - wEnd;
        newBR = wStart;
    }
    else if (alignW & alignFrontL)
    {
        wEnd = 1 - frontLAlign;
        if (wWide > frontLAlign * tileWide)
        {
            wWide = wWide - frontLAlign * tileWide;
            noWide = (int)(wWide / tileWide);
            wRem = (wWide - (float) noWide * tileWide);
            if (wRem > 0)
            {
                wStart = wRem / tileWide;
                noWide = noWide + 1;
            }
            noWide = noWide + 1;
            noWidex = noWide - 1;
        }
        else
        {
            noWide = 1;
            noWidex = 1;
            wStart = wWide / tileWide;
        }   
        newFL = 1 - wEnd;
        newBR = wStart;
    }
    else if (alignW & alignBakR)
    {        
        wStart  = bakRAlign;
        if (wWide > bakRAlign * tileWide)
        {
            wWide = wWide - bakRAlign * tileWide;
            noWide = (int)(wWide / tileWide);
            wRem = (wWide - (float) noWide * tileWide);
            if (wRem > 0)
            {
                wEnd = 1 - wRem / tileWide;
                noWide = noWide + 1;
            }
            noWide = noWide + 1;
            noWidex = noWide - 1;
        }
        else
        {
            noWide = 1;
            noWidex = 1;
            wEnd = 1 - wWide / tileWide;
            tw2a = 0;
        }        
        newBR = wStart;
        newFL = 1 - wEnd;           
    }

    hStart = 1.0;
    hEnd  =  0.0;
    if (alignH == 0)
    {
        hRem = (yHigh - (float) noHigh * tileHigh) / 2;
        if (hRem > 0)
        {
            hStart = hRem / tileHigh;
            hEnd  = 1 - hStart;
            noHigh = noHigh + 2;
            if (hStart < 0.5 && noHigh > 2)
            {
                hStart = hStart + 0.5f;
                hEnd = hEnd - 0.5f;
                noHigh = noHigh - 1;
                
            }
            noHighx = noHigh - 1;
        }
        
    }
    else if (alignH & alignUp)
    {
        hEnd  = 1 - upAlign;        
        if (yHigh > upAlign * tileHigh)
        {
            yHigh = yHigh - upAlign * tileHigh;
            noHigh = (int)(yHigh / tileHigh);
            hRem = (yHigh - (float) noHigh * tileHigh);
            if (hRem > 0)
            {
                hStart = hRem / tileHigh;
                noHigh = noHigh + 1;
            }
            noHigh = noHigh + 1;
            noHighx = noHigh - 1;
        }
        else
        {
            noHigh = 1;
            noHighx = 1;
            hEnd  = 1 - yHigh / tileHigh;        }            
    }
    else if (alignH & alignDown)
    {
        hStart  = downAlign;
        if (yHigh > downAlign * tileHigh)
        {
            yHigh = yHigh - downAlign * tileHigh;
            noHigh = (int)(yHigh / tileHigh);
            hRem = (yHigh - (float) noHigh * tileHigh);
            if (hRem > 0)
            {
                hEnd = 1 - hRem / tileHigh;
                noHigh = noHigh + 1;
            }
            noHigh = noHigh + 1;
            noHighx = noHigh - 1;
        }
        else
        {
            noHigh = 1;
            noHighx = 1;
            hStart  = yHigh / tileHigh;
        }
    }
    
    glTexEnvi(GL_TEXTURE_ENV,
                        GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D,
                       GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                       GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                           GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                           GL_TEXTURE_WRAP_T, GL_REPEAT);   
    if (tileData == useTile5)
    {
       glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[5], abhigh[5], 0,
                     GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[5]); // GL_BGR
    }
    else if (tileData == useTile6)
    {
       glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[6], abhigh[6], 0,
                     GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[6]);  // GL_BGR
    }
    else if (tileData == useTile7)
    {
       glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[7], abhigh[7], 0,
                    GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[7]); //  GL_BGR
    }
    else if (tileData == useTile8)
    {
       glTexImage2D(GL_TEXTURE_2D, 0, 3, abwide[8], abhigh[8], 0,
                     GL_BGR_EXT, GL_UNSIGNED_BYTE, myTile[8]);  // GL_BGR
    }  
     
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glBegin(GL_QUADS);

    for (i=0; i<noHigh; i++)
    {
        th1 = 1;
        th2 = 0;
        if (i == 0)
        {
            th1 = hStart;
        }
        else if (i == noHighx)
        {
            th2 = hEnd;
        }
        th3 = th1 - th2;   
        ha = h1;
        hb = ha - tileHigh * th3;
        h1 = hb;
        w1 = w1a;
        
        for (k=0; k<noWide; k++)
        {
          tw1 = 1.0;
          tw2 = tw2a;
          if (k == 0)
          {
             tw1 = wStart;
             if (surface == cFront || surface == cLeft)
             {
                tw2 = 1 - tw1; tw1 = 1;
             }
          }
          else if (k == noWidex)
          {
             tw2 = wEnd;
             if (surface == cFront || surface == cLeft)
             {
                tw1 = 1 - tw2; tw2 = 0;
             }
          }
          tw3 = tw1 - tw2;   
          wa = w1;
          wb = wa - tileWide * tw3;
          w1 = wb;
          if (surface == cFloor)
          {
              glNormal3f( 0.0F, 1.0F, 0.0F);
              glTexCoord2f(tw1, th1); glVertex3f(ha, fix, wa);
              glTexCoord2f(tw2, th1); glVertex3f(ha, fix, wb);
              glTexCoord2f(tw2, th2); glVertex3f(hb, fix, wb); 
              glTexCoord2f(tw1, th2); glVertex3f(hb, fix, wa);
              lines = lines + 3;
          }
          else if (surface == cLeft)
          {
             glNormal3f( 0.0F, 1.0F, 0.0F);
             glTexCoord2f(tw1, th1); glVertex3f(fix, ha, wb);
             glTexCoord2f(tw2, th1); glVertex3f(fix, ha, wa);
             glTexCoord2f(tw2, th2); glVertex3f(fix, hb, wa); 
             glTexCoord2f(tw1, th2); glVertex3f(fix, hb, wb);
             lines = lines + 3;
          }
          else if (surface == cRight)
          {
             glNormal3f( 0.0F, 1.0F, 0.0F);
             glTexCoord2f(tw1, th1); glVertex3f( fix, ha, wa);
             glTexCoord2f(tw2, th1); glVertex3f( fix, ha, wb);
             glTexCoord2f(tw2, th2); glVertex3f( fix, hb, wb);
             glTexCoord2f(tw1, th2); glVertex3f( fix, hb, wa);
             lines = lines + 3;
          }
          else if (surface == cFront)
          {
             glNormal3f( 0.0F, 1.0F, 0.0F);
             glTexCoord2f(tw1, th1); glVertex3f( wb, ha, fix);
             glTexCoord2f(tw2, th1); glVertex3f( wa, ha, fix);
             glTexCoord2f(tw2, th2); glVertex3f( wa, hb, fix);
             glTexCoord2f(tw1, th2); glVertex3f( wb, hb, fix);
             lines = lines + 3;
          }
          else if (surface == cBack)
          {
             glNormal3f( 0.0F, 1.0F, 0.0F); // 0 0 1
             glTexCoord2f(tw1, th1); glVertex3f(wa, ha, fix);
             glTexCoord2f(tw2, th1); glVertex3f(wb, ha, fix);
             glTexCoord2f(tw2, th2); glVertex3f(wb, hb, fix); 
             glTexCoord2f(tw1, th2); glVertex3f(wa, hb, fix);
             lines = lines + 3;
          }                      
        }   
    }
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

} // tileSurface


void rightView(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
    int types;
    int i;
    float h1, h2, h3, r1, l1;
    float fac, fad;

    if (useTexture) shadeIt = TRUE;
    
    if (viewSide != cRight)
    {
       fromWall = 40;
       fromLorF = roomDepth - 52;
       chair(x1, x2, y1, y2, z1, z2, cRight, 0);
    }

    // Window right
    fromLorF = 46; // from front
    wideM = 60;
    floorUp = 42;
    highM = 42;
    deepM = 3;
    inset = 6;
    wide2 = 2;
    types = glassIn + upBar;
    if (useTexture) shadeIt = TRUE;
    frameW(x1, x2, y1, y2, z1, z2, cRight, types);
    deepM = wallR;
    shadeIt = FALSE; 
    holeA(x1, x2, y1, y2, z1, z2, cRight, 0, 0);
    deepM = inset;
    holeA(x1, x2, y1, y2, z1, z2, cRight, 0, 13);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 0;
    wideM = 21.75 + 20 + 80;
    deepM = 21;
    inset = - deepM;
    upAlign = 0.7f;
    downAlign = 0.7f;
    frontLAlign = 1.0f;
    workTop(x1, x2, y1, y2, z1, z2, cRight, noEdge, alignFrontL, alignUp);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 21;
    wideM = 20.75 + 80;
    deepM = thickTB;
    inset = -21.75;
    upAlign = 0.7f;
    downAlign = 0.7f;
    workTop(x1, x2, y1, y2, z1, z2, cRight, edge, 0, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 0;
    wideM = 0.75 + 21;
    deepM = thickTB;
    inset = -41.75;
    workTop(x1, x2, y1, y2, z1, z2, cRight, edge, 0, 0);

    fromLorF = 21;
    fromLorFa = 21.75;
    wideM = 20.75;
    floorUp = 4.5;
    highM = 29;
    handleUp = 23;
    inset = - wideM;
    wideMa = 20;
    deepMa = -0.25;
    deepMb = -0.5; 
    deepMc = -0.75;
    wide2c = 3;
    wide2a = 0.25;
    wide2b = 0.25;
    wide2d = 2;
    for (i=0; i<5; i++)
    {
       door3(x1, x2, y1, y2, z1, z2, cRight, 0);
       fromLorFa = fromLorFa + wideMa;
       fromLorF = fromLorFa;
       highM = 29;
       wideM = 20;
       floorUp = 4.5;
    }

    fromLorFa = 21.75;
    fromLorF = 21.75;
    floorUp = 56;
    handleUp = 2;
    wideM = 20;
    highM = 29;
    inset = -11;
    wideMa = 20;
    deepMa = -0.25;
    deepMb = -0.5; 
    deepMc = -0.75;
    wide2c = 3;
    wide2a = 0.25;
    wide2b = 0.25;
    wide2d = 2;
    door3(x1, x2, y1, y2, z1, z2, cRight, 0);
    fromLorF = 11;
    wideM = 10.75;
    highM = 29;
    floorUp = 56;
    door3(x1, x2, y1, y2, z1, z2, cRight, 0);

    if (useTexture) shadeIt = TRUE;

    fromLorF = 21.75 + 20;
    floorUp = 56;
    wideM = 0;
    deepM = 11;
    highM = 29;       
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    facex(x1, x1-deepM, y2+floorUp, y2+floorUp+highM, z1-fromLorF+wideM, 0);

    fromLorF = 21.75 + 100;
    floorUp = 4.5;
    wideM = 0;
    deepM = 21;
    highM = 29;       
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    facex(x1, x1-deepM, y2+floorUp, y2+floorUp+highM, z1-fromLorF+wideM, 0);

    // Door right
    fromLorF = 129;
    wideM = 44;
    floorUp = 0;
    highM = 82;
    deepM = 0.7f;
    inset = -0.7f;
    wide2 = 2.6f;
    if (useTexture) shadeIt = TRUE;
    frameW(x1, x2, y1, y2, z1, z2, cRight, noBottom);

    inset = -0.5;
    deepM = 1.0;
    highM = 0.6f;
    floorUp = 41;
    fromLorF = 134.75;
    wideM = 3.5;    
    doHandle = TRUE;
    glColor3f(handr, handg, handb);
    door(x1, x2, y1, y2, z1, z2, cRight, 0);
    floorUp = 40;
    fromLorF = 134;
    wideM = 1.5;
    highM = 3;
    inset = 0;
    deepM = 0.5;
    door(x1, x2, y1, y2, z1, z2, cRight, 0);
    doHandle = FALSE;

    fromLorF = 132;
    wideM = 38;
    floorUp = 0;
    highM = 79;
    wide2 = 6;
    deepM = 1.5;
    inset = 0; // wallR-deepM-2;
    door2(x1, x2, y1, y2, z1, z2, cRight, glassIn);
        
    shadeIt = FALSE;
    fromLorF = 130; // from left
    wideM = 42;  // width
    floorUp = 0;  // from floor
    highM = 81;  // height
    deepM = wallR;   // frame depth
    inset = 0;   // inset
    wide2 = 2;   // frame width
    frameW(x1, x2, y1, y2, z1, z2, cRight, noBottom);

    shadeIt = FALSE;
    
    fromLorF = 0.75;
    wideM = 41;
    shelfHi = 15;
    deepM = 21;
    inset = - deepM;;
    highM = 29;       
    floorUp = 4.5;
    wide2 = 0.75;
    types = shelfIn + backIn;
    frameW(x1, x2, y1, y2, z1, z2, cRight, types);

    fromLorF = 41.75;
    wideM = 40;
    highM = 29;       
    shelfHi = 15;
    deepM = 21;
    inset = - deepM;;
    floorUp = 4.5;
    wide2 = 0.75;
    types = shelfIn + backIn;
    frameW(x1, x2, y1, y2, z1, z2, cRight, types);
    fromLorF = 81.75;
    wideM = 20;
    frameW(x1, x2, y1, y2, z1, z2, cRight, types);
    fromLorF = 101.75;
    wideM = 20;
    frameW(x1, x2, y1, y2, z1, z2, cRight, types);

    fromLorF = 0.75;
    wideM = 41;
    floorUp = 56;
    shelfHi = 15;
    deepM = 11;
    inset = - deepM;;
    wide2 = 0.75;
    highM = 29;
    frameW(x1, x2, y1, y2, z1, z2, cRight, types);

    if (useTexture) shadeIt = TRUE;

    if (useTexture)
    {
        h2 = y2 + winBup + tile7H + 5.5f * tile6H; // top border                  
        h3 = h2;
        h1 = h2 + tile7H;
        l1 = z1; r1 = z2;
        upAlign = 1.0;
 
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile7H, tile7W, 0, alignUp, useTile7, cRight); 

        frontLAlign = newFL; // LH inset note for later use
        bakRAlign = newBR; // RH inset

        h2 = h1; h1 = y1; // top of border
        upAlign = 1.0;
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignUp, useTile6, cRight); 

        h2 = y2 + winBup; // bottom border front
        h1 = h2 + tile7H;    
        l1 = z1; r1 = l1 - 46; //  60w - 129 to d;
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile7H, tile7W, alignBakR, 0, useTile7, cRight); 
        fad = 1 - newFL;


        h1 = y2 + winBup; // below border
        h2 = y2 + 35;
        l1 = z1; r1 = z1 - 106; 
        downAlign = 1.0;
        tileSurface(h1, h2, 0, x1, l1,
                 r1,  tile6H, tile6W, alignBakR, alignDown, useTile6, cRight); 
        fac = newFL;
      
        l1 = z1; r1 = l1 - 41.75f;
        h2 = y2 + winBup + tile7H; // above bottom border front
        h1 = y2 + 56;
        upAlign = 1.0; 
        tileSurface(h1, h2, 0, x1, l1,
                 r1,  tile6H, tile6W, alignBakR, alignUp, useTile6, cRight);

        h2 = y2 + 85; h1 = h3; // below top border over cupboards
        downAlign = 0.5;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cRight);

        frontLAlign = fac;
        l1 = z1 - 46; r1 = l1 - 60; // window top
        h2 = y2 + winBup + 42; h1 = h3;
        downAlign = 0.5;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cRight);

        frontLAlign = 1 - newBR; // end cupboard
        h2 = y2 + winBup + tile7H;  h1 = h3;
        l1 = z1 - 41.75f; r1 = z1 - 46;
        downAlign = 0.5;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cRight);

        bakRAlign = 1 - fac; // end window
        l1 = z1 - 106; r1 = z1 - 129; 
        h2 = y2 + winBup + tile7H;  h1 = h3;
        downAlign = 0.5;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cRight);

        h1 = y2 + winBup; // below border
        h2 = y2 + 35; 
        r1 = z1 - 121.75f;
        downAlign = 1.0;
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cRight);

        h2 = y2 + winBup; h1 = h2 + tile7H; // border
        upAlign = 1;
        r1 = z1 - 129;
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile7H, tile7W, alignBakR, alignUp, useTile7, cRight); 

        frontLAlign = newFL;
        l1 = z1 - 20.75f - 80 - 20 - 0.75f; // by door RHS bottom       
        r1 = z1 - 129;
        h2 = y2; h1 =  y2 + winBup;
        downAlign = 1.0;
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cRight);

        bakRAlign = 1 - newFL;
        l1 = z1 - 129; r1 = l1 - 44;
        h2 = y2 + 82; h1 = h3;
        downAlign = 0.5;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cRight);

        bakRAlign = 1 - newFL;
        h2 = y2 + winBup + tile7H; h1 = h3;
        l1 = r1; r1 = z2; 
        downAlign = 0.5;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cRight);

        h2 = y2 + winBup; h1 = h2 + tile7H; // border
        upAlign = 1;
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile7H, tile7W, alignBakR, alignUp, useTile7, cRight); 

        h2 = y2; h1 = y2 + winBup; // LH door
        downAlign = 1.0;               
        tileSurface(h1, h2, 0, x1, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cRight);

        // Window
        
        h1 =  x1 + 6; h2 = x1; // down / across
        r1 = z1 - 46; l1 = r1 - 60; // window bottom - back

        downAlign = 1.0;
        bakRAlign = fad;
        tileSurface(h1, h2, y2 + winBup, y2 + winBup, r1,
             l1, tile6H, tile6W, alignBakR, alignDown, useTile6, cFloor);

        r1 =  x1 + 6; l1 = x1; // window inside
        h2 = y2 + winBup; h1 = h2 + tile7H; // border
        upAlign = 1;
        frontLAlign = 1;
        tileSurface(h1, h2, 0, z1-46, r1,
             l1, tile7H, tile7W, alignFrontL, alignUp, useTile7, cFront); 
        tileSurface(h1, h2, 0, z1-106, r1,
             l1, tile7H, tile7W, alignFrontL, alignUp, useTile7, cBack);    

        h2 = y2 + winBup + tile7H; h1 = y2 + winBup + 42 ;
        h3 = (h3 - h1) / tile6H - 0.5f;

        while (h3 > 1.0)
        {
            h3 = h3 - 1.0f;
        }
        if (h3 == 0 || h3 < 0)
        {
            h3 = 1.0;
        }
        upAlign = h3;               
        tileSurface(h1, h2, 0, z1-46, r1,
             l1, tile6H, tile6W, alignFrontL, alignUp, useTile6, cFront); 
        tileSurface(h1, h2, 0, z1-106, r1,
             l1, tile6H, tile6W, alignFrontL, alignUp, useTile6, cBack);    


    }

    if (viewSide == cRight)
    {
       fromWall = 40;
       fromLorF = roomDepth - 52;
       chair(x1, x2, y1, y2, z1, z2, cRight, 0);
    }

} // rightView


void centreView(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
    fromWall = 25;
    fromLorF = 40;
    table(x1, x2, y1, y2, z1, z2, cBack, 0);

} // centreView

void leftView(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
    int types;
    int i;
    float h1, h2, h3, r1, l1;

    if (viewSide != cLeft)
    {
       fromWall = 31;
       fromLorF = roomDepth - 52;
       chair(x1, x2, y1, y2, z1, z2, cLeft, 0);
    }    

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 21;
    wideM = 0.75 + 4 * 20;
    deepM = thickTB;
    inset = -21.75;
    upAlign = 0.7f;
    downAlign = 0.7f;
    workTop(x1, x2, y1, y2, z1, z2, cLeft, edge, 0, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 0;
    wideM = 0.75 + 21;
    deepM = thickTB;
    inset = -41.75;
    workTop(x1, x2, y1, y2, z1, z2, cLeft, edge, 0, 0);

    fromLorF = 21;
    fromLorFa = 21.75;
    wideM = 20.75;
    wideMa = 20;
    deepMa = -0.25;
    deepMb = -0.5; 
    deepMc = -0.75;
    inset = - wideM;
    highM = 29;
    handleUp = 23;       
    floorUp = 4.5;
    wide2c = 3;
    wide2a = 0.25;
    wide2b = 0.25;
    wide2d = 2;     
    glColor3f(cdorr, cdorg, cdorb);
    for (i=0; i<4; i++)
    {
       door3(x1, x2, y1, y2, z1, z2, cLeft, 0);
       fromLorFa = fromLorFa + wideMa;
       fromLorF = fromLorFa;
       highM = 29;
       wideM = 20;
       floorUp = 4.5;
    }
    wideM = 20;
    floorUp = 4.5;
    highM = 80.5;
    handleUp = 45;
    door3(x1, x2, y1, y2, z1, z2, cLeft, 0);

    fromLorFa = 21.75;
    fromLorF = 21.75;
    floorUp = 56;
    wideM = 20;
    highM = 29;
    handleUp = 2;
    inset = -11;
    wideMa = 20;
    deepMa = -0.25;
    deepMb = -0.5; 
    deepMc = -0.75;
    wide2c = 3;
    wide2a = 0.25;
    wide2b = 0.25;
    wide2d = 2;
    for (i=0; i<4; i++)
    {
       door3(x1, x2, y1, y2, z1, z2, cLeft, 0);
       fromLorFa = fromLorFa + wideMa;
       fromLorF = fromLorFa;
       highM = 29;
       wideM = 20;
       floorUp = 56;
    }
    fromLorF = 11;
    wideM = 10.75;
    highM = 29;
    floorUp = 56;
    door3(x1, x2, y1, y2, z1, z2, cLeft, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 0;
    wideM = 21.75 + 4 * 20;
    deepM = 21;
    inset = - deepM;
    upAlign = 0.7f;
    downAlign = 0.7f;
    frontLAlign = 1.0;
    workTop(x1, x2, y1, y2, z1, z2, cLeft, noEdge, alignFrontL, alignDown);

    // End panel Left tall
    wideM = -20;
    floorUp = 4.5;
    fromLorF = 21.75 + 4 * 20;
    highM = 80.5;
    deepM = 21;
    if (useTexture) shadeIt = TRUE;
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    facey(x2, x2+deepM, y2+floorUp, y2+floorUp+highM, z1-fromLorF+wideM, 0);
    wideM = 0;
    floorUp = 4.5 + 28;
    fromLorF = 21.75 + 4 * 20;
    highM = 8;
    deepM = 21;
    glColor3f(cdorr, cdorg, cdorb);
    facey(x2, x2+deepM, y2+floorUp, y2+floorUp+highM, z1-fromLorF+wideM, 0);

    wideM = 0; // tall LHS
    floorUp = 4.5 + 29;
    fromLorF = 21.75 + 4 * 20;
    highM = 22.5;
    deepM = 21;
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    facex(x2, x2+deepM, y2+floorUp, y2+floorUp+highM, z1-fromLorF+wideM, 0);

    floorUp = 4.5 + 29;
    highM = 22.5;
    wideM = 0;
    floorUp = floorUp + highM;
    highM = 29;
    fromLorF = 21.75 + 4 * 20;
    deepM = 21;
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    facex(x2+11, x2+deepM, y2+floorUp, y2+floorUp+highM, z1-fromLorF+wideM, 0);

    shadeIt = FALSE;
    
    fromLorF = 0.75;
    wideM = 41;
    shelfHi = 15;
    deepM = 21;
    inset = - deepM;;
    highM = 29;       
    floorUp = 4.5;
    wide2 = 0.75;
    types = shelfIn + backIn;
    frameW(x1, x2, y1, y2, z1, z2, cLeft, types);

    fromLorF = 41;
    wideM = 20;
    shelfHi = 15;
    deepM = 21;
    highM = 29;       
    inset = - deepM;;
    floorUp = 4.5;
    wide2 = 0.75;
    types = shelfIn + backIn;
    for (i=0; i<3; i++)
    {
       frameW(x1, x2, y1, y2, z1, z2, cLeft, types);
       fromLorF = fromLorF + wideM;
    }
    highM = 80.5;
    shelfHi = 66.5;
    frameW(x1, x2, y1, y2, z1, z2, cLeft, types);

    fromLorF = 0.75;
    wideM = 41;
    shelfHi = 15;
    floorUp = 56;
    deepM = 11;
    inset = - deepM;;
    wide2 = 0.75;
    highM = 29;
    frameW(x1, x2, y1, y2, z1, z2, cLeft, types);
    wideM = 20;
    fromLorF = 21;
    for (i=0; i<4; i++)
    {
       frameW(x1, x2, y1, y2, z1, z2, cLeft, types);
       fromLorF = fromLorF + wideM;
    }

    if (useTexture) shadeIt = TRUE;

    if (useTexture)
    {
        h2 = y2 + winBup + tile7H + 5.5f * tile6H; // top border                  
        h3 = h2;
        h1 = h2 + tile7H;
        l1 = z1; r1 = z2;
        upAlign = 1.0;

        tileSurface(h1, h2, 0, x2, l1,
             r1, tile7H, tile7W, 0, alignUp, useTile7, cLeft); 

        frontLAlign = newFL; // LH inset note for later use
        bakRAlign = newBR; // RH inset

        h2 = h1; h1 = y1; // top of border
        upAlign = 1.0;
        tileSurface(h1, h2, 0, x2, l1,
             r1, tile6H, tile6W, alignBakR, alignUp, useTile6, cLeft); 

        h2 = y2 + 85; h1 = h3; // top cupboards
        l1 = z1; r1 = l1 - 121.75f;
        downAlign = 1.0;               
        tileSurface(h1, h2, 0, x2, l1,
             r1, tile6H, tile6W, alignBakR, alignDown, useTile6, cLeft);

        h2 = y2 + winBup; // bottom border side
        h1 = h2 + tile7H;    
        l1 = r1; r1 = z2;
        upAlign = 1.0;
        tileSurface(h1, h2, 0, x2, l1,
             r1, tile7H, tile7W, alignFrontL, alignUp, useTile7, cLeft); 
    
        h2 = h1; h1 = h1 + 5.5f * tile6H; // 5.5 tiles up from border
        upAlign = 1.0;
        tileSurface(h1, h2, 0, x2, l1,
             r1, tile6H, tile6W, alignFrontL, alignUp, useTile6, cLeft); 
             
        h1 = y2 + winBup; h2 = y2; // below border
        downAlign = 1.0;
        tileSurface(h1, h2, 0, x2, l1,
             r1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cLeft); 

        h2 = y2 + winBup; // bottom border cupboards
        h1 = h2 + tile7H;    
        l1 = z1; r1 = l1 - 101.75f;
        tileSurface(h1, h2, 0, x2, l1,
             r1, tile7H, tile7W, alignBakR, 0, useTile7, cLeft); 

        h1 = y2 + winBup; // below border
        h2 = y2 + 35;
        downAlign = 1.0;
        tileSurface(h1, h2, 0, x2, l1,
                 r1,  tile6H, tile6W, alignBakR, alignDown, useTile6, cLeft); 

        h2 = y2 + winBup + tile7H; // above border
        h1 = y2 + 56;
        upAlign = 1.0; 
        tileSurface(h1, h2, 0, x2, l1,
                 r1,  tile6H, tile6W, alignBakR, alignUp, useTile6, cLeft);
    }
    if (viewSide == cLeft)
    {
       fromWall = 31;
       fromLorF = roomDepth - 52;
       chair(x1, x2, y1, y2, z1, z2, cLeft, 0);
    }    

} // leftView

void frontView(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
    int types;
    float h1, h2, h3, r1, l1;
    float thisBR, thisFL;
    
    if (viewSide != cFront)
    {
       fromWall = roomDepth - 64;
       fromLorF = 47;
       chair(x1, x2, y1, y2, z1, z2, cFront, 0);

       fromWall = roomDepth - 64;
       fromLorF = 67;
       chair(x1, x2, y1, y2, z1, z2, cFront, 0);
    }

    fromLorF = 49;
    wideM = 44;
    floorUp = 0;
    highM = 82;
    deepM = 0.7f;
    inset = -0.7f;
    wide2 = 2.6f;
    if (useTexture) shadeIt = TRUE;
    frameW(x1, x2, y1, y2, z1, z2, cFront, noBottom);

    inset = -0.5;
    deepM = 1.0;
    highM = 0.6f;
    floorUp = 41;
    fromLorF = 54.75;
    wideM = 3.5;    
    doHandle = TRUE;
    glColor3f(handr, handg, handb);
    door(x1, x2, y1, y2, z1, z2, cFront, 0);
    fromLorF = 54;
    floorUp = 40;
    wideM = 1.5;
    highM = 3;
    inset = 0;
    deepM = 0.5;
    doHandle = TRUE;
    glColor3f(handr, handg, handb);
    door(x1, x2, y1, y2, z1, z2, cFront, 0);
    doHandle = FALSE;

    floorUp = 0;
    fromLorF = 52;
    wideM = 38;
    deepM = 1.5;
    inset = 0;
    highM = 79;       
    glColor3f(doorr, doorg, doorb);
    door(x1, x2, y1, y2, z1, z2, cFront, 0);
    shadeIt = FALSE;
    fromLorF = 50;
    wideM = 42;
    floorUp = 0;
    highM = 81;
    deepM = wallF;
    inset = 0;
    wide2 = 2;   // frame width
    frameW(x1, x2, y1, y2, z1, z2, cFront, noBottom);

    if (useTexture) shadeIt = TRUE;

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 21;
    wideM = 20.75;
    deepM = 21;
    inset = - deepM;
    bakRAlign = 0.7f;
    workTop(x1, x2, y1, y2, z1, z2, cFront, noEdge, alignBakR, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = roomWidth - 21 - wideM;
    wideM = 20.75;
    deepM = 21;
    inset = - deepM;
    bakRAlign = 0.7f;       
    workTop(x1, x2, y1, y2, z1, z2, cFront, noEdge, alignBakR, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = 21.75;
    wideM = 20;
    deepM = thickTB;
    inset = -21.75;
    workTop(x1, x2, y1, y2, z1, z2, cFront, edge, 0, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    wideM = 20;
    fromLorF = roomWidth - 21.75f - wideM;
    deepM = thickTB;
    inset = -21.75;       
    workTop(x1, x2, y1, y2, z1, z2, cFront, edge, 0, 0);

    floorUp = 33.5;
    highM = 1.5;
    thickTB = 0.75;
    fromLorF = roomWidth - 21.75f;
    wideM = 21.75;
    deepM = thickTB;
    inset = -21.75 - 100;
    workTop(x1, x2, y1, y2, z1, z2, cFront, edge, 0, 0);

    fromLorF = 21;
    highM = 29;
    handleUp = 23;
    wideM = 20.75;
    floorUp = 4.5;
    inset = - wideM;
    wideMa = 20;
    deepMa = -0.25;
    deepMb = -0.5; 
    deepMc = -0.75;
    wide2c = 3;
    wide2a = 0.25;
    wide2b = 0.25;
    wide2d = 2;
    door3(x1, x2, y1, y2, z1, z2, cFront, 0);
    fromLorF = roomWidth - 21 - wideM;
    highM = 29;
    wideM = 20.75;
    fromLorF = roomWidth - 21 - wideM;
    floorUp = 4.5;
    door3(x1, x2, y1, y2, z1, z2, cFront, 0);

    fromLorF = 21;
    floorUp = 56;
    handleUp = 2;
    wideM = 20.75;
    highM = 29;
    inset = -11;
    wideMa = 20;
    deepMa = -0.25;
    deepMb = -0.5; 
    deepMc = -0.75;
    wide2c = 3;
    wide2a = 0.25;
    wide2b = 0.25;
    wide2d = 2;
    door3(x1, x2, y1, y2, z1, z2, cFront, 0);
    fromLorF = 11;
    wideM = 10.75;
    highM = 29;
    floorUp = 56;
    door3(x1, x2, y1, y2, z1, z2, cFront, 0);
    wideM = 20.75;
    fromLorF = roomWidth - 11 - 10.75f - wideM;
    floorUp = 56;
    highM = 29;
    door3(x1, x2, y1, y2, z1, z2, cFront, 0);
    wideM = 10.75;
    fromLorF = roomWidth - 11 - wideM;
    floorUp = 56;
    highM = 29;
    door3(x1, x2, y1, y2, z1, z2, cFront, 0);

    if (useTexture) shadeIt = TRUE;

    wideM = 20.75;
    floorUp = 4.5;
    fromLorF = 21;
    highM = 29;       
    deepM = 21;
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    sidey(0, x2+fromLorF+wideM, y2+floorUp, y2+floorUp+highM, z1, z1-deepM);

    wideM = 20.75;
    floorUp = 4.5;
    highM = 29;       
    deepM = 21;
    fromLorF = roomWidth - 21 - 2 * wideM;
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    sidex(0, x2+fromLorF+wideM, y2+floorUp, y2+floorUp+highM, z1, z1-deepM);

    wideM = 20.75;
    fromLorF = 21;
    floorUp = 56;
    highM = 29;       
    deepM = 11;
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    sidey(0, x2+fromLorF+wideM, y2+floorUp, y2+floorUp+highM, z1, z1-deepM);

    wideM = 20.75;
    floorUp = 56;
    deepM = 11;
    highM = 29;       
    fromLorF = roomWidth - 11 - 10.75f - 2 * wideM; // RHS
    glColor3f(cdorr*0.8f, cdorg*0.8f, cdorb*0.8f);
    sidex(0, x2+fromLorF+wideM, y2+floorUp, y2+floorUp+highM, z1, z1-deepM);

    shadeIt = FALSE;

    wideM = 20.75;
    fromLorF = 21;
    highM = 29;       
    shelfHi = 15;
    deepM = 21;
    inset = - deepM;;
    floorUp = 4.5;
    wide2 = 0.75;
    types = shelfIn + backIn;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);
    wideM = 20.75; // RHS
    fromLorF = roomWidth - 21 - wideM;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);

    fromLorF = 11;
    wideM = 30.75;
    floorUp = 56;
    deepM = 11;
    shelfHi = 15;
    inset = - deepM;;
    wide2 = 0.75;
    highM = 29;
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);
    fromLorF = roomWidth - 11 - wideM; // RHS
    frameW(x1, x2, y1, y2, z1, z2, cFront, types);
    
    if (useTexture) shadeIt = TRUE;

    if (useTexture)
    {
        r1 = x1; l1 = x2;
        h2 = y2 + winBup + tile7H + 5.5f * tile6H; // top border                  
        h3 = h2;
        h1 = h2 + tile7H;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile7H, tile7W, 0, alignUp, useTile7, cFront); 

        h2 = h1; h1 = y1; // top of border
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, 0, alignUp, useTile6, cFront); 

        frontLAlign = newFL; // LH inset note for later use
        bakRAlign = newBR; // RH inset

        h2 = y2 + 85; h1 = h3; // top cupboards LHS - R inside room
        l1 = x2; r1 = l1 + 41.75f; 
        downAlign = 1.0;               
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cFront); 

        r1 = x1; l1 = r1 - 41.75f; // top cubboard RHS
        downAlign = 1.0;               
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignBakR, alignDown, useTile6, cFront); 


        h2 = y2 + winBup; // bottom border side
        h1 = h2 + tile7H;    
        l1 = x2; r1 = l1 + 49; 
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile7H, tile7W, alignFrontL, alignUp, useTile7, cFront); 

        thisBR = newBR;
        
        l1 = r1+44; r1 = x1; // bottom border
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile7H, tile7W, alignBakR, alignUp, useTile7, cFront); 

        thisFL = newFL;

        h2 = y2 + winBup + tile7H; // above bottom border
        h1 = y2 + 56;
        upAlign = 1.0; 
        l1 = x2; r1 = l1 + 41.75f; 
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignFrontL, alignUp, useTile6, cFront);

        r1 = x1; l1 = r1 - 41.75f; // above bb RHS
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignBakR, alignUp, useTile6, cFront); 

        h1 = y2 + winBup; // below bottom border
        h2 = y2 + 35;
        downAlign = 1.0;
        l1 = x2; r1 = l1 + 41.75f; 
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cFront);

        r1 = x1; l1 = r1 - 41.75f;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignBakR, alignDown, useTile6, cFront); 

        frontLAlign = 1 - newBR;

        downAlign = 0.5;
        l1 = x2 + 41.75f; r1 = x1 - 41.75f; // above door
        h2 = y2 + 82; h1 = h3;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cFront); 


        bakRAlign = thisBR;
        
        h1 = y2 + 82;
        h2 = y2 + winBup + tile7H; // side of door
        upAlign = 1.0; 
        l1 = x2 + 41.75f; r1 = x2 + 49; 
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignBakR, alignUp, useTile6, cFront);

        downAlign = 1;
        h1 = y2 + winBup; h2 = y2;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignBakR, alignDown, useTile6, cFront);
        
        frontLAlign = thisFL;        
        h1 = y2 + 82;
        h2 = y2 + winBup + tile7H; // side of door
        upAlign = 1.0; 
        r1 = x1 - 41.75f; l1 = x2 + 49 + 44; 
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignFrontL, alignUp, useTile6, cFront);

        downAlign = 1;
        h1 = y2 + winBup; h2 = y2;
        tileSurface(h1, h2, 0, z1, r1,
             l1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cFront);

    }

    if (viewSide == cFront)
    {
       fromWall = roomDepth - 64;
       fromLorF = 47;
       chair(x1, x2, y1, y2, z1, z2, cFront, 0);

       fromWall = roomDepth - 64;
       fromLorF = 67;
       chair(x1, x2, y1, y2, z1, z2, cFront, 0);
    }
    
} // frontView

void rearView(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
    int types;
    float h1, h2, h3, r1, l1;
    float winWide, winFromL, winHigh;
    float fad;
 
    if (viewSide != cBack)
    {
       fromWall = 18;
       fromLorF = 47;
       chair(x1, x2, y1, y2, z1, z2, cBack, 0);
       fromWall = 18;
       fromLorF = 67;
       chair(x1, x2, y1, y2, z1, z2, cBack, 0);
    }

    // Window rear
    winFromL = 42;
    winWide = 60;
    winBup  = 42;
    winHigh = 42;
    fromLorF = winFromL;
    wideM = winWide;
    floorUp = winBup;
    highM = winHigh;
    deepM = 3;
    inset = 6;
    wide2 = 2; 
    upBarIn = 18;
    types = glassIn + upBar;
    if (useTexture) shadeIt = TRUE;
    frameW(x1, x2, y1, y2, z1, z2, cBack, types);
    deepM = wallB;
    shadeIt = FALSE;
    holeA(x1, x2, y1, y2, z1, z2, cBack, 0, 0);
    deepM = inset;
    holeA(x1, x2, y1, y2, z1, z2, cBack, 0, 13);

    if (useTexture)
    {
        h1 = y2 + winBup; h2 = y2; // under window
        r1 = x1; l1 = x2;
        downAlign = 1.0;

        tileSurface(h1, h2, 0, z2, r1,
                 l1,  tile6H, tile6W, 0, alignDown, useTile6, cBack); 
        frontLAlign = newFL; // LH inset note for later use
        bakRAlign = newBR; // RH inset
        
        h2 = h1; h1 = h2 + tile7H; // RHS window border
        l1 = x2 + winFromL + winWide; r1 = x1;
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z2, r1,
                 l1, tile7H, tile7W, alignBakR, alignUp, useTile7, cBack); 
        
        l1 = x2; r1 = x2 + winFromL; // LHS window border
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z2, r1,
                 l1,  tile7H, tile7W, alignFrontL, alignUp, useTile7, cBack);
        fad = 1 - newBR; 
    
        h2 = h1; h1 = h1 + 5.5f * tile6H; // 5.5 tiles up from border
        h3 = h1;
        l1 = x2 + winFromL + winWide; r1 = x1;
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z2, r1,
                 l1, tile6H,  tile6W, alignBakR, alignUp, useTile6, cBack); 
        
        l1 = x2; r1 = x2 + winFromL; // 5.5 tiles LHS up
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z2, r1,
                 l1, tile6H,  tile6W, alignFrontL, alignUp, useTile6, cBack); 
    
        frontLAlign = 1 - newBR;
    
        h2 = y2 + winHigh + winBup; // over window start half tile down
        downAlign = 0.5;
        l1 = x2 + winFromL; r1 = l1 + winWide; 
        tileSurface(h1, h2, 0, z2, r1,
                 l1, tile6H, tile6W, alignFrontL, alignDown, useTile6, cBack); 
        
    
        h2 = h1; h1 = h2 + tile7H; // top border
        r1 = x1; l1 = x2;
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z2, r1,
                 l1, tile7H, tile7W, alignBakR, alignUp, useTile7, cBack); 
    
        h2 = h1; h1 = y1; // top of border
        upAlign = 1.0;
        tileSurface(h1, h2, 0, z2, r1,
                 l1, tile6H, tile6W, alignBakR, alignUp, useTile6, cBack);    

        // WINDOW
        

        h2 = x2 + winFromL; h1 = x2 + winFromL + winWide;
        r1 = z2; l1 = z2 - 6;
        downAlign = fad;
        bakRAlign = inset / tile6W;
        tileSurface(h1, h2, y2 + winBup, y2 + winBup, r1,
             l1, tile6H, tile6W, alignBakR, alignDown, useTile6, cFloor);

        r1 =  z2 - 6; l1 = z2; // window inside
        h2 = y2 + winBup; h1 = h2 + tile7H; // border
        upAlign = 1;
        frontLAlign = 1;
        tileSurface(h1, h2, 0, x2 + winFromL, l1,
                 r1,  tile7H, tile7W, alignBakR, alignUp, useTile7, cLeft);
        tileSurface(h1, h2, 0, x2 + winFromL + winWide, l1,
                 r1,  tile7H, tile7W, alignBakR, alignUp, useTile7, cRight);

        h2 = y2 + winBup + tile7H; h1 = y2 + winBup + winHigh ;
        h3 = (h3 - h1) / tile6H - 0.5f;

        while (h3 > 1.0)
        {
            h3 = h3 - 1.0f;
        }
        if (h3 == 0 || h3 < 0)
        {
            h3 = 1.0;
        }
        upAlign = h3;               
        tileSurface(h1, h2, 0, x2 + winFromL, l1,
                 r1,  tile6H, tile6W, alignBakR, alignUp, useTile6, cLeft);
        tileSurface(h1, h2, 0, x2 + winFromL + winWide, l1,
                 r1,  tile6H, tile6W, alignBakR, alignUp, useTile6, cRight);
    }
    
    if (viewSide == cBack)
    {
       fromWall = 18;
       fromLorF = 47;
       chair(x1, x2, y1, y2, z1, z2, cBack, 0);
       fromWall = 18;
       fromLorF = 67;
       chair(x1, x2, y1, y2, z1, z2, cBack, 0);
    }
    
} // rearView


void lastView(float x1, float x2, float y1,
           float y2, float z1, float z2)
{
        int i;
        
        fromLorF = 0.75;
        wideM = 41;
        floorUp = 4.5;
        wide2 = 0.75;
        deepM = 20;
        inset = - deepM;
        plynth(x1, x2, y1, y2, z1, z2, cRight, 0);
        fromLorF = 41.75;
        wideM = 40;
        plynth(x1, x2, y1, y2, z1, z2, cRight, 0);
        fromLorF = 81.75;
        wideM = 20;
        plynth(x1, x2, y1, y2, z1, z2, cRight, 0);
        fromLorF = 101.75;
        wideM = 20;
        plynth(x1, x2, y1, y2, z1, z2, cRight, 0);

        fromLorF = 0.75;
        wideM = 41;
        floorUp = 4.5;
        wide2 = 0.75;
        deepM = 20;
        inset = - deepM;
        plynth(x1, x2, y1, y2, z1, z2, cLeft, 0);
        wideM = 20;      
        fromLorF = 41;
        for (i=0; i<3; i++)
        {
           plynth(x1, x2, y1, y2, z1, z2, cLeft, 0);
           fromLorF = fromLorF + wideM;
        }
        plynth(x1, x2, y1, y2, z1, z2, cLeft, 0);

        fromLorF = 21;
        wideM = 20.75;      
        floorUp = 4.5;
        wide2 = 0.75;
        deepM = 20;
        inset = - deepM;
        plynth(x1, x2, y1, y2, z1, z2, cFront, 0);
        wideM = 20.75;
        fromLorF = roomWidth - 21 - wideM;
        plynth(x1, x2, y1, y2, z1, z2, cFront, 0);

} // lastView




