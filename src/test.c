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
                                        "BS123456",
                                        "形式与政策",
                                        "必修",
                                        48,
                                        4,
                                        2,
                                        30,
                                        100
                                    },
                                    {
                                        "B16020514",
                                        "任强",
                                        "男",
                                        21,
                                        "电磁场与无线技术",
                                        "B160205",
                                        "15295518250"
                                    }
    };
    
    DATABASE * database_current_ptr = &database_current;
    search_database_subject(database_current.subject.ID);
    fprintf(stdout, "学号:%s 姓名:%s 性别:%s 年龄:%d 专业:%s 班级:%s 联系方式:%s\n",
                                                                                            (database_current_ptr -> student).ID,
                                                                                            (database_current_ptr -> student).NAME,
                                                                                            (database_current_ptr -> student).SEX,
                                                                                            (database_current_ptr -> student).AGE,
                                                                                            (database_current_ptr -> student).MAJOR,
                                                                                            (database_current_ptr -> student).CLASS,
                                                                                            (database_current_ptr -> student).NUMBER
                                                                                            );

    return 0;

}

