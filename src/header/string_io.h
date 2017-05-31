/*************************************************************************
	> File Name: sting_io.h
	> Author:
	> Mail:
	> Created Time: 2017年05月25日 星期四 08时22分01秒
 ************************************************************************/

#ifndef _STRING_IO_H
#define _STRING_IO_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

/********************************************************
*自定义输入函数
*可以做到输入时,丢弃超过指定长度的字符串,并且清空缓冲区
*不提供字符串格式检测功能
*********************************************************/
char * s_gets(char * st, int n);

/******************************************
*empty buffer
******************************************/
int s_scanf(const char * format, const int * mode);

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
                  );

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
                  );
#endif
