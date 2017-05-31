/*********************************************************************************************
	> File Name: database.c
	> Author:
	> Mail:
	> Created Time: 2017年05月23日 星期二 10时29分03秒
    > Featurs: 声明一个结构体,保存每个选课的学生和其选择的课程.
 ********************************************************************************************/

//头文件
#include "header/database.h"

//测试通过
/*****************************************************************
 * 将学生选课信息从二进制文件中读取并且显示
 * 由于系统不同,所以产生的二进制文件或具有不可移植性
 * 甚至同一个系统的不同编译设置也可能会导致不可移植性
 * ****使用函数之前需要创建文件,否则可能无法正常工作****
******************************************************************/
void show_database_info(void)
{
    FILE * database_b_file;                 //二进制文件指针
    FILE * subject_b_file;
    int count = 0;
    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));        //从二进制文件中读取的课程信息结构体
    char * file_name = (char *)malloc((SUBJECT_ID_LEN + 5) * sizeof(char)); //课程名称字符串指针

    DATABASE * database_read = (DATABASE *)malloc(sizeof(DATABASE));//从二进制文件中读出的数据库结构体,并且申请内存

    if ( (subject_b_file = fopen("subject.dat", "rb")) != NULL )
    {
        while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
        {
            //将课程ID复制到file_name指向的地址空间里同时申请内存
            //返回值为指向file_name的二级指针(不使用)
            strcpy(file_name, subject_read -> ID);
            //将".dat"文件后缀复制到file_name指向的地址空间后面,并且覆盖原有的\0结束符
            strcat(file_name, ".dat");

            //测试输出搜索的文件名
            //fprintf(stdout, "search filename: \"%s\"\n", file_name);

            if ( (database_b_file = fopen(file_name, "rb")) != NULL)
            {
                count = 0;
                rewind(database_b_file);              //定位到二进制文件开始
                while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
                {
                    count++; //count
                    fprintf(stdout, "课程ID:%s 课程名称:%s 学生ID:%s 学生姓名:%s\n",
                                                                                    (database_read -> subject).ID,
                                                                                    (database_read -> subject).NAME,
                                                                                    (database_read -> student).ID,
                                                                                    (database_read -> student).NAME
                                                                                    );
                }
                fprintf(stdout, "count : %d\n", count);
                //尝试关闭文件如果无法正常关闭则报错
                if ( fclose(database_b_file) == EOF)
                    fprintf(stderr, "Error closing file \"%s\".\n", file_name);
            }
        }
        if ( fclose(subject_b_file) == EOF)
            fprintf(stderr, "Error closing file \"subject.dat\".\n");
    }
    else
        fprintf(stdout, "file \"subject.dat\" doesn't exit.\n");

    free(subject_read);
    free(database_read);
    free(file_name);
}

//测试通过
/******************************************************************************************
 *从二进制文件中读取学生信息并且保存到文本文件中以便查阅
*******************************************************************************************/
void save_database_txt(void)
{
    FILE * database_b_file;                 //二进制文件指针
    FILE * subject_b_file;
    FILE * database_t_file;                 //文本文件指针

    SUBJECT * subject_read = (SUBJECT *)malloc(sizeof(SUBJECT));        //从二进制文件中读取的课程信息结构体
    char * file_name = (char *)malloc((SUBJECT_ID_LEN + 5) * sizeof(char)); //课程名称字符串指针

    DATABASE * database_read = (DATABASE *)malloc(sizeof(DATABASE));//从二进制文件中读出的数据库结构体,并且申请内存

    if ( (subject_b_file = fopen("subject.dat", "rb")) != NULL )
    {
        while ( fread(subject_read, sizeof(SUBJECT), 1, subject_b_file) == 1)
        {
            //将课程ID复制到file_name指向的地址空间里同时申请内存
            //返回值为指向file_name的二级指针(不使用)
            strcpy(file_name, subject_read -> ID);
            //将".dat"文件后缀复制到file_name指向的地址空间后面,并且覆盖原有的\0结束符
            strcat(file_name, ".dat");

            //输出搜索的文件名
            //fprintf(stdout, "search filename: \"%s\"\n", file_name);

            if ( ((database_b_file = fopen(file_name, "rb")) != NULL) && ((database_t_file = fopen("subject_class.txt", "w+")) != NULL) )
            {
                rewind(database_b_file);              //定位到二进制文件开始
                while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
                    fprintf(database_t_file, "SUBJECT_ID:%s SUBJECT_NAME:%s STUDENT_ID:%s STUDENT_NAME:%s\n",
                                                                                    (database_read -> subject).ID,
                                                                                    (database_read -> subject).NAME,
                                                                                    (database_read -> student).ID,
                                                                                    (database_read -> student).NAME
                                                                                    );
                //尝试关闭文件如果无法正常关闭则报错
                if ( fclose(database_b_file) == EOF)
                    fprintf(stderr, "Error closing file \"%s\".\n", file_name);
                if ( fclose (database_t_file) == EOF)
                    fprintf(stderr, "Error closing file \"subject_class.txt\".\n");
                else
                    fprintf(stdout, "save database_txt_file successfully!\n");
            }
        }
        if ( fclose(subject_b_file) == EOF)
            fprintf(stderr, "Error closing file \"subject.dat\".\n");
    }
    else
        fprintf(stdout, "file \"subject.dat\" doesn't exit.\n");

    free(subject_read);
    free(database_read);
    free(file_name);
}

//调试成功
/***************添加选课信息到二进制文件*****************
 * 添加选课信息到database.dat文件中
 * 通过传入选课信息结构体指针的方式传入结构体信息到文件
*********************************************************/
void append_database(const DATABASE * database_append) //待添加的课程信息结构体指针
{
    FILE * database_b_file;          //二进制文件指针
    DATABASE * database_read = (DATABASE *)malloc(sizeof(DATABASE));        //从文件中读出的选课信息结构体指针,并且申请内存
    int flag = 0;                    //设置判断标志位,0表示选课信息未添加,1表示选课信息已存在
    char * file_name = (char *)malloc( (SUBJECT_ID_LEN + 5) * sizeof(char) ); //申请内存,存储用于搜索的文件名

    //将课程ID复制到file_name指向的地址空间里同时申请内存
    //返回值为指向file_name的二级指针(不使用)
    strcpy(file_name, (database_append -> subject).ID);
    //将".dat"文件后缀复制到file_name指向的地址空间后面,并且覆盖原有的\0结束符
    strcat(file_name, ".dat");

    //测试输出搜索的文件名
    //fprintf(stdout, "filename: \"%s\"\n", file_name);

    //尝试以更新二进制模式打开文件,如果文件打开失败,则猜测可能是文件不存在
    //然后尝试以append二进制模式添加一个文件,如果文件真的不存在则新建一个文件
    //如果创建失败,则返回错误信息,并且退出程序
    //如果创建成功,则关闭文件
    //然后再次以更新二进制模式打开文件
    if ( (database_b_file = fopen(file_name, "r+b")) == NULL)
    {
        if ( (database_b_file = fopen(file_name, "ab")) == NULL)
        {
            fprintf(stderr, "Can't creat file \"%s\".\n", file_name);
            exit(EXIT_FAILURE);
        }
        if ( fclose(database_b_file) == EOF)
            fprintf(stderr, "Error closing file \"%s\".\n", file_name);

        if( (database_b_file = fopen(file_name, "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and create file \"%s\".\n", file_name);
            exit(EXIT_FAILURE);
        }
    }

    rewind(database_b_file);           //定位到二进制文件开始
    while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
    {
        if (strcmp( (database_append -> student).ID, (database_read -> student).ID ) == 0)//比对学生ID和课程ID,如果发现两者同时重复则提示数据重复并取消添加
        {
            flag = 1;                                       //flag为1表示选课信息存在
            fprintf(stdout, "database-class exists!\n");
            break;                                          //终止遍历文件
        }
    }

    //如果选课信息未添加,则定位到文件末尾,添加选课信息到二进制文件中
    if (flag == 0)
    {
        fseek(database_b_file, 0L, SEEK_END); //定位至文件结尾

        //尝试写入database_append信息到二进制文件中
        if ( fwrite(database_append, sizeof(DATABASE), 1, database_b_file) != 1)
            fprintf(stderr, "Error writing database_append to file \"%s\".\n", file_name);
        else
            fprintf(stdout, "append database successfully\n");
    }


    //尝试关闭二进制文件
    if (fclose(database_b_file) == EOF)
        fprintf(stderr, "Error closing file \"%s\"\n", file_name);

    free(file_name);
    free(database_read);
}


//调试成功
/**************************************************************************
 *ID is subject's ID
***************************************************************************/
void search_database_subject(const char * ID)   //搜索的文件名字符串指针
{
    //将每一门的课程保存在文件里,文件名为课程的ID
    //搜索文件的原理为在文件都可读的权限下,尝试打开,
    //如果无法打开则搜索不到文件,
    //如果搜索到文件名则输出文件结构体中的信息

    FILE * database_b_file;         //二进制文件指针
    DATABASE * database_read = (DATABASE *)malloc(sizeof(DATABASE));       //从二进制文件中读取的数据库结构体
    char * file_name = (char *)malloc( (SUBJECT_ID_LEN + 5) * sizeof(char) ); //申请内存,存储用于搜索的文件名
    int flag = 1;                   //判断文件里有没有选课信息结构体,即该课程有没有被学生选择,
                                    //0为课程至少被选择一次,1为课程未被选择
    //将课程ID复制到file_name指向的地址空间里同时申请内存
    //返回值为指向file_name的二级指针(不使用)
    strcpy(file_name, ID);
    //将".dat"文件后缀复制到file_name指向的地址空间后面,并且覆盖原有的\0结束符
    strcat(file_name, ".dat");

    //测试输出搜索的文件名
    //fprintf(stdout, "filename: \"%s\"\n", file_name);

    //搜索文件是否存在
    //如果搜索到则从第一个结构体里读取出选课信息结构体,
    //然后输出课程信息结构体的基本信息,
    //********(如果可能的话,还可以从最后一个结构体读出课程当前的已选容量)
    if ( (database_b_file = fopen(file_name, "rb")) != NULL) //如果文件打开成功
    {
        while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
        {
            flag = 0;   //标记课程被选择过
            fprintf(stdout, "STUDENT : \nID:%s NAME:%s SEX:%s AGE:%d MAJOR:%s CLASS:%s PHONENUMBER:%s\n",
                                                                                            (database_read -> student).ID,
                                                                                            (database_read -> student).NAME,
                                                                                            (database_read -> student).SEX,
                                                                                            (database_read -> student).AGE,
                                                                                            (database_read -> student).MAJOR,
                                                                                            (database_read -> student).CLASS,
                                                                                            (database_read -> student).NUMBER
                                                                                            );
        }
        if (flag == 1) //课程未被选择
            fprintf(stdout, "subject has not be selected.\n");

        if ( fclose(database_b_file) == EOF )
            fprintf(stderr, "Error closing file \"%s\".\n", file_name);
    }
    else
        fprintf(stdout, "subject \"%s\" has not be selected.\n", ID);

    free(file_name); //释放内存
    free(database_read);
}


/*******************************************************
*delete by search
*******************************************************/
void delete_database(const char * student_ID, const char * subject_ID)
{
    //将每一门的课程保存在文件里,文件名为课程的ID
    //搜索文件的原理为在文件都可读的权限下,尝试打开,
    //如果无法打开则搜索不到文件

    FILE * database_b_file;         //二进制文件指针
    FILE * temporary_file;          //teporary file

    DATABASE * database_read = (DATABASE *)malloc(sizeof(DATABASE));       //从二进制文件中读取的数据库结构体

    int flag = 1;
    char * file_name = (char *)malloc( (SUBJECT_ID_LEN + 5) * sizeof(char) ); //申请内存,存储用于搜索的文件名
    //将课程ID复制到file_name指向的地址空间里同时申请内存
    //返回值为指向file_name的二级指针(不使用)
    strcpy(file_name, subject_ID);
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
    if ( (database_b_file = fopen(file_name, "rb")) != NULL) //如果文件打开成功
    {
        while ( fread(database_read, sizeof(DATABASE), 1, database_b_file) == 1)
        {
            if (strcmp(student_ID, (database_read -> student).ID) == 0)
            {
                flag = 0;
                continue;
            }
            fwrite(database_read, sizeof(DATABASE), 1, temporary_file);
        }

        if (flag == 1) //课程未被选择
            fprintf(stdout, "subject has not be selected by this student.\n");

        if ( fclose(database_b_file) == EOF )
            fprintf(stderr, "Error closing file \"%s\".\n", file_name);
        if ( fclose(temporary_file) == EOF )
            fprintf(stderr, "Error closing file \"temporary\"\n");
    }
    else
        fprintf(stdout, "subject \"%s\" has not be selected.\n", subject_ID);

    //remove subject file
    remove(file_name);
    //rename  to subject file
    rename("temporary", file_name);

    free(file_name); //释放内存
    free(database_read);
}
