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
    FILE * database_b_file;                 //二进制文件指针
    DATABASE * database_read;               //从二进制文件中读出的数据库结构体 

    if ( (database_b_file = fopen("database.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"database.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(database_b_file);              //定位到二进制文件开始
    while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
        fprintf(stdout, "信息ID:%d 课程ID:%s 课程名称:%s 学生ID:%s 学生姓名:%s\n",
                                                                                  (database_read -> ID),
                                                                                  (database_read -> subject).ID,
                                                                                  (database_read -> subject).NAME,
                                                                                  (database_read -> student).ID,
                                                                                  (database_read -> student).NAME
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
    DATABASE * database_read;                //从二进制文件中读出的数据库结构体

    //尝试以只读二进制模式
    if ( (database_b_file = fopen("database.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"database.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(database_b_file);              //定位到二进制文件起始
    while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
        fprintf(database_t_file, "信息ID:%d 课程ID:%s 课程名称:%s 学生ID:%s 学生姓名:%s\n",
                                                                                  (database_read -> ID),
                                                                                  (database_read -> subject).ID,
                                                                                  (database_read -> subject).NAME,
                                                                                  (database_read -> student).ID,
                                                                                  (database_read -> student).NAME
                                                                                );

    //尝试关闭二进制文件如果无法正常关闭则报错
    if (fclose(database_b_file) == EOF)
        fprintf(stderr, "Error closing file \"database.dat\".\n");
    //尝试关闭文本文件如果无法正常关闭则报错
    if (fclose(database_t_file) == EOF)
        fprintf(stderr, "Error closing file \"database.txt\".\n");
}


/***************添加选课信息到二进制文件*****************
 * 添加选课信息到database.dat文件中
 * 通过传入选课信息结构体指针的方式传入结构体信息到文件
*********************************************************/
void append_database(DATABASE * database_append) //待添加的课程信息结构体指针
{
    FILE * database_b_file;          //二进制文件指针 
    DATABASE * database_read;        //从文件中读出的选课信息结构体指针
    int flag = 0;                    //设置判断标志位,0表示选课信息未添加,1表示选课信息已存在

    //尝试以更新二进制模式打开文件,如果文件打开失败,则猜测可能是文件不存在
    //然后尝试以append二进制模式添加一个文件,如果文件真的不存在则新建一个文件
    //如果创建失败,则返回错误信息,并且退出程序
    //如果创建成功,则关闭文件
    //然后再次以更新二进制模式打开文件
    if ( (database_b_file = fopen("database.dat", "r+b")) == NULL)
    {
        if ( (database_b_file = fopen("database.dat", "ab")) == NULL)
        {
            fprintf(stderr, "Can't creat file \"database.dat\".\n");
            exit(EXIT_FAILURE);
        }
        if ( fclose(database_b_file) == EOF)
            fprintf(stderr, "Error closing file \"database.dat\".\n");

        if( (database_b_file = fopen("database.dat", "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and create file \"database.dat\".\n");
            exit(EXIT_FAILURE);
        }
    }

    rewind(database_b_file);           //定位到二进制文件开始
    while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
    {
        if (1)               //比对学生ID和课程ID,如果发现两者同时重复则提示数据重复并取消添加
        {
            flag = 1;                                       //flag为1表示选课信息存在
            fprintf(stdout, "选课信息已存在,无需重复添加!");
            break;                                          //终止遍历文件
        }
    }

    //如果选课信息未添加,则定位到文件末尾,添加选课信息到二进制文件中
    if (flag == 0)
    {
        fseek(database_b_file, 0L, SEEK_END); //定位至文件结尾

        //尝试写入database_append信息到二进制文件中
        if ( fwrite(database_append, sizeof(DATABASE), 1, database_b_file) != 1)
        B
            fprintf(stderr, "Error writing database_append to file \"database.dat\".\n");
    }


    //尝试关闭二进制文件
    if (fclose(database_b_file) == EOF)
        fprintf(stderr, "Error closing file \"database.dat\"\n");
}


/*******************************************************
 * 查询选课信息
 * 通过给出的ID
 * 先从database里面查找学生数据
 * 如果找不到就从学生数据库和课程数据库里查找信息
 *******************************************************/
void search_database(const char * ID)
{
    
}
