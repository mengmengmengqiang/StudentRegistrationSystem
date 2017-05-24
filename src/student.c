/*************************************************************************
	> File Name: student.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 08时53分43秒
    > Features: 学生信息结构声明
    > Task: 学生可以对课程信息进行查询,选修符合要求的课程,根据课程信息和学生信息完成对课程的选修.
 ************************************************************************/

#include "header/student.h"

/*********************显示学生基本信息*********************
 *将从学生信息二进制文件中读取学生信息并且显示出来
 *由于系统不同,所以产生的数据文件可能不具有可移植性
 *甚至同一个系统的不同编译设置也可能会导致不可移植性
 *
 ***使用函数之前需要创建文件,否则可能无法正常工作***
**********************************************************/
void show_student_info(void)
{
    FILE * student_b_file;    //二进制文件指针
    STUDENT * student_read;      //从文件中读出的学生结构体的指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Cant't open file \"student.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(student_b_file);           //定位到文件开始
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
        fprintf(stdout, "学号:%s 姓名:%s 性别:%s 年龄:%d 专业:%s 班级:%s 联系方式:%s\n",
                                                                                        student_read -> ID,
                                                                                        student_read -> NAME,
                                                                                        student_read -> SEX,
                                                                                        student_read -> AGE,
                                                                                        student_read -> MAJOR,
                                                                                        student_read -> CLASS,
                                                                                        student_read -> NUMBER
                                                                                        );
    if (fclose(student_b_file) == EOF)
        fprintf(stderr, "Error closing file \"student.dat\"\n");
}


/*******************保存学生信息到文本文件*****************
 *从二进制文件中读取学生信息并保存到文本文件中以便查阅
***********************************************************/
void save_student_txt(void)
{
    FILE * student_b_file; //二进制文件指针
    FILE * student_t_file; //文本文件指针
    STUDENT * student_read;      //从文件中读出的学生结构体指针

    //尝试以只读二进制模式打开二进制文件,如果文件打开失败,则输出错误信息并且退出
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Cant't open file \"student.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    //尝试以写文本模式打开文本文件,如果文件打开/创建失败,则输出错误信息并且退出
    if ( (student_t_file = fopen("student.txt", "w")) == NULL)
    {
        fprintf(stderr, "Cant't open or create file \"student.txt\".\n");
        exit(EXIT_FAILURE);
    }
    rewind(student_b_file);           //定位到二进制文件开始
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1) //从二进制文件中读取数据保存到结构体中然后打印到文本文件中
        fprintf(student_t_file, "学号:%s 姓名:%s 性别:%s 年龄:%d 专业:%s 班级:%s 联系方式:%s\n",
                                                                                        student_read -> ID,
                                                                                        student_read -> NAME,
                                                                                        student_read -> SEX,
                                                                                        student_read -> AGE,
                                                                                        student_read -> MAJOR,
                                                                                        student_read -> CLASS,
                                                                                        student_read -> NUMBER
                                                                                        );
    if (fclose(student_b_file) == EOF) //尝试关闭二进制文件
        fprintf(stderr, "Error closing file \"student.dat\"\n");
    if (fclose(student_t_file) == EOF) //尝试关闭文本文件
        fprintf(stderr, "Error closing file \"student.txt\"\n");
}


/***************添加学生信息到二进制文件*****************
 * 添加学生到student.dat文件中
 * 通过传入学生信息结构体指针的方式传入结构体信息到文件
*********************************************************/
void append_student(STUDENT * student_append) //待添加的学生信息结构体指针
{
    FILE * student_b_file;          //二进制文件指针 
    STUDENT * student_read;         //从文件中读出的学生信息结构体指针
    int flag = 0;                   //设置判断标志位,0表示学生信息未添加,1表示学生信息已存在

    //尝试以更新二进制模式打开文件,如果文件打开失败,则猜测可能是文件不存在
    //然后尝试以append二进制模式添加一个文件,如果文件真的不存在则新建一个文件
    //如果创建失败,则返回错误信息,并且退出程序
    //如果创建成功,则关闭文件
    //然后再次以更新二进制模式打开文件
    if ( (student_b_file = fopen("student.dat", "r+b")) == NULL)
    {
        if ( (student_b_file = fopen("student.dat", "ab")) == NULL)
        {
            fprintf(stderr, "Can't creat file \"student.dat\".\n");
            exit(EXIT_FAILURE);
        }
        if ( fclose(student_b_file) == EOF)
            fprintf(stderr, "Error closing file \"student.dat\".\n");

        if( (student_b_file = fopen("student.dat", "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and creat file \"student.dat\".\n");
            exit(EXIT_FAILURE);
        }
    }

    rewind(student_b_file);           //定位到二进制文件开始
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
    {
        if (1)               //比对学生ID,如果发现重复则提示数据重复并取消添加
        {
            flag = 1;                                       //flag为1表示学生信息存在
            fprintf(stdout, "学生信息已存在,无需重复添加!");
            break;                                          //终止遍历文件
        }
    }

    //如果学生信息未添加,则定位到文件末尾,添加学生信息到二进制文件中
    if (flag == 0)
    {
        fseek(student_b_file, 0L, SEEK_END); //定位至文件结尾

        //尝试写入student_append信息到二进制文件中
        if ( fwrite(student_append, sizeof(STUDENT), 1, student_b_file) != 1)
            fprintf(stderr, "Error writing student_append to file \"student.dat\".");
    }


    //尝试关闭二进制文件
    if (fclose(student_b_file) == EOF)
        fprintf(stderr, "Error closing file \"student.dat\"\n");
}
