/*************************************************************************
	> File Name: passwd.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月30日 星期二 18时47分20秒
 ************************************************************************/

#include "header/passwd.h"

int checkpasswd(void)
{
    struct termios old;
    struct termios new;
    tcgetattr(0,&old);
    new = old;
    new.c_lflag &= ~(ECHO|ICANON);

    char passwd_stdin[20] = {0};
    char passwd_true[] = ADMIN_PASSWD;
    char ch;
    int i = 0;

    fprintf(stdout, "please enter admin passwd\n");
    
    while(1)
    {
        tcsetattr(0, TCSANOW, &new);//进入循环将stdin设置为不回显状态    
        scanf("%c",&ch);//在不回显状态下输入密码
        tcsetattr(0, TCSANOW, &old);//每次输入一个密码的字符就恢复正常回显状态
        if(i==20 || ch == '\n')//输入回车符表示密码输入完毕，退出循环；或者超出密码长度退出循环
            break;
        passwd_stdin[i] = ch;//将输入的单个字符依次存入数组中

        printf("*");//在回显状态下输出*
        i++;
    }
    /*比较从终端输入的密码与设定好的密码是否相同，相同打印一些信息，表示登陆成功；不同做出一些操作，对非正常登陆作出保护性措施*/
    if(!strcmp(passwd_stdin,passwd_true)){
        printf("\nwelcom admin!\n");
        return 1;
    }
    else
    {
        printf("\nsorry, passwd error\n");
        return 0;
    }
}
