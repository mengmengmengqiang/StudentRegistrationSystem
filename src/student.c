/*************************************************************************
	> File Name: student.c
	> Author:
	> Mail:
	> Created Time: 2017
    > Features:
 ************************************************************************/

#include "header/student.h"


void show_student_info(void)
{
    FILE * student_b_file;    
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));
    int count = 0;
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Error, file \"student.dat\" doesn't exits.\n");
        return;
    }

    rewind(student_b_file);           
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
        {
            count++;
            fprintf(stdout, "ID:%s NAME:%s SEX:%s AGE:%d MAJOR:%s CLASS:%s PHONENUMBER:%s\n",
                                                                                        student_read -> ID,
                                                                                        student_read -> NAME,
                                                                                        student_read -> SEX,
                                                                                        student_read -> AGE,
                                                                                        student_read -> MAJOR,
                                                                                        student_read -> CLASS,
                                                                                        student_read -> NUMBER
                                                                                        );
        }
    fprintf(stdout, "count : %d\n", count);

    if (fclose(student_b_file) == EOF)
        fprintf(stderr, "Error closing file \"student.dat\"\n");
    free(student_read);
}


void save_student_txt(void)
{
    FILE * student_b_file; 
    FILE * student_t_file; 
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT)); 
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Error, file \"student.dat\" doesn't exits.\n");
        return;
    }

    if ( (student_t_file = fopen("student_info.txt", "w")) == NULL)
    {
        fprintf(stderr, "Cant't open or create file \"student_info.txt\".\n");
        return;
    }
    
    rewind(student_b_file);           
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1) 
        fprintf(student_t_file, "ID:%s NAME:%s SEX:%s AGE:%d MAJOR:%s CLASS:%s PHONENUMBER:%s\n",
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
    if (fclose(student_t_file) == EOF) 
        fprintf(stderr, "Error closing file \"student_info.txt\"\n");
    else
        fprintf(stdout, "save student_txt_file successfully!\n");

    free(student_read);
}


void append_student(STUDENT * student_append) 
{
    FILE * student_b_file;          
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT)); 
    int flag = 0;                   
    if ( (student_b_file = fopen("student.dat", "r+b")) == NULL)
    {
        if ( (student_b_file = fopen("student.dat", "ab")) == NULL)
        {
            fprintf(stderr, "Can't create file \"student.dat\".\n");
            return;
        }
        if ( fclose(student_b_file) == EOF)
            fprintf(stderr, "Error closing file \"student.dat\".\n");

        if( (student_b_file = fopen("student.dat", "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and create file \"student.dat\".\n");
            return;
        }
    }

    rewind(student_b_file);           
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
    {
        if (strcmp(student_read -> ID, student_append -> ID) == 0)               
        {
            flag = 1;                                       
            fprintf(stdout, "student exists!\n");
            break;                                          
        }
    }

    
    if (flag == 0)
    {
        fseek(student_b_file, 0L, SEEK_END); 

        if ( fwrite(student_append, sizeof(STUDENT), 1, student_b_file) != 1)
            fprintf(stderr, "Error writing student_append to file \"student.dat\".\n");
        else
            fprintf(stdout, "append student successfully\n");
    }


    if (fclose(student_b_file) == EOF)
        fprintf(stderr, "Error closing file \"student.dat\"\n");
    free(student_read);
}



STUDENT  search_student(const char * ID)   
{
    FILE * student_b_file;         
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));        

    if ( (student_b_file = fopen("student.dat", "rb")) != NULL) 
    {
        while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
            if( strcmp(ID, (student_read -> ID)) == 0)                                             
            {
                fprintf(stdout, "ID:%s NAME:%s SEX:%s AGE:%d MAJOR:%s CLASS:%s PHONENUMBER:%s\n",
                                                                                            student_read -> ID,
                                                                                            student_read -> NAME,
                                                                                            student_read -> SEX,
                                                                                            student_read -> AGE,
                                                                                            student_read -> MAJOR,
                                                                                            student_read -> CLASS,
                                                                                            student_read -> NUMBER
                                                                                            );
                if ( fclose(student_b_file) == EOF )
                    fprintf(stderr, "Error closing file \"student.dat\".\n");
                return *student_read;                       
            }
    }
    else
        fprintf(stdout, "Sorry, can't find student \"%s\".\n", ID);

    free(student_read);
}

/*******************************************************
*delete by search
*ID is student's ID
*******************************************************/
void delete_student(const char * ID)
{
    FILE * student_b_file;         //二进制文件指针
    FILE * temporary_file;          //teporary file

    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));       //从二进制文件中读取的数据库结构体


    if ( (temporary_file = fopen("temporary", "wb")) == NULL)
        fprintf(stderr, "error create file \"temporary\"\n");
    //测试输出搜索的文件名
    //fprintf(stdout, "filename: \"%s\"\n", file_name);

    //搜索文件是否存在
    //如果搜索到则从第一个结构体里读取出选课信息结构体,
    //然后输出课程信息结构体的基本信息,
    //********(如果可能的话,还可以从最后一个结构体读出课程当前的已选容量)
    if ( (student_b_file = fopen("student.dat", "rb")) != NULL) //如果文件打开成功
    {
        while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
        {
            if (strcmp(ID, student_read -> ID) == 0)
                continue;
            fwrite(student_read, sizeof(STUDENT), 1, temporary_file);
        }

        if ( fclose(student_b_file) == EOF )
            fprintf(stderr, "Error closing file \"student.dat\".\n");
        if ( fclose(temporary_file) == EOF )
            fprintf(stderr, "Error closing file \"temporary\"\n");
    }
    else
        fprintf(stdout, "No students informations.\n");

    //remove student.dat file
    remove("student.dat");
    //rename  to student.dat file
    rename("temporary", "student.dat");

    free(student_read);
}


/*************************************************************
*edit by search
**************************************************************/
void edit_student(const char * ID)
{
    FILE * student_b_file;         
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));        
    if ( (student_b_file = fopen("student.dat", "r+b")) != NULL) 
    {
        while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
            if( strcmp(ID, (student_read -> ID)) == 0)                                             
            {
                fprintf(stdout, "ID:%s NAME:%s SEX:%s AGE:%d MAJOR:%s CLASS:%s PHONENUMBER:%s\n",
                                                                                            student_read -> ID,
                                                                                            student_read -> NAME,
                                                                                            student_read -> SEX,
                                                                                            student_read -> AGE,
                                                                                            student_read -> MAJOR,
                                                                                            student_read -> CLASS,
                                                                                            student_read -> NUMBER
                                                                                            );
                student_scanf(
                            student_read -> ID,
                            student_read -> NAME,
                            student_read -> SEX,
                            &(student_read -> AGE),
                            student_read -> MAJOR,
                            student_read -> CLASS,
                            student_read -> NUMBER
                            );

                if (fseek(student_b_file, -sizeof(STUDENT), SEEK_CUR) != 0)
                    fprintf(stderr, "error fseek\n");
                if (fwrite(student_read, sizeof(STUDENT), 1, student_b_file) != 1)
                    fprintf(stdout, "write failed\n");

                if ( fclose(student_b_file) == EOF )
                    fprintf(stderr, "Error closing file \"student.dat\".\n");
            }
    }
    else
        fprintf(stdout, "Sorry, can't find student \"%s\".\n", ID);

    free(student_read);
}
