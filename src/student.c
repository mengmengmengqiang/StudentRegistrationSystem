/*************************************************************************
	> File Name: student.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 08时53分43秒
    > Features: 学生信息结构声明
    > Task: 学生可以对课程信息进行查询,选修符合要求的课程,根据课程信息和学生信息完成对课程的选修.
 ************************************************************************/

#include "student.h"

/*********************显示学生基本信息*********************
 *将从学生信息二进制文件中读取学生信息并且显示出来
 *由于系统不同,所以产生的数据文件可能不具有可移植性
 *甚至同一个系统的不同编译设置也可能会导致不可移植性
 *
 ***使用函数之前需要创建文件,否则可能无法正常工作***
**********************************************************/
void show_student_info(void)
{
    FILE * student_file;
    STUDENT * student;      //声明一个指向学生结构体的指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (student_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Cant't open file \"student.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(student_file);           //定位到文件开始
    while ( fread(student, sizeof(STUDENT), 1, student_file) == 1)
        fprintf(stdout, "学号:%s 姓名:%s 性别:%s 年龄:%d 专业:%s 班级:%s 联系方式:%s\n",
                                                                                        student -> ID,
                                                                                        student -> NAME,
                                                                                        student -> SEX,
                                                                                        student -> AGE,
                                                                                        student -> MAJOR,
                                                                                        student -> CLASS,
                                                                                        student -> NUMBER
                                                                                        );
    if (fclose(student_file) == EOF)
        fprintf(stderr, "Error closing file \"student.dat\"\n");
}


/*******************保存学生信息到文本文件*****************
 *从二进制文件中读取学生信息并保存到文本文件中以便查阅
***********************************************************/
void save_student_txt(void)
{
    FILE * student_b_file; //二进制文件指针
    FILE * student_t_file; //文本文件指针
    STUDENT * student;      //声明一个指向学生结构体的指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Cant't open file \"student.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    //尝试以写文本模式打开文件,如果文件打开/创建失败,则输出错误信息并且退出
    if ( (student_t_file = fopen("student.txt", "w")) == NULL)
    {
        fprintf(stderr, "Cant't open or create file \"student.txt\".\n");
        exit(EXIT_FAILURE);
    }
    rewind(student_b_file);           //定位到二进制文件开始
    while ( fread(student, sizeof(STUDENT), 1, student_b_file) == 1) //从二进制文件中读取数据保存到结构体中然后打印到文本文件中
        fprintf(student_t_file, "学号:%s 姓名:%s 性别:%s 年龄:%d 专业:%s 班级:%s 联系方式:%s\n",
                                                                                        student -> ID,
                                                                                        student -> NAME,
                                                                                        student -> SEX,
                                                                                        student -> AGE,
                                                                                        student -> MAJOR,
                                                                                        student -> CLASS,
                                                                                        student -> NUMBER
                                                                                        );
    if (fclose(student_b_file) == EOF) //尝试关闭二进制文件
        fprintf(stderr, "Error closing file \"student.dat\"\n");
    if (fclose(student_t_file) == EOF) //尝试关闭文本文件
        fprintf(stderr, "Error closing file \"student.txt\"\n");
}
