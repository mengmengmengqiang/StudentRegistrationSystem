/*************************************************************************
	> File Name: student.c
	> Author:
	> Mail:
	> Created Time: 2017å¹´05æ23æ¥ ææäº 08æ¶53å43ç§
    > Features: å­¦çä¿¡æ¯ç»æå£°æ
    > Task: å­¦çå¯ä»¥å¯¹è¯¾ç¨ä¿¡æ¯è¿è¡æ¥è¯¢,éä¿®ç¬¦åè¦æ±çè¯¾ç¨,æ ¹æ®è¯¾ç¨ä¿¡æ¯åå­¦çä¿¡æ¯å®æå¯¹è¯¾ç¨çéä¿®.
 ************************************************************************/

#include "header/student.h"

/*********************æ¾ç¤ºå­¦çåºæ¬ä¿¡æ¯*********************
 *å°ä»å­¦çä¿¡æ¯äºè¿å¶æä»¶ä¸­è¯»åå­¦çä¿¡æ¯å¹¶ä¸æ¾ç¤ºåºæ¥
 *ç±äºç³»ç»ä¸å,æä»¥äº§ççæ°æ®æä»¶å¯è½ä¸å·æå¯ç§»æ¤æ§
 *çè³åä¸ä¸ªç³»ç»çä¸åç¼è¯è®¾ç½®ä¹å¯è½ä¼å¯¼è´ä¸å¯ç§»æ¤æ§
 *
 ***ä½¿ç¨å½æ°ä¹åéè¦åå»ºæä»¶,å¦åå¯è½æ æ³æ­£å¸¸å·¥ä½***
**********************************************************/
void show_student_info(void)
{
    FILE * student_b_file;    //äºè¿å¶æä»¶æé
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));//ä»æä»¶ä¸­è¯»åºçå­¦çç»æä½çæé,å¹¶ä¸åéåå­
    int count = 0;
    //å°è¯ä»¥åªè¯»äºè¿å¶æ¨¡å¼æå¼æä»¶,å¦ææä»¶æå¼å¤±è´¥,åè¾åºéè¯¯ä¿¡æ¯å¹¶ä¸éåº
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Error, file \"student.dat\" doesn't exits.\n");
        exit(EXIT_FAILURE);
    }

    rewind(student_b_file);           //å®ä½å°æä»¶å¼å§
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


/*******************ä¿å­å­¦çä¿¡æ¯å°ææ¬æä»¶*****************
 *ä»äºè¿å¶æä»¶ä¸­è¯»åå­¦çä¿¡æ¯å¹¶ä¿å­å°ææ¬æä»¶ä¸­ä»¥ä¾¿æ¥é
***********************************************************/
void save_student_txt(void)
{
    FILE * student_b_file; //äºè¿å¶æä»¶æé
    FILE * student_t_file; //ææ¬æä»¶æé
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT)); //ä»æä»¶ä¸­è¯»åºçå­¦çç»æä½æé,å¹¶ä¸åéåå­

    //å°è¯ä»¥åªè¯»äºè¿å¶æ¨¡å¼æå¼äºè¿å¶æä»¶,å¦ææä»¶æå¼å¤±è´¥,åè¾åºéè¯¯ä¿¡æ¯å¹¶ä¸éåº
    if ( (student_b_file = fopen("student.dat", "rb")) == NULL)
    {
        fprintf(stderr, "Error, file \"student.dat\" doesn't exits.\n");
        exit(EXIT_FAILURE);
    }

    //å°è¯ä»¥åææ¬æ¨¡å¼æå¼ææ¬æä»¶,å¦ææä»¶æå¼/åå»ºå¤±è´¥,åè¾åºéè¯¯ä¿¡æ¯å¹¶ä¸éåº
    if ( (student_t_file = fopen("student_info.txt", "w")) == NULL)
    {
        fprintf(stderr, "Cant't open or create file \"student_info.txt\".\n");
        exit(EXIT_FAILURE);
    }
    rewind(student_b_file);           //å®ä½å°äºè¿å¶æä»¶å¼å§
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1) //ä»äºè¿å¶æä»¶ä¸­è¯»åæ°æ®ä¿å­å°ç»æä½ä¸­ç¶åæå°å°ææ¬æä»¶ä¸­
        fprintf(student_t_file, "ID:%s NAME:%s SEX:%s AGE:%d MAJOR:%s CLASS:%s PHONENUMBER:%s\n",
                                                                                        student_read -> ID,
                                                                                        student_read -> NAME,
                                                                                        student_read -> SEX,
                                                                                        student_read -> AGE,
                                                                                        student_read -> MAJOR,
                                                                                        student_read -> CLASS,
                                                                                        student_read -> NUMBER
                                                                                        );
    if (fclose(student_b_file) == EOF) //å°è¯å³é­äºè¿å¶æä»¶
        fprintf(stderr, "Error closing file \"student.dat\"\n");
    if (fclose(student_t_file) == EOF) //å°è¯å³é­ææ¬æä»¶
        fprintf(stderr, "Error closing file \"student_info.txt\"\n");
    else
        fprintf(stdout, "save student_txt_file successfully!\n");

    free(student_read);
}


/***************æ·»å å­¦çä¿¡æ¯å°äºè¿å¶æä»¶*****************
 * æ·»å å­¦çå°student.datæä»¶ä¸­
 * éè¿ä¼ å¥å­¦çä¿¡æ¯ç»æä½æéçæ¹å¼ä¼ å¥ç»æä½ä¿¡æ¯å°æä»¶
*********************************************************/
void append_student(STUDENT * student_append) //å¾æ·»å çå­¦çä¿¡æ¯ç»æä½æé
{
    FILE * student_b_file;          //äºè¿å¶æä»¶æé
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT)); //ä»æä»¶ä¸­è¯»åºçå­¦çä¿¡æ¯ç»æä½æé,å¹¶ä¸åéåå­
    int flag = 0;                   //è®¾ç½®å¤æ­æ å¿ä½,0è¡¨ç¤ºå­¦çä¿¡æ¯æªæ·»å ,1è¡¨ç¤ºå­¦çä¿¡æ¯å·²å­å¨

    //å°è¯ä»¥æ´æ°äºè¿å¶æ¨¡å¼æå¼æä»¶,å¦ææä»¶æå¼å¤±è´¥,åçæµå¯è½æ¯æä»¶ä¸å­å¨
    //ç¶åå°è¯ä»¥appendäºè¿å¶æ¨¡å¼æ·»å ä¸ä¸ªæä»¶,å¦ææä»¶ççä¸å­å¨åæ°å»ºä¸ä¸ªæä»¶
    //å¦æåå»ºå¤±è´¥,åè¿åéè¯¯ä¿¡æ¯,å¹¶ä¸éåºç¨åº
    //å¦æåå»ºæå,åå³é­æä»¶
    //ç¶ååæ¬¡ä»¥æ´æ°äºè¿å¶æ¨¡å¼æå¼æä»¶
    if ( (student_b_file = fopen("student.dat", "r+b")) == NULL)
    {
        if ( (student_b_file = fopen("student.dat", "ab")) == NULL)
        {
            fprintf(stderr, "Can't create file \"student.dat\".\n");
            exit(EXIT_FAILURE);
        }
        if ( fclose(student_b_file) == EOF)
            fprintf(stderr, "Error closing file \"student.dat\".\n");

        if( (student_b_file = fopen("student.dat", "r+b")) == NULL)
        {
            fprintf(stderr, "Error, Can't open and create file \"student.dat\".\n");
            exit(EXIT_FAILURE);
        }
    }

    rewind(student_b_file);           //å®ä½å°äºè¿å¶æä»¶å¼å§
    while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
    {
        if (strcmp(student_read -> ID, student_append -> ID) == 0)               //æ¯å¯¹å­¦çID,å¦æåç°éå¤åæç¤ºæ°æ®éå¤å¹¶åæ¶æ·»å 
        {
            flag = 1;                                       //flagä¸º1è¡¨ç¤ºå­¦çä¿¡æ¯å­å¨
            fprintf(stdout, "student exists!\n");
            break;                                          //ç»æ­¢éåæä»¶
        }
    }

    //å¦æå­¦çä¿¡æ¯æªæ·»å ,åå®ä½å°æä»¶æ«å°¾,æ·»å å­¦çä¿¡æ¯å°äºè¿å¶æä»¶ä¸­
    if (flag == 0)
    {
        fseek(student_b_file, 0L, SEEK_END); //å®ä½è³æä»¶ç»å°¾

        //å°è¯åå¥student_appendä¿¡æ¯å°äºè¿å¶æä»¶ä¸­
        if ( fwrite(student_append, sizeof(STUDENT), 1, student_b_file) != 1)
            fprintf(stderr, "Error writing student_append to file \"student.dat\".\n");
        else
            fprintf(stdout, "append student successfully\n");
    }


    //å°è¯å³é­äºè¿å¶æä»¶
    if (fclose(student_b_file) == EOF)
        fprintf(stderr, "Error closing file \"student.dat\"\n");
    free(student_read);
}


/*******************************************************************
 * æ¥è¯¢å­¦çä¿¡æ¯
 * éè¿ç»åºçå­¦çID
 * ä»student.datéé¢æ¥æ¾å­¦çæ°æ®
 * æ¯è¾å¤æ­æ¯å¦å­å¨è¿ä¸ªå­¦ç
 * è¥å­å¨åå°æç´¢æäº¤ç»search_database_student()å»æç´¢å­¦ççè¯¾ç¨ä¿¡æ¯
********************************************************************/
STUDENT  search_student(const char * ID)   //æç´¢çå­¦çIDå­ç¬¦ä¸²æé
{
    FILE * student_b_file;         //äºè¿å¶æä»¶æé
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));        //ä»äºè¿å¶æä»¶ä¸­è¯»åçå­¦çä¿¡æ¯ç»æä½,å¹¶ä¸åéåå­

    //ä»student.datäºè¿å¶æä»¶ä¸­è¯»åå­¦çä¿¡æ¯ç»æä½
    if ( (student_b_file = fopen("student.dat", "rb")) != NULL) //å¦ææä»¶æå¼æå
    {
        while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
            if( strcmp(ID, (student_read -> ID)) == 0)                                             //æ¯å¯¹å­¦çID,å¦æç¬¦ååè¾åºå­¦çä¿¡æ¯,å¹¶ä¸è¿åç»æä½
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
                return *student_read;                       //å½æ°è¿åå¼ä¸ä¸º0,èä¸ºSTUDENTç»æä½è¡¨ç¤ºæ¾å°è¯¥å­¦ç
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
    FILE * student_b_file;         //äºè¿å¶æä»¶æé
    STUDENT * student_read = (STUDENT *)malloc(sizeof(STUDENT));        //ä»äºè¿å¶æä»¶ä¸­è¯»åçå­¦çä¿¡æ¯ç»æä½,å¹¶ä¸åéåå­

    //ä»student.datäºè¿å¶æä»¶ä¸­è¯»åå­¦çä¿¡æ¯ç»æä½
    if ( (student_b_file = fopen("student.dat", "rb")) != NULL) //å¦ææä»¶æå¼æå
    {
        while ( fread(student_read, sizeof(STUDENT), 1, student_b_file) == 1)
            if( strcmp(ID, (student_read -> ID)) == 0)                                             //æ¯å¯¹å­¦çID,å¦æç¬¦ååè¾åºå­¦çä¿¡æ¯,å¹¶ä¸è¿åç»æä½
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

                fseek(student_b_file, -sizeof(STUDENT), SEEK_CUR);
                fwrite(student_read, sizeof(STUDENT), 1, student_b_file);

                if ( fclose(student_b_file) == EOF )
                    fprintf(stderr, "Error closing file \"student.dat\".\n");
            }
    }
    else
        fprintf(stdout, "Sorry, can't find student \"%s\".\n", ID);

    free(student_read);
}
