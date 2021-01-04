// Compile   - javac whets2.java
// Run Linux -  appletviewer -J-Djava.security.policy=po.policy whetjava.html


import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.text.*;
import java.net.*;
import java.lang.*;

public class whets2 extends Applet 
{
    private double TimeUsed;
    private float x,y,z;
    private float[] e1 = new float[4];
    private float Check;
    private float mwips;
    private double[] loop_time = new double[9];
    private double[] loop_mops = new double[9];
    private double[] loop_mflops = new double[9];
    private float[] results = new float[9];
    private String[] titles = new String[9];
    private String[] headings = new String[6];

    private int[] num = new int[4];

    private int wwidth  = 500;
    private int wheight = 325;

    private String xout;
    private double runTime;
    private double mflops;
    private int w1, w2, w3, w4, w5, h1;
    private int section;

    Font font1;
    Font font2;
    Font font3;
     
    private int x100 = 100;

    public void paint(Graphics g) 
    {
        section = 0;
        h1 = 20;
        display(g);              

        headings[0] = "Test\0";
        headings[1] = "Result\0";
        headings[2] = "MFLOPS\0";
        headings[3] = "MOPS\0";
        headings[4] = "millisecs\0";
        
        h1 = h1 + 30;
        TimeUsed = 0.0; 
        for (section=1; section<9; section++)
        {
            whetstones();
            display(g);
        }     
    }

    public void whetstones() 
    {
        double startTime;
        double endTime;
        int i, j, k, l, ix, xtra, n1mult;
        
        float t  =  0.49999975f;
        float t0 = t;  
        float t1 = 0.50000025f;
        float t2 = 2.0f;

        int n1 = 12*x100;
        int n2 = 14*x100;
        int n3 = 345*x100;
        int n4 = 210*x100;
        int n5 = 32*x100;
        int n6 = 899*x100;
        int n7 = 616*x100;
        int n8 = 93*x100;
               
        num[0] = 0;
        num[1] = 1;
        num[2] = 2;
        num[3] = 3;

        w1 = 10;
        w2 = 150;
        w3 = 260;     
        w4 = 330;
        w5 = 420;
                
        switch (section)
        {
        case 1:

        // Section 1, Array elements
        
        n1mult = 10;
        
        e1[0] =  1.0f;
        e1[1] = -1.0f;
        e1[2] = -1.0f;
        e1[3] = -1.0f;                   

        runTime = 0.0;
        xtra = 10;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0; i<n1*n1mult; i++)
                {
                    e1[0] = (e1[0] + e1[1] + e1[2] - e1[3]) * t;
                    e1[1] = (e1[0] + e1[1] - e1[2] + e1[3]) * t;
                    e1[2] = (e1[0] - e1[1] + e1[2] + e1[3]) * t;
                    e1[3] = (-e1[0] + e1[1] + e1[2] + e1[3]) * t;
                }
                t = 1.0f - t;
                if (ix == 0) results[section] = e1[3];
            }
            t =  t0;                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        
        Check = Check + e1[3];
        loop_time[section] = runTime / (double)n1mult / (double)xtra;
        loop_mflops[section] = (double)(n1*16) / 1000000.0 / loop_time[section];
        loop_mops[section] = 0.0;
        titles[section] = "N1 floating point\0";
        TimeUsed = TimeUsed + loop_time[section];
        break;

        case 2:
 
        // Section 2, Array as parameter

        runTime = 0.0;
        xtra = 10;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0; i<n2; i++)
                {   
                      pa(e1,t,t2);
                }
                t = 1.0f - t;
                if (ix == 0) results[section] = e1[3];
            }
            t =  t0;                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + e1[3];
        loop_time[section] = runTime / (double)xtra;
        loop_mflops[section] = (double)(n2*96) / 1000000.0 / loop_time[section];
        loop_mops[section] = 0.0;
        titles[section] = "N2 floating point\0";
        TimeUsed = TimeUsed + loop_time[section];
        break;

        case 3:

        // Section  3, Conditional jumps

        // num[0] to num[3] instead of 1, 2, 3 and 4
        
        runTime = 0.0;
        xtra = 10;
        j = 1;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0; i<n3; i++)
                {
                    if (j == 1)
                    {       
                       j = num[2];
                    }
                    else
                    {
                       j = num[3];
                    }
                    if (j > 2)
                    {
                       j = num[0];
                    }
                    else
                    {
                       j = num[1];
                    }
                    if (j < 1)
                    {
                       j = num[1];
                    }
                    else
                    {
                       j = num[0];
                    }
                }
                if (ix == 0) results[section] = (float)j;
            }                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + (float)j;
        loop_time[section] = runTime / (double)xtra;
        loop_mflops[section] = 0.0;
        loop_mops[section] = (double)(n3*3) / 1000000.0 / loop_time[section];
        titles[section] = "N3 if then else \0";
        TimeUsed = TimeUsed + loop_time[section];
        break;

        case 4:
        
        // Section 4, Integer arithmetic
                
        // num[1] to num[3] instead of j, k, l for 1, 2, 3

        j = 1;
        k = 2;
        l = 3;
        runTime = 0.0;
        xtra = 10;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0; i<n4; i++)
                {
                     j = num[1] *(k-j)*(l-k);
                     k = num[3] * k - (l-j) * k;
                     l = (l-k) * (num[2]+j);
                     e1[l-2] = j + k + l;
                     e1[k-2] = j * k * l;
                }
                if (ix == 0) results[section] = e1[0]+e1[1];
            }                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + e1[0]+e1[1];
        loop_time[section] = runTime / (double)xtra;

        loop_mflops[section] = 0.0;
        loop_mops[section] = (double)(n4*15) / 1000000.0 / loop_time[section];
        titles[section] = "N4 fixed point\0";
        TimeUsed = TimeUsed + loop_time[section];
        break;

        case 5:
        
        // Section 5, Trig function        
                 
        x = 0.5f;
        y = 0.5f;
        runTime = 0.0;
        xtra = 10;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {

                for(i=1; i<n5; i++)
                {
                    x = (float)(t*Math.atan(t2*Math.sin(x)*Math.cos(x)/
                            (Math.cos(x+y)+Math.cos(x-y)-1.0)));
                    y = (float)(t*Math.atan(t2*Math.sin(y)*Math.cos(y)/
                             (Math.cos(x+y)+Math.cos(x-y)-1.0)));
                }
                t = 1.0f - t;
                if (ix == 0) results[section] = y;
            }
            t =  t0;                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + y;
        loop_time[section] = runTime / (double)xtra;
        loop_mflops[section] = 0.0;
        loop_mops[section] = (double)(n5*26) / 1000000.0 / loop_time[section];
        titles[section] = "N5 sin,cos etc.\0";
        TimeUsed = TimeUsed + loop_time[section];
        break;

        case 6:

       // Section 6, Procedure calls
       
        x = 1.0f;
        y = 1.0f;
        z = 1.0f;
        runTime = 0.0;
        xtra = 10;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0; i<n6; i++)
                {
                         p3(t,t1,t2);
                }
                if (ix == 0) results[section] = z;
            }
            t =  t0;                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + z;
        loop_time[section] = runTime / (double)xtra;
        loop_mflops[section] = (double)(n6*6) / 1000000.0 / loop_time[section];
        loop_mops[section] = 0.0;
        titles[section] = "N6 floating point\0";
        TimeUsed = TimeUsed + loop_time[section];        
        break;

        case 7:
       
       // Section 7, Array refrences 
       
        j = 0;
        k = 1;
        l = 2;
        e1[0] = 1.0f;
        e1[1] = 2.0f;
        e1[2] = 3.0f;
        runTime = 0.0;
        xtra = 10;        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0;i<n7;i++)
                {
                    po(e1,j,k,l);
                }
                if (ix == 0) results[section] = e1[2];
            }
            t =  t0;                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + e1[2];
        loop_time[section] = runTime / (double)xtra;
        loop_mflops[section] = 0.0;
        loop_mops[section] = (double)(n7*3) / 1000000.0 / loop_time[section];
        titles[section] = "N7 assignments\0";
        TimeUsed = TimeUsed + loop_time[section];       
        break;

        case 8:
       
       // Section 8, Standard functions      

        x = 0.75f;
        runTime = 0.0;
        xtra = 10;
        do
        {
            if (runTime > 0.2)
            {
                xtra = xtra * 5;
            }
            else if (runTime > 0.5)
            {
                xtra = xtra * 2;
            }
            else
            {
                xtra = xtra * 10;
            }
            startTime = getTime();
            for (ix=0; ix<xtra; ix++)
            {
                for(i=0; i<n8; i++)
                {
                    x = (float)(Math.sqrt(Math.exp(Math.log(x)/t1)));
                }
                if (ix == 0) results[section] = x;
            }
            t =  t0;                    
            endTime = getTime();
            runTime = endTime - startTime;
        }
        while (runTime < 1.0);
        Check = Check + x;
        loop_time[section] = runTime / (double)xtra;
        loop_mflops[section] = 0.0;
        loop_mops[section] = (double)(n8*4) / 1000000.0 / loop_time[section];
        titles[section] = "N8 exp,sqrt etc.\0";
        TimeUsed = TimeUsed + loop_time[section];
        mwips = (float)x100 / (float)(10.0 * TimeUsed);
        break;
        }              
    }

    void po(float e1[], int j, int k, int l)
    {
        e1[j] = e1[k];
        e1[k] = e1[l];
        e1[l] = e1[j];
        return;
    }

    void p3(float t, float t1, float t2)
    {
        x = y;
        y = z;
        x = t * (x + y);
        y = t1 * (x + y);
        z = (x + y)/t2;
        return;
    }

    void pa(float e[], float t, float t2)
    { 
        int j;
        for(j=0;j<6;j++)
        {
            e[0] = (e[0]+e[1]+e[2]-e[3])*t;
            e[1] = (e[0]+e[1]-e[2]+e[3])*t;
            e[2] = (e[0]-e[1]+e[2]+e[3])*t;
            e[3] = (-e[0]+e[1]+e[2]+e[3])/t2;
        }
        return;
    }

    public void init()
    {
        setBackground(Color.blue);
    }

    public void stop()
    {
    }

    void display(Graphics g)
    {
        if (section == 0)
        {
            Format formatter;
            font1 = new Font("CourierNew", Font.PLAIN, 12);
            font2 = new Font("CourierNew", Font.BOLD, 14);
            font3 = new Font("CourierNew", Font.PLAIN, 10);
            Calendar c = Calendar.getInstance();
            Date date = new Date();
            formatter = new SimpleDateFormat("EEE MMM d yyyy, HH:mm:ss");
            String s = formatter.format(date);
            g.setFont(font2);
            g.setColor(Color.white);
            g.drawString("Whetstone Benchmark Java Version\0", 100, h1);
            g.setFont(font1);
            h1 = h1 + 20;
            g.drawString(s, 150, h1);
        }
        else if (section == 1)
        {
            g.setFont(font1);
            g.setColor(Color.white);
            g.drawString(headings[0], w1, h1);
            g.drawString(headings[1], w2+30, h1);
            g.drawString(headings[2], w3+8, h1);
            g.drawString(headings[3], w4+16, h1);
            g.drawString(headings[4], w5, h1);
        }
        if (section > 0)
        {
            h1 = h1 + 20;
            g.drawString(titles[section], w1, h1);
            xout = format(results[section], 3, 9);
            g.drawString(xout, w2, h1);
            xout = format(loop_mflops[section], 6, 2);
            if (loop_mflops[section] > 0.0) g.drawString(xout, w3, h1);
            xout = format(loop_mops[section], 6, 2);
            if (loop_mops[section] > 0.0) g.drawString(xout, w4, h1);
            xout = format(loop_time[section]*1000.0, 4, 4);
            g.drawString(xout, w5, h1);
        }
        if (section == 8)
        {
            h1 = h1 + 25;
            g.drawString("MWIPS", w1, h1);
            xout = format(mwips, 6, 2);
            g.drawString(xout, w3, h1);
            xout = format(TimeUsed*1000.0, 4, 4);
            g.drawString(xout, w5, h1);
            g.setFont(font3);
            String ss = "Operating System   " + System.getProperty("os.name")
                                + ", Architecture " + System.getProperty("os.arch")
                             + ", Version " + System.getProperty("os.version");                 
            g.drawString(ss, w1, h1+30);        
            String sp = "Java Vendor      " + System.getProperty("java.vendor")
                       + ", Version "   + " " + System.getProperty("java.version");
            g.drawString(sp, w1, h1+45);        
        }
        return;
    }


    public double getTime()
    {
            double q;
            long itime;
            itime = System.currentTimeMillis();
            q = (double) itime;
            return q / 1000.0;
    }

    public String format(double x, int v, int d)
    {
            String s = "";
            String s2;
            int j, len, p;
            int i = (int) Math.abs(x);
            double r = Math.abs(x) - (double) i;
            String m = " ";
            if (x < 0)
            {
                    m = "-";
            }
            s2 = m + i;
            len = v - s2.length();
            if (len < 1)
            {
                    s = s2;
            }
            else
            {
                    for (j = 0; j < len; j++)
                    {
                            s = s + " ";
                    }
                    s = s + s2;
            }
            s = s + ".";
            p = (int)(r * Math.pow(10d,(double)d));
            s2 = "" + p;
            len = d - s2.length();
            if (len < 1)
            {
                    s = s + s2;
            }
            else
            {
                    for (j = 0; j < len; j++)
                    {
                            s = s + "0";
                    }
                    s = s + s2;
            }

            return s;
    }

}














