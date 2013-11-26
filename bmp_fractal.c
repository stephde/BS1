/* Betriebssystem & Middleware
 *
 * Betriebssysteme I WS 2011/2012
 *
 * Uebung 3.3
 */
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <windows.h>


#define XSIZE 500
#define YSIZE 500
#include "algorithm.h"

#pragma comment(lib, "kernel32.lib")

HANDLE mutex;

typedef struct THREAD_PARAMS
{
    int yMin;
    int yMax;
    int xMin;
    int xMax;
    FILE * file;
};

DWORD WINAPI threadFunc(LPVOID data)
{
    struct THREAD_PARAMS myParams = *(struct THREAD_PARAMS*) data;
    int len;
    char bgr[3];
    DWORD mutexResult;

    int y, x;
    for(y=myParams.yMax;y>=myParams.yMin;y--)
    {
        for(x=myParams.xMin; (x<myParams.xMax) && (x<XSIZE);x++)
        {
            getColorValuesAt(x * (2.0 / XSIZE) - 1.5, y * (2.0 / YSIZE) - 1.0,&bgr[2],&bgr[1],&bgr[0]);

            mutexResult = WaitForSingleObject(mutex, INFINITE);
            if(mutexResult == WAIT_OBJECT_0)
            {
                len=fwrite(bgr,1,3,myParams.file);
                if(-1==len || len!=3)
                {
                    perror("write");
                    exit(4);
                }
            }else if(mutexResult == WAIT_ABANDONED)
            {
                return -1;
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fd;
    int len,i;
    char *dsc;
    char bgr[3];
    short svalue;
    int   lvalue;
    unsigned char header[54],*ptr=&header[0];

    HANDLE * handles;
    struct THREAD_PARAMS * tParams;
    LPDWORD * lpThreadIds;
    DWORD dWait;

    short threadNum = 1;
    if(argc >= 2) threadNum = atoi(argv[1]);

    handles = (HANDLE*) malloc(sizeof(HANDLE) * threadNum);
    tParams = (struct THREAD_PARAMS *) malloc(sizeof(struct THREAD_PARAMS) * threadNum);
    lpThreadIds = (LPDWORD*) malloc(sizeof(LPDWORD) * threadNum);
    mutex = CreateMutex(NULL, FALSE, NULL);
    if(mutex == NULL)
    {
        printf("could not create mutex.");
        return 1;
    }

    getDescription(NULL,&len);
    if(NULL==(dsc=(char*)malloc(sizeof(char)*len)))
    {
        perror("malloc");
        exit(1);
    }
    getDescription(dsc,&len);

    printf("Calculate %s %d\n",dsc,getId());
    fd=fopen("test.bmp","wb+");
    if(NULL==fd)
    {
        perror("open"); exit(1);
    }

    svalue=0x4d42;
    memcpy(ptr,&svalue,2);//signatur
    ptr+=2;
    lvalue=XSIZE*YSIZE*3+54;
    memcpy(ptr,&lvalue,4); //filesize
    ptr+=4;
    lvalue=0;
    memcpy(ptr,&lvalue,4);//reserved
    ptr+=4;
    lvalue=54;
    memcpy(ptr,&lvalue,4);//image offset
    ptr+=4;
    lvalue=40;
    memcpy(ptr,&lvalue,4);//size of header follows
    ptr+=4;
    lvalue=XSIZE;
    memcpy(ptr,&lvalue,4);//with of image
    ptr+=4;
    lvalue=YSIZE;
    memcpy(ptr,&lvalue,4); //height of image
    ptr+=4;
    svalue=1;
    memcpy(ptr,&svalue,2); //number of planes
    ptr+=2;
    svalue=24;
    memcpy(ptr,&svalue,2); //number of pixel
    ptr+=2;
    lvalue=0; //compression
    memcpy(ptr,&lvalue,4); //compression
    ptr+=4;
    lvalue=XSIZE*YSIZE*3;
    memcpy(ptr,&lvalue,4); //size of image
    ptr+=4;
    lvalue=0;
    memcpy(ptr,&lvalue,4); //xres
    ptr+=4;
    lvalue=0;
    memcpy(ptr,&lvalue,4); //yres
    ptr+=4;
    lvalue=0;
    memcpy(ptr,&lvalue,4); //number of colortables
    ptr+=4;
    lvalue=0;
    memcpy(ptr,&lvalue,4); //number of important colors
    ptr+=4;

    len=fwrite(header,1,sizeof(header),fd); //write header

    if(-1==len || len!=sizeof(header))
    {
        perror("write");
        exit(2);
    }
#pragma message("!!!!       Implement Multithreading here    !!!!")

    for(i=0; i<threadNum; i++)
    {
        tParams[i].xMin = i * (floor(XSIZE/(float)threadNum));
        tParams[i].xMax = tParams[i].xMin + (floor(XSIZE/(float)threadNum));
        tParams[i].yMin = i * (floor(YSIZE/(float)threadNum));
        tParams[i].yMax = tParams[i].yMin + (floor(YSIZE/(float)threadNum));
        tParams[i].file = fd;
        handles[i] = createThread(NULL, 0, threadFunc, &(tParams[i]), 0, &(lpThreadIds[i]));
    }
    dWait = WaitForMultipleObjects(threadNum, handles, TRUE, 10000); //INFINITE

    fclose(fd);

    return 0;
}
