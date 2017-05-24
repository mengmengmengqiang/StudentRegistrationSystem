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
    
    search_database(database_current.subject.ID);

    return 0;

}

