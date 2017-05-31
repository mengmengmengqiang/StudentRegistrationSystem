/*************************************************************************
	> File Name: password.h
	> Author: 
	> Mail: 
	> Created Time: 2017年05月30日 星期二 18时42分13秒
 ************************************************************************/

#ifndef _PASSWORD_H
#define _PASSWORD_H

#include "stdio.h"
#include "termios.h"
#include "unistd.h"
#include "string.h"
#include "stdbool.h"

#define MAX_PASSWD_LEN 16
#define ADMIN_PASSWD "njupt"

int  checkpasswd(void);
#endif
