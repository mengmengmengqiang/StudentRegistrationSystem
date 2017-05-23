/*************************************************************************
	> File Name: student.h
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 08时53分43秒
    > Features: 学生信息结构声明
    > Task: 学生可以对课程信息进行查询,选修符合要求的课程,根据课程信息和学生信息完成对课程的选修.
 ************************************************************************/

#ifndef _STUDENTINFORMATION_H
#define _STUDENTINFORMATION_H

//头文件
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//宏定义
#define STUDENT_ID_LEN 10                   //学号长度
#define STUDENT_NAME_LEN 50                 //姓名长度
#define STUDENT_SEX_LEN 10                  //性别长度
#define STUDENT_MAJOR_LEN 50                //专业长度
#define STUDENT_CLASS_LEN 8                 //班级长度
#define STUDENT_PTHONE_LEN 11               //联系方式长度

//声明学生信息结构体
typedef struct {
            char ID[STUDENT_ID_LEN];        //学号
            char NAME[STUDENT_NAME_LEN];    //姓名
            char SEX[STUDENT_SEX_LEN];      //性别
            int  AGE;                       //年龄
            char MAJOR[STUDENT_MAJOR_LEN];  //专业
            char CLASS[STUDENT_CLASS_LEN];  //班级
            char NUMBER[STUDENT_PTHONE_LEN];//联系方式
} STUDENT;

/*********************显示学生基本信息*********************
 *将从学生信息二进制文件中读取学生信息并且显示出来
 *由于系统不同,所以产生的数据文件可能不具有可移植性
 *甚至同一个系统的不同编译设置也可能会导致不可移植性
 *
 ***使用函数之前需要创建文件,否则可能无法正常工作***
**********************************************************/
void show_student_info(void);


/*******************保存学生信息到文本文件*****************
 *从二进制文件中读取学生信息并保存到文本文件中以便查阅
***********************************************************/
void save_student_txt(void);

#endif
