#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#define INLINE  static __inline
#define PRINT   printf

#define MAX_RECORD  100
#define MAX_LINE_LEN 4000

typedef struct
{
    char *record[MAX_RECORD];
    int head;
    int tail;
    int cnt;
}RECORD_QUEUE_S;

static char g_result[MAX_LINE_LEN] = "NA";

INLINE void write_file(const bool cover, const char * const buff, const char * const filename);

void record_result(unsigned short edge)
{
    static int len = 0;
    if (len > (MAX_LINE_LEN - 10))
        return;
    if (len > 0)
        len += sprintf(g_result + len, "|");
    len += sprintf(g_result + len, "%d", edge);
}

void print_time(const char *head)
{ 
    struct timeb rawtime; 
    struct tm * timeinfo; 
    ftime(&rawtime); 
    timeinfo = localtime(&rawtime.time);

    static int ms = rawtime.millitm;
    static unsigned long s = rawtime.time;
    int out_ms = rawtime.millitm - ms;
    unsigned long out_s = rawtime.time - s;
    ms = rawtime.millitm;
    s = rawtime.time;

    if (out_ms < 0)
    {
        out_ms += 1000;
        out_s -= 1;
    }
    printf("%s date/time is: %s \tused time is %lu s %d ms.\n", head, asctime(timeinfo), out_s, out_ms); 
}

int read_file(char ** const buff, const unsigned int spec, const char * const filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        PRINT("Fail to open file %s, %s.\n", filename, strerror(errno));
        return 0;
    }
    PRINT("Open file %s OK.\n", filename);

    char line[MAX_LINE_LEN + 2];
    unsigned int cnt = 0;
    //char *pch;
    //char word[MAX_LINE_LEN+2];
    while ((cnt < spec) && !feof(fp))   //feof 检测流上的文件结束符，如果没有结束，返回0
    {
        line[0] = 0;
        fgets(line, MAX_LINE_LEN + 2, fp);
        if (line[0] == 0)   continue;
        /* for test */
        //for(int i=0;i!=strlen(line);++i)
        //{   
        //    PRINT("%c\t",line[i]);
            //if(i%4==0)
               // PRINT("\n");
        //}
        /* end test*/
       /*
        unsigned int len=0;
        pch=strtok(line," ,");
        while(pch!=NULL)
        {
            len+=sprintf(word+len,"%s",pch);
            pch=strtok(NULL," ,");
        }
        */
        buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
        strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
        //strncpy(buff[cnt], word, MAX_LINE_LEN+2-1);
        /* for test */
        //for (unsigned int i=0;i!=strlen(line);++i)
        //    PRINT("%c  ",word[i]);
        buff[cnt][4001] = 0;
        cnt++;
    }
    fclose(fp);
    PRINT("There are %d lines in file %s.\n", cnt, filename);

    return cnt;//图的边数
}

void write_result(const char * const filename)
{
    if (g_result[0] == '\0')
        return;

    write_file(1, g_result, filename);
}

void release_buff(char ** const buff, const int valid_item_num)
{
    for (int i = 0; i < valid_item_num; i++)
        free(buff[i]);
}

INLINE void write_file(const bool cover, const char * const buff, const char * const filename)
{
    if (buff == NULL)
        return;

    const char *write_type = cover ? "w" : "a";//1:覆盖写文件，0:追加写文件
    FILE *fp = fopen(filename, write_type);
    if (fp == NULL)
    {
        PRINT("Fail to open file %s, %s.\n", filename, strerror(errno));
        return;
    }
    PRINT("Open file %s OK.\n", filename);
    fputs(buff, fp);
    fputs("\n", fp);
    fclose(fp);
}

