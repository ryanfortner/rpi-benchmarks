/*
  cc  drivespeed.c cpuidc.c -lm -lrt -O3 -o DriveSpeed

 */
 #define _GNU_SOURCE

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "cpuidh.h"
 #include <malloc.h>
 #include <dirent.h>
 #include <fcntl.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <sys/statvfs.h>
 
FILE    *outfile;

char   version[30] = "RasPi 1.1";
char   testFile[PATH_MAX];
char   filePath[PATH_MAX] = "";
char   partFile[10];

int  *uadataIn;
int  *uadataOut;
int  *dataIn;
int  *dataOut;
int dataSize = 1048576;
int smallSize = 1024;
int useCache;
int largeFile = 1;
int handle;
int fileMB = 8;
int blockSize;
int randBlocks;
int randPos;
int fileMBrand;

double mbps;

int writeFile(int use, int dsize);
int readFile(int use, int dsize);
int writeRead();

int main(int argc, char *argv[])
{
    FILE    *outfile;
    int c, f, g, i, k,  p, s;
    int f1, f2;

    double totalMB;
    double freeMB;
    double cc;
    double msecs;
    double maxdsecs = 0;

    int param1;
    int fileKB;
    int totalf;

    char wr[10][14];

    for (i=1; i<5; i=i+2)
    {
       if (argc > i)
       {
          switch (toupper(argv[i][0]))
          {
                case 'M':
                param1 = 0;
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%d", &param1);
                   if (param1 > 0)
                   {
                      fileMB = param1;
                   }
                }
                break;

                case 'F':
                if (argc > i+1)
                {
                   sscanf(argv[i+1],"%s", filePath);
                   strcat(filePath, "/");
                }
                break;

          }
       }
    }

    outfile = fopen("driveSpeed.txt","a+");
    if (outfile == NULL)
    {
        printf ("Cannot open results file \n\n");
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }
    printf("\n");
    getDetails();


    int pagesize = getpagesize();
    uadataIn  = (int*)malloc(dataSize + pagesize);
    uadataOut = (int*)malloc(dataSize + pagesize);
    dataIn   = (int*)((((int unsigned)uadataIn  + pagesize - 1) / pagesize) * pagesize);
    dataOut  = (int*)((((int unsigned)uadataOut + pagesize - 1) / pagesize) * pagesize);
 
    printf(" ##########################################\n"); 
    fprintf (outfile, " #####################################################\n\n");                     

    printf ("\nFrom File /proc/cpuinfo\n");
    printf("%s\n", configdata[0]);
    printf ("\nFrom File /proc/version\n");
    printf("%s\n", configdata[1]);

    local_time();

    printf("    DriveSpeed %s %s ", version, timeday);
    printf("      Copyright (C) 2013, Roy Longbottom\n");
    printf("\n");

    fprintf(outfile, "   DriveSpeed %s %s ", version, timeday);
    fprintf(outfile, "\n");

    char *thispath = NULL;

    if (strcmp(filePath, "") != 0)
    { 
        printf (" Selected File Path: \n %s\n", filePath);
        fprintf (outfile, " Selected File Path: \n %s\n", filePath);
        thispath = filePath;
    }
    else
    {
        thispath = getcwd(thispath, PATH_MAX); 
        if (thispath == NULL)
        {
            printf(" Current Directory Path not available\n");
            fprintf(outfile, " Current Directory Path not available\n");
        }
        else
        {
            printf (" Current Directory Path: %s\n", thispath);
            fprintf (outfile, " Current Directory Path: %s\n", thispath);
        }
    }
    struct statvfs driveSpace;
    if (statvfs(thispath, &driveSpace))
    {
        printf(" Free Disk Space not available - Exit\n");
        fprintf(outfile, " Free Disk Space not available - Exit\n");
        fclose(outfile);
        free(uadataIn);
        free(uadataOut);
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }
    else
    {  
      totalMB = (double)driveSpace.f_frsize * (double)driveSpace.f_blocks / 1048576.0;
      freeMB  = (double)driveSpace.f_frsize * (double)driveSpace.f_bfree  / 1048576.0;
      printf (" Total MB %7.0f, Free MB %7.0f, Used MB %7.0f\n\n", totalMB, freeMB, totalMB - freeMB);
      fprintf (outfile, " Total MB %7.0f, Free MB %7.0f, Used MB %7.0f\n\n", totalMB, freeMB, totalMB - freeMB);
    }
    if (freeMB < 60)
    {
        printf(" Not Enough Free Disk Space - Exit\n");
        fprintf(outfile, " Not Enough Free Disk Space - Exit\n");
        fclose(outfile);
        free(uadataIn);
        free(uadataOut);
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }        

    for (i=0; i<262144; i++)
    {
        dataIn[i]  = 0;
        dataOut[i] = i;
    }
    printf ("                        MBytes/Second\n");
    printf ("  MB   Write1   Write2   Write3    Read1    Read2    Read3\n\n");
    fprintf (outfile, "                        MBytes/Second\n");
    fprintf (outfile, "  MB   Write1   Write2   Write3    Read1    Read2    Read3\n\n");

    // Large Files
    useCache = 0;

    for (s=0; s<2; s++)
    {
        if (s > 0) fileMB = fileMB * 2;
        printf          ("%4d", fileMB);
        fprintf(outfile, "%4d", fileMB);

        // Write
        for (f=0; f<3; f++)
        {
            sprintf(testFile, "%szzztestz%d", filePath, f); 
            if (!writeFile(fileMB, dataSize))
            {
                for (f=0; f<3; f++)
                {
                   sprintf(testFile, "%szzztestz%d", filePath, f);        
                   remove(testFile);
                }  
                free(uadataIn);
                free(uadataOut);
                exit (0);
            }
            mbps = (double)fileMB * (double)dataSize/ 1000000.0 / secs;
            printf          (" %8.2f", mbps);
            fflush(stdout);
            fprintf(outfile, " %8.2f", mbps);
        }
        //  Read
        for (f=0; f<3; f++)
        {
            sprintf(testFile, "%szzztestz%d", filePath, f);
    
            if (!readFile(fileMB, dataSize))  
            {
                for (f=0; f<3; f++)
                {
                  sprintf(testFile, "%szzztestz%d", filePath, f);        
                  remove(testFile);
                }  
                free(uadataIn);
                free(uadataOut);
                exit (0);
            }
    
            mbps = (double)fileMB * (double)dataSize/ 1000000.0 / secs;
            printf          (" %8.2f", mbps);
            fflush(stdout);
            fprintf(outfile, " %8.2f", mbps);
            fflush(stdout);
            fflush(outfile);
        }
        printf("\n"); 
        fprintf(outfile, "\n"); 
    
        for (f=0; f<3; f++)
        {
           sprintf(testFile, "%szzztestz%d", filePath, f);        
           remove(testFile);
        }  
    }

    // Cached
    useCache = 1;
    fileMB =  8;
    printf(" Cached\n%4d", fileMB); 
    fprintf(outfile, " Cached\n%4d", fileMB); 

    // Write
    for (f=0; f<3; f++)
    {
        sprintf(testFile, "%szzztestz%d", filePath, f); 
        if (!writeFile(fileMB, dataSize))
        {
            for (f=0; f<3; f++)
            {
               sprintf(testFile, "%szzztestz%d", filePath, f);        
               remove(testFile);
            }  
            free(uadataIn);
            free(uadataOut);
            exit (0);
        }
        mbps = (double)fileMB * (double)dataSize/ 1000000.0 / secs;
        printf          (" %8.2f", mbps);
        fflush(stdout);
        fprintf(outfile, " %8.2f", mbps);
    }

    //  Read
    for (f=0; f<3; f++)
    {
        sprintf(testFile, "%szzztestz%d", filePath, f);

        if (!readFile(fileMB, dataSize))  
        {
            for (f=0; f<3; f++)
            {
              sprintf(testFile, "%szzztestz%d", filePath, f);        
              remove(testFile);
            }  
            free(uadataIn);
            free(uadataOut);
            exit (0);
        }

        mbps = (double)fileMB * (double)dataSize/ 1000000.0 / secs;
        printf          (" %8.2f", mbps);
        fprintf(outfile, " %8.2f", mbps);
        fflush(stdout);
        fflush(outfile);
    }
    printf("\n\n"); 
    fprintf(outfile, "\n\n"); 

    for (f=0; f<3; f++)
    {
       sprintf(testFile, "%szzztestz%d", filePath, f);        
       remove(testFile);
    }
     
    // Random
    printf(" Random         Read                       Write\n");
    fprintf(outfile, " Random         Read                       Write\n");
    printf(" From MB        4        8       16        4        8       16\n"); 
    fprintf(outfile, " From MB        4        8       16        4        8       16\n");
    printf(" msecs  "); 
    fprintf(outfile,  " msecs  "); 

    fileMBrand = 16;
    randBlocks = fileMBrand * 1024;
    blockSize = 1024;
    f = 7;
    useCache = 0;
    srand(123);
    sprintf(partFile, "zzztestz%d", f); 

    // Write 16 MB file
    sprintf(testFile, "%s%srand", filePath, partFile); 
    if (!writeFile(fileMBrand, dataSize))
    {
       remove(testFile);
       free(uadataIn);
       free(uadataOut);
       exit (0);
    }

    handle = open(testFile, O_RDWR | O_DIRECT);
    if (handle == -1)
    {
        printf (" Cannot open data file for reading and writing\n\n");
        fprintf (outfile, " Cannot open data file for reading and  writing\n\n");
        fclose(outfile);
        remove("testFile");
        free(uadataIn);
        free(uadataOut);
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }

    // Random Read
    
    c = 3;
    for (p=4; p<fileMBrand+1; p=p*2)
    {
        cc = 0.0;
        start_time();
        do
        {
            for (k=0; k<25; k++)
            {
                randPos = (int)((double)p * 1024.0 * ((double)(rand()) / (double)2147483648.0));
                if (randPos == randBlocks) randPos = randPos - 1;
                lseek(handle, randPos * 1024, SEEK_SET);
                if (read(handle, dataIn, blockSize) == -1)
                {
                    remove(testFile);
                    printf ("\n  Error reading file randomly\n\n");
                    fprintf (outfile, "\n  Error reading file randomly\n\n");
                    printf(" Press Enter\n");
                    g  = getchar();
                    free(uadataIn);
                    free(uadataOut);
                    exit (0);        
                }
            }
            end_time();
            cc = cc + 25.0;
        }
        while (secs < 1.0);
        msecs = 1000.0 * secs / cc;
        printf("%9.3f", msecs);
        fflush(stdout);
        fprintf(outfile, "%9.3f", msecs);
        c = c + 1;            
    }

   // Random Write
    
    c = 0;
    for (p=4; p<fileMBrand+1; p=p*2)
    {  
        cc = 0.0;
        start_time();
        do
        {
            for (k=0; k<25; k++)
            {
                randPos = (int)((double)p * 1024 * ((double)(rand()) / (double)2147483648.0));
                if (randPos == randBlocks) randPos = randPos - 1;
                lseek(handle, randPos * 1024, SEEK_SET);
                if (write(handle, dataOut, blockSize) == -1)
                {
                    remove(testFile);
                    printf ("\n  Error writing file randomly\n\n");
                    fprintf (outfile, "\n  Error writing file randomly\n\n");
                    printf(" Press Enter\n");
                    g  = getchar();
                    free(uadataIn);
                    free(uadataOut);
                    exit (0);        
                }
            }
            end_time();
            cc = cc + 25.0;
        }
        while (secs < 1.0);
        msecs = 1000.0 * secs / cc;
        printf("%9.2f", msecs);
        fflush(stdout);
        fprintf(outfile, "%9.2f", msecs);
        c = c + 1;            
     }        
     close (handle);
     remove(testFile);
     printf("\n\n"); 
     fprintf(outfile, "\n\n"); 
    
      // Small Files
      printf (" WARNING, writing small files can take many seconds\n\n");

      printf(" 200 Files      Write                      Read                  Delete\n");
      printf(" File KB        4        8       16        4        8       16     secs\n");
      printf(" MB/sec "); 
      fprintf(outfile, " 200 Files      Write                      Read                  Delete\n");
      fprintf(outfile, " File KB        4        8       16        4        8       16     secs\n");
      fprintf(outfile, " MB/sec "); 
    
       largeFile = 0;
       useCache = 0;
       f1 = 1000;
       f2 = 1200;
       totalf = f2 - f1;
       c = 0;       
       for (fileKB=4; fileKB<17; fileKB=fileKB*2)
       {
            if (fileKB > 4) sleep(5);
            
            // Write

            start_time();
            for (f=f1; f<f2; f++)
            {
                sprintf(testFile, "%s%s%d", filePath, partFile, f); 
                if (!writeFile(1, smallSize * fileKB))
                {
                    for (f=f1; f<f2; f++)
                    {
                        sprintf(testFile, "%s%s%d", filePath, partFile, f);
                        remove(testFile);
                        free(uadataIn);
                        free(uadataOut);
                        exit (0);
                     }
                }

            }
            end_time();
            mbps = (double)totalf * (double)fileKB * (double)smallSize / 1000000.0 / secs;
            msecs = secs * 1000.0 / (double)totalf;
            printf("%9.2f", mbps);
            fflush(stdout);
            fprintf(outfile, "%9.2f", mbps);
            sprintf(wr[c], "%9.2f", msecs);

            // Read
            
            start_time();
            for (f=f1; f<f2; f++)
            { 
                sprintf(testFile, "%s%s%d", filePath, partFile, f);
                if (!readFile(1, smallSize * fileKB))
                {
                    for (f=f1; f<f2; f++)
                    {
                        sprintf(testFile, "%s%s%d", filePath, partFile, f); 
                        remove(testFile);
                        free(uadataIn);
                        free(uadataOut);
                        exit (0);
                    }
                }
            }
            end_time();
            mbps = (double)totalf * (double)fileKB * (double)smallSize / 1000000.0 / secs;
            msecs = secs * 1000.0 / (double)totalf;
            fflush(stdout);
            sprintf(wr[c+7], "%9.2f", mbps);
            sprintf(wr[c+3], "%9.2f", msecs);
            
            start_time();
            for (f=f1; f<f2; f++)
            {
                sprintf(testFile, "%s%s%d", filePath, partFile, f); 
                remove(testFile);
            }
            end_time();
            if (secs > maxdsecs) maxdsecs = secs;
            c = c + 1;
       }
       sprintf(wr[6], "%9.3f", maxdsecs);

       printf("%s%s%s\n ms/file%s%s%s%s%s%s%s\n",
                wr[7], wr[8], wr[9], wr[0], wr[1], wr[2], wr[3], wr[ 4], wr[ 5], wr[6]);
       fprintf(outfile, "%s%s%s\n ms/file%s%s%s%s%s%s%s\n",
                 wr[7], wr[8], wr[9], wr[0], wr[1], wr[2], wr[3], wr[ 4], wr[ 5], wr[6]);

    
        printf("\n");
        fprintf(outfile, "\n");
        fflush(stdout);
        fflush(outfile);

    local_time();
    fprintf(outfile, "\n                End of test %s\n", timeday);

    fprintf (outfile, " SYSTEM INFORMATION\n\nFrom File /proc/cpuinfo\n");
    fprintf (outfile, "%s \n", configdata[0]);
    fprintf (outfile, "\nFrom File /proc/version\n");
    fprintf (outfile, "%s \n", configdata[1]);
    fprintf (outfile, "\n");

    fflush(outfile);

    char moredata[1024];
    printf("\n Type additional information to include in driveSpeed.txt - Press Enter\n");
    if (fgets (moredata, sizeof(moredata), stdin) != NULL)
    fprintf (outfile, " Additional information - %s\n", moredata);

    free(uadataOut);
    free(uadataIn);
    fflush(outfile);
    fclose(outfile);
           
    return 1;
}



int writeFile(int use, int dsize)
{
    int  g, p;
    
    if (largeFile) start_time();

    if (useCache)
    {
          handle = open(testFile, O_WRONLY | O_CREAT | O_TRUNC,
                                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    }
    else
    {
          handle = open(testFile, O_WRONLY | O_CREAT | O_TRUNC | O_DIRECT,  // | O_SYNC | O_DIRECT  
                                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    }
    if (handle == -1)
    {
        printf ("\n Cannot open data file for writing\n\n");
        fprintf (outfile, "\n Cannot open data file for writing\n\n");
        fclose(outfile);
        printf(" Press Enter\n");
        g  = getchar();
        return 0;
    }

    for (p=0; p<use; p++)
    {
       if (write(handle, dataOut, dsize) != dsize )
       {
            printf ("\n Error writing file\n\n");
            fprintf (outfile, "\n Error writing file\n\n");
            fclose(outfile);
            close(handle);
            printf(" Press Enter\n");
            g  = getchar();
            return 0;
        }
    }
//    if (!useCache) fsync(handle);
    close(handle);
    if (largeFile) end_time();
    return 1;
}

int readFile(int use, int dsize)
{
    int g, p;

    if (largeFile) start_time();

    if (useCache)
    {
          handle = open(testFile, O_RDONLY);
    }
    else
    {
          handle = open(testFile, O_RDONLY | O_DIRECT);
    }


    if (handle == -1)
    {
        printf ("\n Cannot open data file for reading\n\n");
        fprintf (outfile, "\n Cannot open data file for reading\n\n");
        fclose(outfile);
        printf(" Press Enter\n");
        g  = getchar();
        return 0;
    }

    for (p=0; p<use; p++)
    {
        if (read(handle, dataIn, dsize) == -1)
        {
            printf ("\n Error reading file\n\n");
            fprintf (outfile, "\n Error reading file\n\n");
            fclose(outfile);
            close(handle);
            printf(" Press Enter\n");
            g  = getchar();
            return 0;
        }           
 
    }
    close(handle);
    if (largeFile) end_time();
    return 1;
}

