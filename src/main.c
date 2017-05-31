/*************************************************************************
	> File Name: test.c
	> Author:
	> Mail:
	> Created Time: 2017年05月23日 星期二 20时12分16秒
    > Features: test my API in header file.
 ************************************************************************/
//添加头文件
#include "header/database.h"
#include "header/passwd.h"

int main(void)
{
    SUBJECT * subject_ptr = (SUBJECT *)malloc(sizeof(SUBJECT));
    STUDENT * student_ptr = (STUDENT *)malloc(sizeof(STUDENT));
    STUDENT  student;
    SUBJECT  subject;
    DATABASE * database_ptr = (DATABASE *)malloc(sizeof(DATABASE));

    int login_mode = 0;             //login_mode_flag

    int student_mode = 0;           //student_mode_flag

    int admin_mode = 0;             //admin_mode_flag
    int admin_add_mode = 0;         //admin_add_mode_flag
    int admin_search_mode = 0;      //admin_search_mode_flag
    int admin_list_mode = 0;        //admin_list_mode_flag
    int admin_edit_mode = 0;        //admin_edit_mode_flag
    int admin_delete_mode = 0;      //admin_delete_mode_flag

    //登录模块
    LOGIN:
        fprintf(stdout, "1 : STUDENT LOGIN(NOPASSWD)\n2 : ADMIN LOGIN(PASSWD)\n3 : EXIT\n");

        if (s_scanf("%d", &login_mode) != 1)
            goto LOGIN;
        else if (login_mode == 1) //学生登录模式
        {
            fprintf(stdout, "hello student!\n");
            goto STUDENT_MODE; //跳入学生模块
        }
        else if (login_mode == 2) //admin 登录模式
        {
            if ( checkpasswd() == 1) //登录成功
            {
                goto ADMIN_MODE; //跳入管理员模块
            }
            else
                goto LOGIN;
        }
        else if (login_mode == 3)
            goto EXIT;
        else
            goto LOGIN;

    //学生模块
    STUDENT_MODE:
        fprintf(stdout, "1 : SELECT SUBJECT\n2 : SEARCH SUBJECT\n3 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &student_mode) != 1)
            goto STUDENT_MODE;
        else if (student_mode == 1) //选课模式
        {
            char * student_ID = (char *)malloc(sizeof(STUDENT_ID_LEN));
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));

            do
            {
                fprintf(stdout, "please enter student's ID(string)\n");
            }while(scanf("%s", student_ID) != 1);

            do
            {
                fprintf(stdout, "please enter subject's ID(string)\n");
            }while(scanf("%s", subject_ID) != 1);

            if ( (strcmp( (student = search_student(student_ID)).ID, student_ID) == 0) && (strcmp( (subject = search_subject(subject_ID)).ID, subject_ID) == 0) )
                {
                    database_ptr -> student = student;
                    database_ptr -> subject = subject;
                    append_database(database_ptr);
                }
            else
                fprintf(stdout, "student or subject doesn't exist.");
            free(student_ID);
            free(subject_ID);
            //free(student_ptr2); //malloc in function ,free out
            //free(subject_ptr2); //malloc in function, free out
            goto STUDENT_MODE;
        }
        else if (student_mode == 2) //查课模式
        {
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter subject's ID(string).\n");
            }
            while(scanf("%s", subject_ID) != 1);
            search_subject(subject_ID);

            free(subject_ID);
            goto STUDENT_MODE;
        }
        else if (student_mode == 3)
            goto LOGIN;
        else
            goto STUDENT_MODE;


    //管理员一级模块
    ADMIN_MODE:
        fprintf(stdout, "1 : ADD\n2 : SEARCH\n3 : LIST\n4 : EDIT\n5 : DELETE\n6 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &admin_mode) != 1)
            goto ADMIN_MODE;
        else if (admin_mode == 1) //添加模式
            goto ADMIN_ADD_MODE;
        else if (admin_mode == 2) //查询模式
            goto ADMIN_SEARCH_MODE;
        else if (admin_mode == 3) //显示功能
            goto ADMIN_LIST_MODE;
        else if (admin_mode == 4) //编辑功能
            goto ADMIN_EDIT_MODE;
        else if (admin_mode == 5) //删除功能
            goto ADMIN_DELETE_MODE;
        else if (admin_mode == 6) //back
            goto LOGIN;
        else
            goto ADMIN_MODE;

    //管理员二级模块
    ADMIN_ADD_MODE:
        fprintf(stdout, "1 : ADD STUDENT\n2 : ADD SUBJECT\n3 : ADD DATABASE\n4 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &admin_add_mode) != 1)
            goto ADMIN_ADD_MODE;
        else if (admin_add_mode == 1)
        {
            student_scanf(
                          student_ptr -> ID,
                          student_ptr -> NAME,
                          student_ptr -> SEX,
                          &(student_ptr -> AGE),
                          student_ptr -> MAJOR,
                          student_ptr -> CLASS,
                          student_ptr -> NUMBER
                          );
            append_student(student_ptr);
            goto ADMIN_ADD_MODE;
        }
        else if (admin_add_mode == 2)
        {
            subject_scanf(
                        subject_ptr -> ID,
                        subject_ptr -> NAME,
                        subject_ptr -> NATURE,
                        &(subject_ptr -> PERIOD),
                        &(subject_ptr -> CREDIT),
                        &(subject_ptr -> START),
                        &(subject_ptr -> SELECTED),
                        &(subject_ptr -> MAX_SELECTED)
                        );
            append_subject(subject_ptr);
            goto ADMIN_ADD_MODE;
        }
        else if (admin_add_mode == 3)
        {
            char * student_ID = (char *)malloc(sizeof(STUDENT_ID_LEN));
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter student's ID(string)\n");
            }while(scanf("%s", student_ID) != 1);

            do
            {
                fprintf(stdout, "please enter subject's ID(string)\n");
            }while(scanf("%s", subject_ID) != 1);

            if ( (strcmp( (student = search_student(student_ID)).ID, student_ID) == 0) && (strcmp( (subject = search_subject(subject_ID)).ID, subject_ID) == 0) )
                {
                    database_ptr -> student = student;
                    database_ptr -> subject = subject;
                    append_database(database_ptr);
                }
            else
                fprintf(stdout, "student or subject doesn't exist.\n");
            free(student_ID);
            free(subject_ID);
            goto ADMIN_ADD_MODE;
        }
        else if (admin_add_mode == 4)
            goto ADMIN_MODE; //back
        else
            goto ADMIN_ADD_MODE;

    //search
    ADMIN_SEARCH_MODE:
        fprintf(stdout, "1 : SEARCH STUDENT\n2 : SEARCH SUBJECT\n3 : SEARCH SUBJECT-CLASS\n4 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &admin_search_mode) != 1)
            goto ADMIN_SEARCH_MODE;
        else if (admin_search_mode == 1)
        {
            char * student_ID = (char *)malloc(sizeof(STUDENT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter student's ID(string).\n");
            }
            while(scanf("%s", student_ID) != 1);
            search_student(student_ID);
            free(student_ID);
            goto ADMIN_SEARCH_MODE;
        }
        else if (admin_search_mode == 2)
        {
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter subject's ID(string).\n");
            }
            while(scanf("%s", subject_ID) != 1);
            search_subject(subject_ID);
            free(subject_ID);
            goto ADMIN_SEARCH_MODE;
        }
        else if (admin_search_mode == 3)
        {
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter subject's ID(string).\n");
            }
            while(scanf("%s", subject_ID) != 1);

            search_database_subject(subject_ID);
            free(subject_ID);
            goto ADMIN_SEARCH_MODE;
        }
        else if (admin_search_mode == 4)
            goto ADMIN_MODE;
        else
            goto ADMIN_SEARCH_MODE;

    //
    ADMIN_LIST_MODE:
        fprintf(stdout, "1 : LIST STUDENT\n2 : LIST SUBJECT\n3 : LIST DATABASE\n4 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &admin_list_mode) != 1)
            goto ADMIN_LIST_MODE;
        else if (admin_list_mode == 1)
        {
            show_student_info();
            goto ADMIN_LIST_MODE;
        }
        else if (admin_list_mode == 2)
        {
            show_subject_info();
            goto ADMIN_LIST_MODE;
        }
        else if (admin_list_mode == 3)
        {
            show_database_info();
            goto ADMIN_LIST_MODE;
        }
        else if (admin_list_mode == 4)
            goto ADMIN_MODE;
        else
            goto ADMIN_LIST_MODE;

    ADMIN_EDIT_MODE:
        fprintf(stdout, "1 : EDIT STUDENT\n2 : EDIT SUBJECT\n3 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &admin_edit_mode) != 1)
            goto ADMIN_EDIT_MODE;
        else if (admin_edit_mode == 1)
        {
            char * student_ID = (char *)malloc(sizeof(STUDENT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter student's ID(string).\n");
            }
            while(scanf("%s", student_ID) != 1);
            edit_student(student_ID);
            free(student_ID);
            goto ADMIN_EDIT_MODE;
        }
        else if (admin_edit_mode == 2)
        {
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter subject's ID(string).\n");
            }
            while(scanf("%s", subject_ID) != 1);
            edit_subject(subject_ID);
            free(subject_ID);
            goto ADMIN_EDIT_MODE;
        }
        else if (admin_edit_mode == 3)
            goto ADMIN_MODE;
        else
            goto ADMIN_EDIT_MODE;

    ADMIN_DELETE_MODE:
        fprintf(stdout, "1 : DELETE STUDENT\n2 : DELETE SUBJECT\n3 : DELETE SUBJECT-CLASS\n4 : BACK\n");
        fprintf(stdout, "please select them by enter related number.\n");

        if (s_scanf("%d", &admin_delete_mode) != 1)
            goto ADMIN_DELETE_MODE;
        else if (admin_delete_mode == 1)
        {
            char * student_ID = (char *)malloc(sizeof(STUDENT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter student's ID(string).\n");
            }
            while(scanf("%s", student_ID) != 1);
            delete_student(student_ID);
            free(student_ID);
            goto ADMIN_DELETE_MODE;
        }
        else if (admin_delete_mode == 2)
        {
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));
            do
            {
                fprintf(stdout, "please enter subject's ID(string).\n");
            }
            while(scanf("%s", subject_ID) != 1);
            delete_subject(subject_ID);
            free(subject_ID);
            goto ADMIN_DELETE_MODE;
        }
        else if (admin_delete_mode == 3)
        {
            char * student_ID = (char *)malloc(sizeof(STUDENT_ID_LEN));
            char * subject_ID = (char *)malloc(sizeof(SUBJECT_ID_LEN));

            do
            {
                fprintf(stdout, "please enter student's ID(string)\n");
            }while(scanf("%s", student_ID) != 1);

            do
            {
                fprintf(stdout, "please enter subject's ID(string)\n");
            }while(scanf("%s", subject_ID) != 1);

            delete_database(student_ID, subject_ID);
            free(student_ID);
            free(subject_ID);
            goto ADMIN_DELETE_MODE;
        }
        else if (admin_delete_mode == 4)
            goto ADMIN_MODE; //back
        else
            goto ADMIN_DELETE_MODE;


    EXIT:
        save_student_txt();
        save_subject_txt();
        save_database_txt();

        free(student_ptr);
        free(subject_ptr);
        free(database_ptr);

        return 0;
}

