
// Compile command -  cc RPiHeatMHz.c -lrt -o RPiHeatMHz

// Run     command -  ./RPiHeatMHz passes ppp, seconds sss

//                    for ppp samples at sss second intervals

// Default            ./RPiHeatMHz

//                    10 samples at 1 second intervals  

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE     *outfile;

char    timeday[30];
double  theseSecs = 0.0;
double  startSecs = 0.0;
double  secs;
struct  timespec tp1;
int     passes  = 10;
int     seconds = 1;


void getTemperature();
void start_time();
void end_time();
void getSecs();
void local_time();



void getMHz()
{
    int qz;
    char buffer[100];

    qz = system("grep -v ^# /boot/config.txt |grep -v ^$ > thizPiz.txt");
    FILE    *infile;
    infile = fopen("thizPiz.txt","r");
    if (infile == NULL)
    {
        printf (" MHz details not available\n\n");
        fprintf (outfile, " MHz details not available\n\n");
    }
    else
    {
        printf (" Boot Settings\n\n");
        fprintf (outfile, " Boot Settings\n\n");
        while (fgets( buffer, 100, infile ) != NULL)
        {
            printf(" %s", buffer);
            fprintf(outfile, " %s", buffer);
        }
        printf("\n"); 
        fprintf(outfile, "\n"); 
    }
    fclose (infile);
}

void main(int argc, char *argv[])
{
    int i;
    int param1;

    for (i=1; i<5; i=i+2)
    {
       if (argc > i)
       {
          switch (toupper(argv[i][0]))
          {
               case 'P':
                param1 = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   if (param1 > 0) passes = param1;
                }
                break;

                case 'S':
                param1 = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   if (param1 > 0) seconds = param1;
                }
                break;
          }
       }
    }
    outfile = fopen("RPiHeatMHz.txt", "a+");
    if (outfile == NULL)
    {
        printf ("Cannot open results file \n\n");
        exit (0);
    }

    local_time();
    fprintf(outfile, " Temperature and CPU MHz Measurement\n\n Start at %s\n", timeday); 
    fprintf(stdout,  " Temperature and CPU MHz Measurement\n\n Start at %s\n", timeday);
    fprintf(outfile, " Using %d samples at %d second intervals\n\n", passes, seconds);
    fprintf(stdout,  " Using %d samples at %d second intervals\n\n", passes, seconds);

    getMHz();
        
    fprintf(outfile, " Seconds\n");
    fprintf(stdout,  " Seconds\n");
    secs = 0.0;
    getTemperature();

    start_time();

    for (i=0; i<passes; i++)
    {
        sleep(seconds);
        end_time();
        getTemperature();
    }
    local_time();
    fprintf(outfile, "\n End at   %s\n", timeday); 
    fprintf(stdout,  "\n End at   %s\n", timeday);

    fprintf(stdout,  " Results also in RPiHeatMHz.txt where temperatures will be\n"
                     " slightly different as separate function calls are used.\n");

    fclose(outfile);
    return;
}

void getTemperature()
{
    int freq;
    int armfreq;

    int f = system("cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq > thisSpd.txt");    
    int s = system("vcgencmd measure_clock arm > MH.txt");
    int m = system("grep -Eo  '[0-9]{6,10}' MH.txt > MH2.txt");

    FILE    *afile;
    afile = fopen("thisSpd.txt","r");
    fscanf(afile, "%d", &freq);
    fclose(afile);

    afile = fopen("MH2.txt","r");
    fscanf(afile, "%d", &armfreq);
    fclose(afile);

    fprintf(outfile, " %6.1f  ", secs);
    fprintf(stdout,  " %6.1f  ", secs);
    fprintf(stdout,  " %6d scaling MHz, %6d ARM MHz, ", freq/1000, armfreq/1000000);
    fprintf(outfile, " %6d scaling MHz, %6d ARM MHz, ", freq/1000, armfreq/1000000);
    fflush(outfile);
    fflush (stdout);

    int g = system("/opt/vc/bin/vcgencmd measure_temp >> RPiHeatMHz.txt");
    int h = system("/opt/vc/bin/vcgencmd measure_temp");
    return;
}

void local_time()
{
    time_t t;

    t = time(NULL);
    sprintf(timeday, "%s", asctime(localtime(&t)));
    return;
}

void getSecs()
{
     clock_gettime(CLOCK_REALTIME, &tp1);

     theseSecs =  tp1.tv_sec + tp1.tv_nsec / 1e9;           
     return;
}

void start_time()
{
    getSecs();
    startSecs = theseSecs;
    return;
}

void end_time()
{
    getSecs();
    secs = theseSecs - startSecs;
    return;
}    

