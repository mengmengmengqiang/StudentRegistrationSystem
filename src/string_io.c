/*************************************************************************
	> File Name: string_io.c
	> Author:
	> Mail:
	> Created Time: 2017年05月25日 星期四 08时42分23秒
 ************************************************************************/

/********************************************************
*自定义输入函数
*可以做到输入时,丢弃超过指定长度的字符串,并且清空缓冲区
*不提供字符串格式检测功能
*st指向处理后的输入的字符串的首地址
*********************************************************/
#include "header/string_io.h"

int s_scanf(const char * format, const int * mode)
{
    int count;
    count = scanf(format, mode);
    while (getchar() != '\n')
        continue;
    return count;
}

/*****************************************
*scanf student struct
*****************************************/
int student_scanf( char * ID,
                   char * NAME,
                   char * SEX,
                   int * AGE,
                   char * MAJOR,
                   char * CLASS,
                   char * NUMBER
                  )
{
    do
    {
        fprintf(stdout, "enter ID(string)\n");
    }while(scanf("%s", ID) != 1);

    do
    {
        fprintf(stdout, "enter NAME(string)\n");
    }while(scanf("%s", NAME) != 1);

    do
    {
        fprintf(stdout, "enter SEX(string)\n");
    }while(scanf("%s", SEX) != 1);

    do
    {
        fprintf(stdout, "enter AGE(integer)\n");
    }while(scanf("%d", AGE) != 1);

    do
    {
        fprintf(stdout, "enter MAJOR(string)\n");
    }while(scanf("%s", MAJOR) != 1);

    do
    {
        fprintf(stdout, "enter CLASS(string)\n");
    }while(scanf("%s", CLASS) != 1);

    do
    {
        fprintf(stdout, "enter NUMBER(string)\n");
    }while(scanf("%s", NUMBER) != 1);

    return 0;
}

/*****************************************
*scanf subject struct
*****************************************/
int subject_scanf( char * ID,
                   char * NAME,
                   char * NATURE,
                   int * PERIOD,
                   int * CREDIT,
                   int * START,
                   int * SELECTED,
                   int * MAX_SELECTED
                  )
{
    do
    {
        fprintf(stdout, "enter ID(string)\n");
    }while(scanf("%s", ID) != 1);

    do
    {
        fprintf(stdout, "enter NAME(string)\n");
    }while(scanf("%s", NAME) != 1);

    do
    {
        fprintf(stdout, "enter NATURE(string)\n");
    }while(scanf("%s", NATURE) != 1);

    do
    {
        fprintf(stdout, "enter PERIOD(integer)\n");
    }while(scanf("%d", PERIOD) != 1);

    do
    {
        fprintf(stdout, "enter CREDIT(integer)\n");
    }while(scanf("%d", CREDIT) != 1);

    do
    {
        fprintf(stdout, "enter START(integer)\n");
    }while(scanf("%d", START) != 1);

    do
    {
        fprintf(stdout, "enter SELECTED(integer)\n");
    }while(scanf("%d", SELECTED) != 1);

    do
    {
        fprintf(stdout, "enter MAX_SELECTED(integer)\n");
    }while(scanf("%d", MAX_SELECTED) != 1);

    return 0;
}


