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
#include "assert.h"

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
                int  MAX_SELECTED;                //初始最大课程容量,需要赋值
} SUBJECT;

/***************************************************************************
 * 显示课程基本信息
 * 将从课程信息二进制文本中读取信息并且显示出来
 * 由于系统不同所以产生的数据文件可能不具有可移植性
 * 甚至相同系统不同的编译设置也可能导致不可移植性
 *
 * ****使用函数之前需要创建文件否则可能无法工作****
****************************************************************************/
void show_subject_info(void);


/******************************************************************
 *保存课程信息到文本文件以便查阅
*******************************************************************/
void save_subject_txt(void);

/***************添加课程信息到二进制文件*****************
 * 添加课程到subject.dat文件中
 * 通过传入课程信息结构体指针的方式传入结构体信息到文件
*********************************************************/
void append_subject(SUBJECT * subject_append); //待添加的课程信息结构体

/*******************************************************************
 * 查询课程信息
 * 通过给出的课程ID
 * 从subject.dat里面查找学生数据
 * 比较判断是否存在这个课程
 * 若存在则将搜索权交给search_database_subject()去搜索课程的选课情况信息
********************************************************************/
int search_subject(const char * ID);   //搜索的课程ID字符串指针
#endif
