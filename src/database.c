/*********************************************************************************************
	> File Name: database.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 10时29分03秒
    > Featurs: 声明一个结构体,保存每个选课的学生和其选择的课程
               可以声明一个****结构体数组****,用来保存选修同一课程的学生.在后期方案中被放弃.
 ********************************************************************************************/

//头文件
#include "database.h"

/*****************************************************************
 * 将学生选课信息从二进制文件中读取并且显示
 * 由于系统不同,所以产生的二进制文件或具有不可移植性
 * 甚至同一个系统的不同编译设置也可能会导致不可移植性
 *
 * ****使用函数之前需要创建文件,否则可能无法正常工作****
******************************************************************/
void show_database_info(void)
{
    FILE * database_b_file;             //二进制文件指针
    DATABASE * database;                //声明一个指向数据库结构体的指针 

    if ( (database_b_file = fopen("database.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"database.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(database_b_file);              //定位到二进制文件开始
    while ( fread(database, sizeof(DATABASE), 1, database_b_file) == 1)
        fprintf(stdout, "信息ID:%d 课程ID:%s 课程名称:%s 学生ID:%s 学生姓名:%s\n",
                                                                                  database -> ID,
                                                                                  database -> subject.ID,
                                                                                  database -> subject.NAME,
                                                                                  database -> student.ID,
                                                                                  database -> student.NAME
                                                                                );

    //尝试关闭文件如果无法正常关闭则报错
    if ( fclose(database_b_file) == EOF)
        fprintf(stderr, "Error closing file \"database.dat\".\n");
}


/******************************************************************************************
 *从二进制文件中读取学生信息并且保存到文本文件中以便查阅
*******************************************************************************************/
void save_database_txt(void)
{
    FILE * database_b_file;             //二进制文件指针
    FILE * database_t_file;             //文本文件指针
    DATABASE * database;                //声明一个指向数据库结构体的指针 

    //尝试以只读二进制模式
    if ( (database_b_file = fopen("database.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"database.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(database_b_file);              //定位到二进制文件起始
    while ( fread(database, sizeof(DATABASE), 1, database_b_file) == 1)
        fprintf(database_t_file, "信息ID:%d 课程ID:%s 课程名称:%s 学生ID:%s 学生姓名:%s\n",
                                                                                  database -> ID,
                                                                                  database -> subject.ID,
                                                                                  database -> subject.NAME,
                                                                                  database -> student.ID,
                                                                                  database -> student.NAME
                                                                                );

    //尝试关闭二进制文件如果无法正常关闭则报错
    if (fclose(database_b_file) == EOF)
        fprintf(stderr, "Error closing file \"database.dat\".\n");
    //尝试关闭文本文件如果无法正常关闭则报错
    if (fclose(database_t_file) == EOF)
        fprintf(stderr, "Error closing file \"database.txt\".\n");
}
