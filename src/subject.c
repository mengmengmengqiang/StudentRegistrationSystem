/*************************************************************************
	> File Name: subject.h
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 09时27分27秒
    > Featurs: subjectinformation.
 ************************************************************************/

#ifndef _SUBJECTINFORMATION_H
#define _SUBJECTINFORMATION_H

//头文件
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//宏定义
#define SUBJECT_ID_LEN  10             //课程代码长度
#define SUBJECT_NAME_LEN 50            //课程名称长度
#define SUBJECT_NATURE_LEN 50          //课程性质长度

//声明课程信息结构
typedef struct {
                char ID[SUBJECT_ID_LEN];          //课程代码
                char NAME[SUBJECT_NAME_LEN];      //课程名称
                char NATURE[SUBJECT_NATURE_LEN];  //课程性质
                int  PERIOD;                      //总学时
                int  CREDIT;                      //学分
                int  START;                       //开科学期
                int  SELECTED;                    //课程已选人数
                int  MAX_SELECTED = 100;          //初始最大课程容量
} SUBJECT;

/***************************************************************************
 * 显示课程基本信息
 * 将从课程信息二进制文本中读取信息并且显示出来
 * 由于系统不同所以产生的数据文件可能不具有可移植性
 * 甚至相同系统不同的编译设置也可能导致不可移植性
 *
 * ****使用函数之前需要创建文件否则可能无法工作****
****************************************************************************/
void show_subject_info(void)
{
    FILE * subject_file;
    SUBJECT * subject;                  //声明一个指向结构体的指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (subject_file = fopen("subject.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"subject.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(subject_file);           //定位到文件开始
    while ( fread(subject, sizeof(SUBJECT), 1, subject_file) == 1)
        fprintf(stdout, "课程代码:%s  课程名称:%s 课程性质:%s 总学时:%d 学分:%d :%d 已选人数:%d 课程容量:%d",
                                                                                                             subject -> ID,
                                                                                                             subject -> NAME,
                                                                                                             subject -> NATURE,
                                                                                                             subject -> PERIOD,
                                                                                                             subject -> CREDIT,
                                                                                                             subject -> START,
                                                                                                             subject -> SELECTED,
                                                                                                             subject -> MAX_SELECTED
                                                                                                             );

    if (fclose(subject_file) == EOF)
        fprintf(stderr, "Error closing file \"subject.dat\".\n");
}


/******************************************************************
 *保存课程信息到文本文件以便查阅
*******************************************************************/
void save_subject_txt(void)
{
    FILE * subject_b_file;    //二进制文件指针
    FILE * subject_t_file;    //文本文件指针
    SUBJECT * subject;                  //声明一个指向课程结构体的指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (subject_b_file = fopen("subject.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"subject.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    //尝试以写文本模式打开/创建文件,如果文件打开/创建失败,则输出错误信息并且退出
    if ( (subject_t_file = fopen("subject.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can't open or creat file \"subject.txt\".\n");
        exit(EXIT_FAILURE);
    }
    rewind(subject_b_file);           //定位到二进制文件开始
    while ( fread(subject, sizeof(SUBJECT), 1, subject_b_file) == 1) //从二进制文件中读取数据保存到结构体中然后打印到文本文件中
        fprintf(subject_t_file, "课程代码:%s  课程名称:%s 课程性质:%s 总学时:%d 学分:%d :%d 已选人数:%d 课程容量:%d",
                                                                                                             subject -> ID,
                                                                                                             subject -> NAME,
                                                                                                             subject -> NATURE,
                                                                                                             subject -> PERIOD,
                                                                                                             subject -> CREDIT,
                                                                                                             subject -> START,
                                                                                                             subject -> SELECTED,
                                                                                                             subject -> MAX_SELECTED
                                                                                                             );

    if (fclose(subject_b_file) == EOF) //尝试关闭二进制文件
        fprintf(stderr, "Error closing file \"subject.dat\".\n");
    if (fclose(subject_t_file) == EOF) //尝试关闭文本文件
        fprintf(stderr, "Error closing file \"subject.txt\".\n");
}
#endif
