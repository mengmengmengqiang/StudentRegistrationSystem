/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月23日 星期二 20时12分16秒
    > Features: test my API in header file.
 ************************************************************************/
//添加头文件
#include "header/database.h"

int main(void)
{
    DATABASE database_current  = {
                                    1,
                                    {
                                        "BS123457",
                                        "形式与政策",
                                        "必修",
                                        48,
                                        4,
                                        2,
                                        30,
                                        100
                                    },
                                    {
                                        "B16020515",
                                        "任强",
                                        "男",
                                        21,
                                        "电磁场与无线技术",
                                        "B160205",
                                        "15295518250"
                                    }
    };

    STUDENT student_current = {
                                        "B16020514",
                                        "任强",
                                        "男",
                                        21,
                                        "电磁场与无线技术",
                                        "B160205",
                                        "15295518250"

    };

    SUBJECT subject_current = {
                                        "BS123455",
                                        "形式与政策",
                                        "必修",
                                        48,
                                        4,
                                        2,
                                        30,
                                        100
                                    };

    DATABASE * database_current_ptr = &database_current;
    STUDENT * student_current_ptr = &student_current;
    SUBJECT * subject_current_ptr = &subject_current;

    fprintf(stdout, "\n初始化测试:\n\t--> 学号:%s 姓名:%s 性别:%s 年龄:%d 专业:%s 班级:%s 联系方式:%s",
                                                                                            (database_current_ptr -> student).ID,
                                                                                            (database_current_ptr -> student).NAME,
                                                                                            (database_current_ptr -> student).SEX,
                                                                                            (database_current_ptr -> student).AGE,
                                                                                            (database_current_ptr -> student).MAJOR,
                                                                                            (database_current_ptr -> student).CLASS,
                                                                                            (database_current_ptr -> student).NUMBER
                                                                                            );
    
    //
    fprintf(stdout, "\nappend_student(STUDENT *) 测试:\n\t--> ");
    append_student(student_current_ptr);

    fprintf(stdout, "\nappend_subject(SUBJECT *) 测试:\n\t--> ");
    append_subject(subject_current_ptr);

    fprintf(stdout, "\nappend_database(DATABASE *)测试:\n\t--> ");
    append_database(database_current_ptr);
    
    //
    fprintf(stdout, "\nsearch_student(char * ID) 测试:\n\t--> ");
    search_student(student_current_ptr -> ID);

    fprintf(stdout, "\nsearch_subject(char * ID) 测试:\n\t--> ");
    search_subject(subject_current_ptr -> ID);

    printf("\nsearch_database_subject(char * subject_ID) 测试:\n\t--> ");
    search_database_subject(database_current.subject.ID);
    
    //
    fprintf(stdout, "\nshow_student_info(void) 测试:\n\t--> ");
    show_student_info();

    fprintf(stdout, "\nsave_student_txt() 测试:\n\t--> ");
    save_student_txt();
    
    //
    fprintf(stdout, "\nshow_subject_info() 测试:\n\t--> ");
    show_subject_info();
    
    fprintf(stdout, "\nsave_subject_txt() 测试:\n\t--> ");
    save_subject_txt();
    
    //
    fprintf(stdout, "\nshow_database_info(void) 测试:\n\t--> ");
    show_database_info();

    fprintf(stdout, "\nsave_database_txt(void) 测试:\n\t--> ");
    save_database_txt();

    return 0;

}

