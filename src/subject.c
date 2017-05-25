/*************************************************************************
	> File Name: subject.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 09时27分27秒
    > Featurs: subjectinformation.
 ************************************************************************/

//头文件
#include "header/subject.h"

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
    FILE * subject_b_file;                   //二进制课程信息文件
    SUBJECT * subject_read;                  //从二进制文件中读取的课程信息结构体指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (subject_b_file = fopen("subject.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"subject.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    rewind(subject_b_file);           //定位到文件开始
    while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
        fprintf(stdout, "课程代码:%s  课程名称:%s 课程性质:%s 总学时:%d 学分:%d 开课学期:%d 已选人数:%d 课程容量:%d",
                                                                                                             subject_read -> ID,
                                                                                                             subject_read -> NAME,
                                                                                                             subject_read -> NATURE,
                                                                                                             subject_read -> PERIOD,
                                                                                                             subject_read -> CREDIT,
                                                                                                             subject_read -> START,
                                                                                                             subject_read -> SELECTED,
                                                                                                             subject_read -> MAX_SELECTED
                                                                                                             );

    if (fclose(subject_b_file) == EOF)
        fprintf(stderr, "Error closing file \"subject.dat\".\n");
}


/******************************************************************
 *保存课程信息到文本文件以便查阅
*******************************************************************/
void save_subject_txt(void)
{
    FILE * subject_b_file;    //二进制文件指针
    FILE * subject_t_file;    //文本文件指针
    SUBJECT * subject_read;   //从二进制文件中读取的课程信息结构体指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (subject_b_file = fopen("subject.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"subject.dat\", maybe you have not created it.\n");
        exit(EXIT_FAILURE);
    }

    //尝试以写文本模式打开/创建文件,如果文件打开/创建失败,则输出错误信息并且退出
    if ( (subject_t_file = fopen("课程信息表.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can't open or creat file \"课程信息表.txt\".\n");
        exit(EXIT_FAILURE);
    }
    rewind(subject_b_file);           //定位到二进制文件开始
    while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1) //从二进制文件中读取数据保存到结构体中然后打印到文本文件中
        fprintf(subject_t_file, "课程代码:%s  课程名称:%s 课程性质:%s 总学时:%d 学分:%d :%d 已选人数:%d 课程容量:%d",
                                                                                                             subject_read -> ID,
                                                                                                             subject_read -> NAME,
                                                                                                             subject_read -> NATURE,
                                                                                                             subject_read -> PERIOD,
                                                                                                             subject_read -> CREDIT,
                                                                                                             subject_read -> START,
                                                                                                             subject_read -> SELECTED,
                                                                                                             subject_read -> MAX_SELECTED
                                                                                                             );

    if (fclose(subject_b_file) == EOF) //尝试关闭二进制文件
        fprintf(stderr, "Error closing file \"subject.dat\".\n");
    if (fclose(subject_t_file) == EOF) //尝试关闭文本文件
        fprintf(stderr, "Error closing file \"课程信息表.txt\".\n");
    else
        fprintf(stdout, "save subject_txt_file successfully\n");
}


/***************添加课程信息到二进制文件*****************
 * 添加课程到subject.dat文件中
 * 通过传入课程信息结构体指针的方式传入结构体信息到文件
*********************************************************/
void append_subject(SUBJECT * subject_append) //待添加的课程信息结构体指针
{
    FILE * subject_b_file;          //二进制文件指针 
    SUBJECT * subject_read;         //从二进制文件中读出的课程信息结构体指针
    int flag = 0;                   //设置判断标志位,0表示课程信息未添加,1表示课程信息已存在

    //尝试以更新二进制模式打开文件,如果文件打开失败,则猜测可能是文件不存在
    //然后尝试以append二进制模式添加一个文件,如果文件真的不存在则新建一个文件
    //如果创建失败,则返回错误信息,并且退出程序
    //如果创建成功,则关闭文件
    //然后再次以更新二进制模式打开文件
    if ( (subject_b_file = fopen("subject.dat", "r+b")) == NULL)
    {
        if ( (subject_b_file = fopen("subject.dat", "ab")) == NULL)
        {
            fprintf(stderr, "Can't creat file \"subject.dat\".\n");
            exit(EXIT_FAILURE);
        }
        if ( fclose(subject_b_file) == EOF)
            fprintf(stderr, "Error closing file \"subject.dat\".\n");

        if( (subject_b_file = fopen("subject.dat", "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and creat file \"subject.dat\".\n");
            exit(EXIT_FAILURE);
        }
    }


    rewind(subject_b_file);           //定位到二进制文件开始
    while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
    {
        if (1)               //比对课程ID,如果发现重复则提示数据重复并取消添加
        {
            flag = 1;                                       //flag为1表示课程信息存在
            fprintf(stdout, "课程信息已存在,无需重复添加!");
            break;                                          //终止遍历文件
        }
    }

    //如果课程信息未添加,则定位到文件末尾,添加课程信息到二进制文件中
    if (flag == 0)
    {
        fseek(subject_b_file, 0L, SEEK_END); //定位至文件结尾

        //尝试写入subject_append信息到二进制文件中
        if ( fwrite(subject_append, sizeof(SUBJECT), 1, subject_b_file) != 1)
            fprintf(stderr, "Error writing subject_append to file \"subject.dat\".");
        else
            fprintf(stdout, "append subject successfully\n");
    }


    //尝试关闭二进制文件
    if (fclose(subject_b_file) == EOF)
        fprintf(stderr, "Error closing file \"subject.dat\"\n");
}


/*******************************************************************
 * 查询课程信息
 * 通过给出的课程ID
 * 从subject.dat里面查找学生数据
 * 比较判断是否存在这个课程
 * 若存在则将搜索权交给search_database_subject()去搜索课程的选课情况信息
********************************************************************/
int search_subject(const char * ID)   //搜索的课程ID字符串指针
{   
    FILE * subject_b_file;         //二进制文件指针
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));        //从二进制文件中读取的课程信息结构体

    //从student.dat二进制文件中读取课程信息结构体
    if ( (subject_b_file = fopen("subject.dat", "rb")) != NULL) //如果文件打开成功
    {
        while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
            if( strcmp(ID, (subject_read -> ID)) == 0)                                             //比对课程ID,如果符合则输出课程信息退出程序
            {
                fprintf(stdout, "课程代码:%s 课程名称:%s 课程性质:%s 总学时:%d 学分:%d 开课学期:%d 课程容量:%d\n",
                                                                                            subject_read -> ID,
                                                                                            subject_read -> NAME,
                                                                                            subject_read -> NATURE,
                                                                                            subject_read -> PERIOD,
                                                                                            subject_read -> CREDIT,
                                                                                            subject_read -> START,
                                                                                            subject_read -> MAX_SELECTED
                                                                                            );
                if ( fclose(subject_b_file) == EOF )
                    fprintf(stderr, "Error closing file \"subject.dat\".\n");
                return 1;                       //函数返回值为1表示找到该课程
            }
            else
                fprintf(stdout, "Sorry, can't find subject \"%s\".\n", ID);
    }
    else
        fprintf(stdout, "Sorry, can't find file \"subject.dat\"\n");
    
    
    return 0;               //函数返回值为0表示找不到该课程

}
