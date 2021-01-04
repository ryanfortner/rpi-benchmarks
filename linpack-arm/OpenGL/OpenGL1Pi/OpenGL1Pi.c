/*

 Revised version 1.2 Original counting frames twice to indicate double speed in FPS
 
 Use following commands to compile and link - copied from terminal output 
 when runniing sample program hello_pi makefile. Alternative is to use makefiles

 ****************************************************************************
 COMMANDS - ensure that the whole lines are copied

 Compile

 cc -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -Wall -g -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I./ -I../libs/ilclient -I../libs/vgfont -g -c cpuidc.c -o cpuidc.o -Wno-deprecated-declarations

 cc -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -Wall -g -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I./ -I../libs/ilclient -I../libs/vgfont -g -c OpenGL1Pi.c -o OpenGL1Pi.o -Wno-deprecated-declarations

 Link

 cc -o OpenGL1Pi.bin -Wl,--whole-archive OpenGL1Pi.o cpuidc.o -L/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -L../libs/ilclient -L../libs/vgfont -Wl,--no-whole-archive -rdynamic

 ****************************************************************************
 MAKEFILES now included 

 make command executes Makefile that executes Makefile.include


 ****************************************************************************
 Run time parameters, any order;
 w, W, Wide, wide etc. - pixels wide
 h, H, High. high etc. - pixels high 
 r, R, RunTime    etc. - overall running time minutes

 ./OpenGL1Pi.bin Wide 1024, High 640, RunMinutes 5 

##########################################################################
Starting Point was:

Copyright (c) 2012, Broadcom Europe Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include "bcm_host.h"
#include "cpuidh.h"
#include <sys/time.h>

#include "GLES/gl.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"


#define BOOL int
#define FALSE 0
#define TRUE  1

typedef struct
{
   uint32_t screen_width;
   uint32_t screen_height;
// OpenGL|ES objects
   EGLDisplay display;
   EGLSurface surface;
   EGLContext context;
   GLuint tex[6];
// model rotation vector and direction
   GLfloat rot_angle_x_inc;
   GLfloat rot_angle_y_inc;
   GLfloat rot_angle_z_inc;
// current model rotation angles
   GLfloat rot_angle_x;
   GLfloat rot_angle_y;
   GLfloat rot_angle_z;
// current distance from camera
   GLfloat distance;
// pointers to texture buffers
   char *texture1;
   char *texture2;
   char *texture3;
} CUBE_STATE_T;


// ######################### Cubes #######################
 
            float vertices[] = 
            {
                -0.7f, 0.7f, 0.7f,   0.7f, 0.7f, 0.7f,   0.7f,-0.7f, 0.7f,  -0.7f,-0.7f, 0.7f,
                 0.7f, 0.7f,-0.7f,  -0.7f, 0.7f,-0.7f,  -0.7f,-0.7f,-0.7f,   0.7f,-0.7f,-0.7f,
                -0.7f, 0.7f,-0.7f,   0.7f, 0.7f,-0.7f,   0.7f, 0.7f, 0.7f,  -0.7f, 0.7f, 0.7f,
                -0.7f,-0.7f, 0.7f,   0.7f,-0.7f, 0.7f,   0.7f,-0.7f,-0.7f,  -0.7f,-0.7f,-0.7f,
                 0.7f, 0.7f, 0.7f,   0.7f, 0.7f,-0.7f,   0.7f,-0.7f,-0.7f,   0.7f,-0.7f, 0.7f,
                -0.7f, 0.7f,-0.7f,  -0.7f, 0.7f, 0.7f,  -0.7f,-0.7f, 0.7f,  -0.7f,-0.7f,-0.7f,            
            };
    
            GLbyte indices[] = 
            {
                0, 1, 2, 2,  3, 0,
                4, 5, 6, 6,  7, 4,
                8, 9,10, 10,11, 8,
               12,13,14, 14,15,12,
               16,17,18, 18,19,16,
               20,21,22, 22,23,20,
            };
                
            float normals[] = 
            {
                0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,
                0,  0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,
                0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,
                0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,  0,
                1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,
               -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,  0,  0, 
             };

            float textureCubes[] =
            {
                1,0, 1,1, 0,1, 0,0,
                1,0, 1,1, 0,1, 0,0,
                1,0, 1,1, 0,1, 0,0,
                1,0, 1,1, 0,1, 0,0,
                1,0, 1,1, 0,1, 0,0,
                1,0, 1,1, 0,1, 0,0,
            };


// ######################### Flyers #######################

            float flyer[] =
            {
              -0.15f,   0.15f,   0.15f,
               0.15f,   0.15f,   0.15f,
               0.15f,  -0.15f,   0.15f, 
              -0.15f,  -0.15f,   0.15f,   
             };

            GLbyte indicesf[] = { 0, 1, 2, 2, 3, 0}; 
            
            
            float normalsf[] = 
            {
              0.0f, 0.0f, 1.0f,
              0.0f, 0.0f, 1.0f,
              0.0f, 0.0f, 1.0f, 
              0.0f, 0.0f, 1.0f,
            };

             float textureCoords[] =
             {
                1,0, 1,1, 0,1, 0,0,
             };

// ######################### Tunnel #######################

           float vertsq1[] = 
           {
               2.0f,   1.0f, -0.020833f,  // 0, // Right Wall
               2.0f, - 1.0f, -0.020833f,  // 1,
               2.0f, - 1.0f,  0.020833f,  // 2,
               2.0f,   1.0f,  0.020833f,  // 3,    
            };
            
           float vertsq2[] = 
           {
              -2.0f,   1.0f, -0.020833f,  // Left Wall
              -2.0f, - 1.0f, -0.020833f,
              -2.0f, - 1.0f,  0.020833f,
              -2.0f,   1.0f,  0.020833f,    
            };
    
           float vertsq3[] = 
           {
               2.0f,   1.0f, -0.020833f,  // Top
              -2.0f,   1.0f, -0.020833f, 
              -2.0f,   1.0f,  0.020833f, 
               2.0f,   1.0f,  0.020833f,     
            };
    
           float vertsq4[] = 
           {
               2.0f, - 1.0f, -0.0625f,  // Bottom
              -2.0f, - 1.0f, -0.0625f,
              -2.0f, - 1.0f,  0.0625f,
               2.0f, - 1.0f,  0.0625f,    
            };
           
            GLbyte indsq1[] = { 0, 1, 2, 0, 2, 3 };


FILE *outfile;

double runSecs = 10;
long seconds, useconds;

float mRotateAngle = 0.0f;

BOOL  dowire     = FALSE;
BOOL  doTunnel   = TRUE;
BOOL  doTextures = TRUE;
BOOL  reliabilityTest = FALSE;

float re;
float gr;
float bl;
float t1;
float t2;
float t3;
float nf;
float ng;

float fj[] =
{ 1.0f,  1.0f, -1.0f,  1.0f,
  1.0f, -1.0f, -1.0f, -1.0f,    
};

int kk = 60; // 15 30 60;
int rev = 0;
int frameCount = 0;
int testCount = 0;
int cubes = 5;
int firstCount = 0;
int maxTests = 16;
int passes = 100;
int tunnel = 1;
int textureSize;
int textureDim;
int pixWide = 1280;
int pixHigh = 720;

float gi = -12.0f;
float gg = 0.091f;

double testTime;
double totalTime = 0;
int    maxTime = 10;
double fps;
double frames_ps[100];

static void init(CUBE_STATE_T *state);
static void drawScene(CUBE_STATE_T *state);
static void update_model(CUBE_STATE_T *state);
static void exit_func(void);
static volatile int terminate;
static CUBE_STATE_T _state, *state=&_state;
void drawCube();
void drawFlyer();
void drawSquare();
void setColor (int tunnel, int ii);

static void init(CUBE_STATE_T *state)
{
   int32_t success = 0;
   EGLBoolean result;
   EGLint num_config;

   static EGL_DISPMANX_WINDOW_T nativewindow;

   DISPMANX_ELEMENT_HANDLE_T dispman_element;
   DISPMANX_DISPLAY_HANDLE_T dispman_display;
   DISPMANX_UPDATE_HANDLE_T dispman_update;
   VC_RECT_T dst_rect;
   VC_RECT_T src_rect;

   static const EGLint attribute_list[] =
   {
      EGL_RED_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE, 8,
      EGL_ALPHA_SIZE, 8,
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_NONE
   };
   
   EGLConfig config;

   // get an EGL display connection
   state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   assert(state->display!=EGL_NO_DISPLAY);

   // initialize the EGL display connection
   result = eglInitialize(state->display, NULL, NULL);
   assert(EGL_FALSE != result);

   // get an appropriate EGL frame buffer configuration
   result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
   assert(EGL_FALSE != result);

   // create an EGL rendering context
   state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, NULL);
   assert(state->context!=EGL_NO_CONTEXT);

   // create an EGL window surface
   success = graphics_get_display_size(0 /* LCD */, &state->screen_width, &state->screen_height);
   assert( success >= 0 );

   state->screen_width =  pixWide;
   state->screen_height = pixHigh;

   dst_rect.x = 0;
   dst_rect.y = 0;
   dst_rect.width = state->screen_width;
   dst_rect.height = state->screen_height;
      
   src_rect.x = 0;
   src_rect.y = 0;
   src_rect.width = state->screen_width << 16;
   src_rect.height = state->screen_height << 16;        

   dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
   dispman_update = vc_dispmanx_update_start( 0 );
         
   dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
      0/*layer*/, &dst_rect, 0/*src*/,
      &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);
      
   nativewindow.element = dispman_element;
   nativewindow.width = state->screen_width;
   nativewindow.height = state->screen_height;
   vc_dispmanx_update_submit_sync( dispman_update );
      
   state->surface = eglCreateWindowSurface( state->display, config, &nativewindow, NULL );
   assert(state->surface != EGL_NO_SURFACE);

   // connect the context to the surface
   result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
   assert(EGL_FALSE != result);

   srand(123);

   glDisable(GL_DITHER);
   glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
   glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glEnableClientState( GL_VERTEX_ARRAY );
   glViewport(0, 0, (GLsizei)state->screen_width, (GLsizei)state->screen_height);
   float ratio = (float) state->screen_width / state->screen_height;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustumf(-ratio, ratio, -1, 1, 1, 50);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   GLfloat ambientLight[] = { 0.2f, 0.2f,  0.2f, 1.0f };
   GLfloat diffuseLight[] = { 1.0f, 1.0f,  1.0f, 1.0f };
   GLfloat position[]     = { 4.0f, 0.0f,  0.0f, 1.0f };
    
   glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);
   glLightfv(GL_LIGHT0, GL_POSITION,  position);

   glEnable(GL_COLOR_MATERIAL);

   glMatrixMode(GL_MODELVIEW);
   
}


static void update_model(CUBE_STATE_T *state)
{

   glLoadIdentity();

   
}




static void drawScene(CUBE_STATE_T *state)
{
            int i, j, k;

            frameCount = frameCount + 1;

            cubes = 5;
            if (testCount > 3) cubes = 50;

            if (testCount == 0 || testCount == 4  || testCount == 8 || testCount == 12)
            {
                dowire     = TRUE;
                doTunnel   = FALSE;
                doTextures = FALSE;
            }
            if (testCount == 1 || testCount == 5  || testCount == 9 || testCount == 13)
            {
                dowire     = FALSE;
                doTunnel   = FALSE;
                doTextures = FALSE;
            }
            if (testCount == 2 || testCount == 6  || testCount == 10 || testCount == 14)
            {
                dowire     = FALSE;
                doTunnel   = TRUE;
                doTextures = FALSE;
            }
            if (testCount == 3 || testCount == 7 || testCount == 11 || testCount == 15)
            {
                dowire     = FALSE;
                doTunnel   = TRUE;
                doTextures = TRUE;
            }

            if (testCount == 0 || testCount == 1 || testCount == 2 || testCount == 3)
            {  
               kk = 15;
            }
            if (testCount == 4 || testCount == 5 || testCount == 6 || testCount == 7)  
            {
               kk = 15;
            }
            if (testCount == 8 || testCount == 9 || testCount == 10 || testCount == 11)  
            {
               kk = 30;
            }
            if (testCount == 12 || testCount == 13 || testCount == 14 || testCount == 15)  
            {
               kk = 60;
            }
            if (reliabilityTest)
            {
                dowire     = FALSE;
                doTunnel   = TRUE;
                doTextures = TRUE;
                kk = 60;
                cubes = 50;
            }

            if (rev == 0)
            {
               gi = gi + gg;
            }
            else
            {
               gi = gi - gg;
            }
            if (gi > -4.0f)
            {
                rev = 1;
            }
            if (gi < -12.0f)
            { 
                rev = 0;
            }
           
            glClearColor(0.7f, 1.0f, 1.0f ,1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           
            glMatrixMode(GL_MODELVIEW);


            if (doTextures)
            {
                glTexCoordPointer(2, GL_FLOAT, 0, textureCubes);
                glEnable(GL_TEXTURE_2D);
                glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            } 

 
            j = 0;
            for (i=0; i<cubes; i++)
            {
                    nf = fj[j];
                    ng = fj[j+1];
                    j = j + 2;
                    if (j > 7) j = 0;
        
                    re = (float)((double)(rand()) / (double)2147483648.0);
                    gr = (float)((double)(rand()) / (double)2147483648.0);
                    bl = (float)((double)(rand()) / (double)2147483648.0);
                    
                    t1 = (float)((double)(rand()) / (double)2147483648.0) * 30.0f*nf; // 30.0f*nf
                    t2 = (float)((double)(rand()) / (double)2147483648.0) * 15.0f*ng;  // 15.0f*ng
                    t3 = (float)((double)(rand()) / (double)2147483648.0) * 10.0f - 10.0f+ gi;
                                                
                    for (k=0; k<kk; k++)
                    {
                    
                        glLoadIdentity();
                        glTranslatef (t1, t2, t3);
                        glRotatef(mRotateAngle, 0.0f, 1.0f, 0.0f);
                        glColor4f(re, gr, bl, 1.0f);
                        if (doTextures) glBindTexture(GL_TEXTURE_2D, state->tex[2]);
                        drawCube();
                    }
                         
            }
            if (doTextures)
            {
               glDisable(GL_TEXTURE_2D);
            }
            
            int ii = 0;

            float q =  0.3f;
            float r = -0.6f;
            float ic;
            float pass = 1.0f;

            if (doTextures)
            {
                glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
                glEnable(GL_TEXTURE_2D);
                glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            } 

            for (i=1; i<13; i=i+4)
            {
                    ic = (float)i/3;
                    glEnable(GL_COLOR_MATERIAL);
                    glLoadIdentity();
                    glTranslatef(r, q, ic+gi);
                    glRotatef(mRotateAngle*5, 0.0f, 0.0f, pass);
                    if ( dowire) glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
                    if (!dowire && pass == 1) glColor4f(1.0f, 0.4f, 0.4f, 1.0f);
                    if (!dowire && pass ==-1) glColor4f(0.2f, 0.6f, 0.2f, 1.0f);
                    if (doTextures)
                    {
                        if (pass == 1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[0]);
                        if (pass ==-1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[1]);
                    }
                    drawFlyer();
    
                    glLoadIdentity();
                    glTranslatef(-r, q, ic+1.0f+gi);
                    glRotatef(mRotateAngle*7, 0.0f, 0.0f, -pass);
                    if ( dowire) glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                    if (!dowire && pass == 1) glColor4f(0.2f, 0.6f, 0.2f, 1.0f);
                    if (!dowire && pass ==-1) glColor4f(1.0f, 0.4f, 0.4f, 1.0f);
                    if (doTextures)
                    {
                        if (pass == 1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[1]);
                        if (pass ==-1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[0]);
                    }
                    drawFlyer();
    
                    glLoadIdentity();
                    glTranslatef(r/2, -q/2, ic+2.0f+gi);
                    glRotatef(mRotateAngle*6, 0.0f, 0.0f, pass);
                    if ( dowire) glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
                    if (!dowire && pass == 1) glColor4f(0.3f, 0.3f, 1.0f, 1.0f);
                    if (!dowire && pass ==-1) glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
                    if (doTextures)
                    {
                        if (pass == 1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[0]);
                        if (pass ==-1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[1]);
                    }
                    drawFlyer();
    
                    glLoadIdentity();
                    glTranslatef(-r/2, -q/2, ic+3.0f+gi);
                    glRotatef(mRotateAngle*8, 0.0f, 0.0f, -pass);
                    if ( dowire) glColor4f(0.5f, 0.0f, 0.5f, 1.0f);
                    if (!dowire && pass == 1) glColor4f(0.3f, 0.3f, 1.0f, 1.0f);
                    if (!dowire && pass ==-1) glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
                    if (doTextures)
                    {
                        if (pass == 1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[1]);
                        if (pass ==-1.0f) glBindTexture(GL_TEXTURE_2D, state->tex[0]);
                    }
                    drawFlyer();
               
                if (pass == 1)
                {
                    pass = -1;
                }
                else
                {
                   pass = 1;
                }                  
           }
           if (doTextures)
           {
              glDisable(GL_TEXTURE_2D);
           }

           if (doTunnel)
           {                     
              for (tunnel=1; tunnel<5; tunnel++)
              {
                for (i=1; i<17; i++)
                {
                    float dd = ((float) i) / 8 - 0.125f;
                    
                    glEnable(GL_COLOR_MATERIAL);
                    glLoadIdentity();
                    glTranslatef(0.0f, 0.0f, gi+11.0f+dd);
                    setColor (tunnel, ii);              
                    drawSquare();              

                    glLoadIdentity();
                    glTranslatef(0.0f, 0.0f, gi+9.0f+dd);               
                    setColor (tunnel, ii);
                    drawSquare();              
                     
                    glLoadIdentity();
                    glTranslatef(0.0f, 0.0f, gi+7.0f+dd);               
                    setColor (tunnel, ii);              
                    drawSquare();              
     
                    glLoadIdentity();
                    glTranslatef(0.0f, 0.0f, gi+5.0f+dd);               
                    setColor (tunnel, ii);              
                    drawSquare();              
    
                    glLoadIdentity();
                    glTranslatef(0.0f, 0.0f, gi+3.0f+dd);               
                    setColor (tunnel, ii);              
                    drawSquare();

                    if (ii == 0)
                    {
                        ii = 1;
                    }
                    else
                    {
                         ii = 0;
                    }                        
                }
              }
            }

    mRotateAngle = mRotateAngle + 2.0f;
    if (mRotateAngle > 360.0f) mRotateAngle = 0.0f;

    eglSwapBuffers(state->display, state->surface);
   
    end_time();
    testTime = secs;
    fps = (double)frameCount / testTime;
    
    if (testTime > (double)maxTime)
    {
       frames_ps[testCount] = fps;
       testCount = testCount + 1;
       printf(" Test %2d  %6.2f seconds, %6.2f FPS\n", testCount, testTime, fps);
       start_time();
       frameCount = 0;
       totalTime = totalTime + testTime;
    } 
}

void drawCube()
{
            glFrontFace(GL_CW); 
            glVertexPointer(3, GL_FLOAT, 0, vertices);
            glNormalPointer(GL_FLOAT, 0, normals);
            if (dowire)
            {
               glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_BYTE, indices);
            }
            else
            {
               glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
            }
}

void drawFlyer()
{
            
        glFrontFace(GL_CW);
        glVertexPointer(3, GL_FLOAT, 0, flyer);
        glNormalPointer(GL_FLOAT, 0, normalsf);
        if (dowire) 
        {
            glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_BYTE, indicesf);
        }   
        else 
        {
            glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_BYTE, indicesf);
        }

}



void drawSquare()
{
        
        if (tunnel == 1) glVertexPointer(3, GL_FLOAT, 0, vertsq1);
        if (tunnel == 2) glVertexPointer(3, GL_FLOAT, 0, vertsq2);
        if (tunnel == 3) glVertexPointer(3, GL_FLOAT, 0, vertsq3);
        if (tunnel == 4) glVertexPointer(3, GL_FLOAT, 0, vertsq4);
        if (dowire) 
        {
            glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_BYTE, indsq1);
        } 
        else 
        {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indsq1);
        }
        
}


void setColor (int tunnel, int ii)
{
    if (ii == 0)
    {
        if (tunnel == 1) glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        if (tunnel == 2) glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        if (tunnel == 3) glColor4f(0.0f, 0.4f, 1.0f, 1.0f);
        if (tunnel == 4) glColor4f(0.0f, 0.8f, 0.0f, 1.0f);
    }
    else
    {
        if (tunnel == 1) glColor4f(1.0f, 0.7f, 0.0f, 1.0f);
        if (tunnel == 2) glColor4f(1.0f, 0.7f, 0.0f, 1.0f);
        if (tunnel == 3) glColor4f(0.0f, 0.6f, 1.0f, 1.0f);
        if (tunnel == 4) glColor4f(0.0f, 0.6f, 0.0f, 1.0f);
    }
}



static void exit_func(void)
// Function to be passed to atexit().
{
   // clear screen
   glClear( GL_COLOR_BUFFER_BIT );
   eglSwapBuffers(state->display, state->surface);

   // Release OpenGL resources
   eglMakeCurrent( state->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
   eglDestroySurface( state->display, state->surface );
   eglDestroyContext( state->display, state->context );
   eglTerminate( state->display );

   // release texture buffers
   free(state->texture1);
   free(state->texture2);
   free(state->texture3);
} // exit_func()

int runit()
{
   FILE *texFile;
   size_t read;
   
   textureSize = 128 * 128 * 3;
   textureDim = 128;

   
   bcm_host_init();

   // Clear application state
   memset( state, 0, sizeof( *state ) );
      
   init(state);

   state->texture1 = malloc(textureSize);
   if (state->texture1 == NULL)
   {
       printf (" Cannot allocate memory for texture1\n");
       exit (1);
   }

   state->texture2 = malloc(textureSize);
   if (state->texture2 == NULL)
   {
       free(state->texture1);
       printf (" Cannot allocate memory for texture2\n");
       exit (1);
   }

   state->texture3 = malloc(textureSize);
   if (state->texture3 == NULL)
   {
       free(state->texture1);
       free(state->texture1);
       printf (" Cannot allocate memory for texture3\n");
       exit (1);
   }


   texFile = fopen("opengl.raw", "rb");
   if (texFile == NULL)
   {
       free(state->texture1);
       free(state->texture2);
       free(state->texture3);
       printf (" Cannot open file opengl.raw\n");
       exit (1);
   }
   
   read = fread(state->texture1, 1, textureSize, texFile);
   if (read != textureSize)
   {
       free(state->texture1);
       free(state->texture2);
       free(state->texture3);
       printf (" Error reading opengl.raw\n");
       fclose (texFile);
   }
   fclose (texFile);

   texFile = fopen("benchmk.raw", "rb");
   if (texFile == NULL)
   {
       free(state->texture1);
       free(state->texture2);
       free(state->texture3);
       printf (" Cannot open file a128.raw\n");
       exit (1);
   }
   
   read = fread(state->texture2, 1, textureSize, texFile);
   if (read != textureSize)
   {
       free(state->texture1);
       free(state->texture2);
       free(state->texture3);
       printf (" Error reading opengl.raw\n");
       fclose (texFile);
   }
   fclose (texFile);


   texFile = fopen("raspi.raw", "rb");
   if (texFile == NULL)
   {
       free(state->texture1);
       free(state->texture2);
       free(state->texture3);
       printf (" Cannot open file opengl.raw\n");
       exit (1);
   }
   
   read = fread(state->texture3, 1, textureSize, texFile);
   if (read != textureSize)
   {
       free(state->texture1);
       free(state->texture2);
       free(state->texture3);
       printf (" Error reading opengl.raw\n");
       fclose (texFile);
   }
   fclose (texFile);


   glGenTextures(3, &state->tex[0]);

   glBindTexture(GL_TEXTURE_2D, state->tex[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureDim, textureDim, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->texture1);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   glBindTexture(GL_TEXTURE_2D, state->tex[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureDim, textureDim, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->texture2);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   glBindTexture(GL_TEXTURE_2D, state->tex[2]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureDim, textureDim, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->texture3);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   glTexCoordPointer(2, GL_FLOAT, 0, textureCubes);

   glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   start_time();
   update_model(state);

   do   
   {
      drawScene(state);
   }
   while (testCount < maxTests); 
   glFlush();
   glFinish();

   exit_func();
   
   return 0;
}


int main(int argc, char *argv[])
{
    int param;
    int i;
    int nopause = 1;
    int minutes;

    for (i=1; i<7; i=i+2)
    {
        if (argc > i)
        {
            switch (toupper(argv[i][0]))
            {

               case 'W':
                param = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param);
                   if (param > 0) pixWide = param;
                }
                break;

               case 'H':
                param = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param);
                   if (param > 0) pixHigh = param;
                }
                break;

               case 'R':
                reliabilityTest = TRUE;
                param = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param);
                   if (param > 0)
                   {
                       minutes = param;
                       maxTime = (60 * minutes + 15) / 16;
                   }
                }
                break;
            }
        }
    }
   
    getDetails();

    outfile = fopen("OpenGL1Pi.txt","a+");
    if (outfile == NULL)
    {
       printf ("Cannot open results file \n\n");
       exit (0);
    }

    local_time();

    fprintf (outfile, "\n"); 
    fprintf (outfile, "##############################################\n\n");
    fprintf (outfile, " Raspberry Pi OpenGL ES Benchmark 1.2, %s\n", timeday);
    if (reliabilityTest)
    {
        fprintf (outfile, " Reliability Mode 16 Tests of %d Seconds\n\n", maxTime);
        printf(" Reliability Mode 16 Tests of %d Seconds\n\n", maxTime);  
    }
    printf(" Start Time %s\n", timeday);
    runit();
   
    local_time();
    printf(" Run Time %6.2f seconds,   %s\n", totalTime, timeday);

    printf("           --------- Frames Per Second --------\n");
    fprintf(outfile, "           --------- Frames Per Second --------\n");
    if (reliabilityTest)
    {
        printf(" Triangles            All Textured\n\n");
        printf("  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
               "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
               "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
               "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n\n"
               "      Screen Pixels %d Wide %d High\n",
               frames_ps[0],  frames_ps[1],  frames_ps[2],  frames_ps[3],
               frames_ps[4],  frames_ps[5],  frames_ps[6],  frames_ps[7],
               frames_ps[8],  frames_ps[9],  frames_ps[10], frames_ps[11],
               frames_ps[12], frames_ps[13], frames_ps[14], frames_ps[15],
               pixWide, pixHigh);
    
        fprintf(outfile, " Triangles            All Textured\n\n");
        fprintf(outfile, "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
                         "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
                         "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
                         "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n\n"
                         "      Screen Pixels %d Wide %d High\n\n",
               frames_ps[0],  frames_ps[1],  frames_ps[2],  frames_ps[3],
               frames_ps[4],  frames_ps[5],  frames_ps[6],  frames_ps[7],
               frames_ps[8],  frames_ps[9],  frames_ps[10], frames_ps[11],
               frames_ps[12], frames_ps[13], frames_ps[14], frames_ps[15],
               pixWide, pixHigh);
    }
    else
    {
        printf(" Triangles WireFrame   Shaded  Shaded+ Textured\n\n");
        printf("    900+    %7.2f  %7.2f  %7.2f  %7.2f\n"
               "   9000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
               "  18000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
               "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n\n"
               "      Screen Pixels %d Wide %d High\n",
               frames_ps[0],  frames_ps[1],  frames_ps[2],  frames_ps[3],
               frames_ps[4],  frames_ps[5],  frames_ps[6],  frames_ps[7],
               frames_ps[8],  frames_ps[9],  frames_ps[10], frames_ps[11],
               frames_ps[12], frames_ps[13], frames_ps[14], frames_ps[15],
               pixWide, pixHigh);
    
        fprintf(outfile, " Triangles WireFrame   Shaded  Shaded+ Textured\n\n");
        fprintf(outfile, "    900+    %7.2f  %7.2f  %7.2f  %7.2f\n"
                         "   9000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
                         "  18000+    %7.2f  %7.2f  %7.2f  %7.2f\n"
                         "  36000+    %7.2f  %7.2f  %7.2f  %7.2f\n\n"
                         "      Screen Pixels %d Wide %d High\n\n",
               frames_ps[0],  frames_ps[1],  frames_ps[2],  frames_ps[3],
               frames_ps[4],  frames_ps[5],  frames_ps[6],  frames_ps[7],
               frames_ps[8],  frames_ps[9],  frames_ps[10], frames_ps[11],
               frames_ps[12], frames_ps[13], frames_ps[14], frames_ps[15],
               pixWide, pixHigh);
    }
    fprintf(outfile, "      End Time %s\n", timeday);
    fflush(outfile);
    fprintf (outfile, " SYSTEM INFORMATION\n\nFrom File /proc/cpuinfo\n");
    fprintf (outfile, " %s \n", configdata[0]);
    fprintf (outfile, "\n From File /proc/version\n");
    fprintf (outfile, " %s \n", configdata[1]);
    fprintf (outfile, "\n");
    fflush(outfile);
    
    printf ("\n");
    printf ("A new results file, OpenGL1Pi.txt,  will have been created in the same\n");
    printf ("directory as the .BIN files, if one did not already exist.\n\n");
    
    if (nopause)
    {
    char moredata[1024];
    printf("Type additional information to include in OpenGL1Pi.txt - Press Enter\n");
    if (fgets (moredata, sizeof(moredata), stdin) != NULL)
             fprintf (outfile, "Additional information - %s\n", moredata);
    } 
    
    fflush(outfile);
    fclose (outfile);
    
    return 0;
}



