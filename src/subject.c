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
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));                  //从二进制文件中读取的课程信息结构体指针
    int count = 0;
    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (subject_b_file = fopen("subject.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"subject.dat\", maybe you have not created it.\n");
        return;
    }

    rewind(subject_b_file);           //定位到文件开始
    while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
        {
            count++;
            fprintf(stdout, "ID:%s NAME:%s NATURE:%s PERIOD:%d CREDIT:%d START:%d SELECTED:%d MAX_SELECTED:%d\n",
                                                                                                             subject_read -> ID,
                                                                                                             subject_read -> NAME,
                                                                                                             subject_read -> NATURE,
                                                                                                             subject_read -> PERIOD,
                                                                                                             subject_read -> CREDIT,
                                                                                                             subject_read -> START,
                                                                                                             subject_read -> SELECTED,
                                                                                                             subject_read -> MAX_SELECTED
                                                                                                             );
        }

    fprintf(stdout, "count : %d\n", count);

    if (fclose(subject_b_file) == EOF)
        fprintf(stderr, "Error closing file \"subject.dat\".\n");
    free(subject_read);
}


/******************************************************************
 *保存课程信息到文本文件以便查阅
*******************************************************************/
void save_subject_txt(void)
{
    FILE * subject_b_file;    //二进制文件指针
    FILE * subject_t_file;    //文本文件指针
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));   //从二进制文件中读取的课程信息结构体指针

    //尝试以只读二进制模式打开文件,如果文件打开失败,则输出错误信息并且退出
    if ( (subject_b_file = fopen("subject.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Can't open file \"subject.dat\", maybe you have not created it.\n");
        return;
    }

    //尝试以写文本模式打开/创建文件,如果文件打开/创建失败,则输出错误信息并且退出
    if ( (subject_t_file = fopen("subject_info.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can't open or creat file \"subject_info.txt\".\n");
        return;
    }
    rewind(subject_b_file);           //定位到二进制文件开始
    while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1) //从二进制文件中读取数据保存到结构体中然后打印到文本文件中
        fprintf(subject_t_file, "ID:%s NAME:%s NATURE:%s PERIOD:%d CREDIT:%d START:%d SELECTED:%d MAX_SELECTED:%d",
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
        fprintf(stderr, "Error closing file \"subject_info.txt\".\n");
    else
        fprintf(stdout, "save subject_txt_file successfully\n");
    free(subject_read);
}


/***************添加课程信息到二进制文件*****************
 * 添加课程到subject.dat文件中
 * 通过传入课程信息结构体指针的方式传入结构体信息到文件
*********************************************************/
void append_subject(SUBJECT * subject_append) //待添加的课程信息结构体指针
{
    FILE * subject_b_file;          //二进制文件指针
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));         //从二进制文件中读出的课程信息结构体指针
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
            fprintf(stderr, "Can't create file \"subject.dat\".\n");
            return;
        }
        if ( fclose(subject_b_file) == EOF)
            fprintf(stderr, "Error closing file \"subject.dat\".\n");

        if( (subject_b_file = fopen("subject.dat", "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and creat file \"subject.dat\".\n");
            return;
        }
    }


    rewind(subject_b_file);           //定位到二进制文件开始
    while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
    {
        if (strcmp(subject_read -> ID, subject_append -> ID) == 0)               //比对课程ID,如果发现重复则提示数据重复并取消添加
        {
            flag = 1;                                       //flag为1表示课程信息存在
            fprintf(stdout, "subject exists!");
            break;                                          //终止遍历文件
        }
    }

    //如果课程信息未添加,则定位到文件末尾,添加课程信息到二进制文件中
    if (flag == 0)
    {
        fseek(subject_b_file, 0L, SEEK_END); //定位至文件结尾

        //尝试写入subject_append信息到二进制文件中
        if ( fwrite(subject_append, sizeof(SUBJECT), 1, subject_b_file) != 1)
            fprintf(stderr, "Error writing subject_append to file \"subject.dat\".\n");
        else
            fprintf(stdout, "append subject successfully\n");
    }


    //尝试关闭二进制文件
    if (fclose(subject_b_file) == EOF)
        fprintf(stderr, "Error closing file \"subject.dat\"\n");

    free(subject_read);
}


/*******************************************************************
 * 查询课程信息
 * 通过给出的课程ID
 * 从subject.dat里面查找学生数据
 * 比较判断是否存在这个课程
 * 若存在则将搜索权交给search_database_subject()去搜索课程的选课情况信息
********************************************************************/
SUBJECT search_subject(const char * ID)   //搜索的课程ID字符串指针
{
    FILE * subject_b_file;         //二进制文件指针
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));        //从二进制文件中读取的课程信息结构体

    //从student.dat二进制文件中读取课程信息结构体
    if ( (subject_b_file = fopen("subject.dat", "rb")) != NULL) //如果文件打开成功
    {
        while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
            if( strcmp(ID, (subject_read -> ID)) == 0)                                             //比对课程ID,如果符合则输出课程信息退出程序
            {
                fprintf(stdout, "ID:%s NAME:%s NATURE:%s PERIOD:%d CREDIT:%d START:%d MAX_SELECTED:%d\n",
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
                return *subject_read;                       //函数返回值为1表示找到该课程
            }
            else
                fprintf(stdout, "Sorry, can't find subject \"%s\".\n", ID);
    }
    else
        fprintf(stdout, "Sorry, can't find file \"subject.dat\"\n");

    free(subject_read);

}


/*******************************************************
*delete by search
*ID is subject's ID
*******************************************************/
void delete_subject(const char * ID)
{
    //将每一门的课程保存在文件里,文件名为课程的ID
    //搜索文件的原理为在文件都可读的权限下,尝试打开,
    //如果无法打开则搜索不到文件

    FILE * subject_b_file;         //二进制文件指针
    FILE * temporary_file;          //teporary file

    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));       //从二进制文件中读取的数据库结构体
    char * file_name = (char *)malloc( (SUBJECT_ID_LEN + 5) * sizeof(char) ); //申请内存,存储用于搜索的文件名
    //将课程ID复制到file_name指向的地址空间里同时申请内存
    //返回值为指向file_name的二级指针(不使用)
    strcpy(file_name, ID);
    //将".dat"文件后缀复制到file_name指向的地址空间后面,并且覆盖原有的\0结束符
    strcat(file_name, ".dat");

    if ( (temporary_file = fopen("temporary", "wb")) == NULL)
        fprintf(stderr, "error create file \"temporary\"\n");
    //测试输出搜索的文件名
    //fprintf(stdout, "filename: \"%s\"\n", file_name);

    //搜索文件是否存在
    //如果搜索到则从第一个结构体里读取出选课信息结构体,
    //然后输出课程信息结构体的基本信息,
    //********(如果可能的话,还可以从最后一个结构体读出课程当前的已选容量)
    if ( (subject_b_file = fopen("subject.dat", "rb")) != NULL) //如果文件打开成功
    {
        while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
        {
            if (strcmp(ID, subject_read -> ID) == 0)
            {
                remove(file_name); //delete related class file
                continue;
            }
            fwrite(subject_read, sizeof(SUBJECT), 1, temporary_file);
        }

        if ( fclose(subject_b_file) == EOF )
            fprintf(stderr, "Error closing file \"subject.dat\".\n");
        if ( fclose(temporary_file) == EOF )
            fprintf(stderr, "Error closing file \"temporary\"\n");
    }
    else
        fprintf(stdout, "No subjects informations.\n");

    //remove subject.dat file
    remove("subject.dat");
    //rename  to subject.dat file
    rename("temporary", "subject.dat");

    free(subject_read);
    free(file_name);
}


/*************************************************************
*edit by search
**************************************************************/
void edit_subject(const char * ID)
{
    FILE * subject_b_file;         
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));        
    if ( (subject_b_file = fopen("subject.dat", "r+b")) != NULL) 
    {
        while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
            if( strcmp(ID, (subject_read -> ID)) == 0)                                             
            {
                fprintf(stdout, "ID:%s NAME:%s NATURE:%s PERIOD:%d CREDIT:%d START:%d MAX_SELECTED:%d",
                                                                                            subject_read -> ID,
                                                                                            subject_read -> NAME,
                                                                                            subject_read -> NATURE,
                                                                                            subject_read -> PERIOD,
                                                                                            subject_read -> CREDIT,
                                                                                            subject_read -> START,
                                                                                            subject_read -> MAX_SELECTED
                                                                                            );
                subject_scanf(
                            subject_read -> ID,
                            subject_read -> NAME,
                            subject_read -> NATURE,
                            &(subject_read -> PERIOD),
                            &(subject_read -> CREDIT),
                            &(subject_read -> START),
                            &(subject_read -> SELECTED),
                            &(subject_read -> MAX_SELECTED)
                            );

                if (fseek(subject_b_file, -sizeof(SUBJECT), SEEK_CUR) != 0)
                    fprintf(stderr, "error fseek\n");
                if (fwrite(subject_read, sizeof(SUBJECT), 1, subject_b_file) != 1)
                    fprintf(stdout, "write failed.\n");

                if ( fclose(subject_b_file) == EOF )
                    fprintf(stderr, "Error closing file \"subject.dat\".\n");
            }
    }
    else
        fprintf(stdout, "Sorry, can't find subject \"%s\".\n", ID);

    free(subject_read);
}
