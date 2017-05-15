/****************************************************************************/
/*			POJ读书笔记4.4 ―― 子串2744、1226		皮皮 2014-7-5			*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "StrRev.h"

void subStr() {
    int cases;
    scanf("%d", &cases);
    char str[100][101];
    int i;

    while (cases--) {
        int strNum;
        scanf("%d", &strNum);
        int minLenIndex, minLen = 101;
        for (i = 0; i < strNum; i++) {
            scanf("%s", str[i]);
            if (strlen(str[i]) < minLen) {
                minLen = strlen(str[i]);
                minLenIndex = i;
            }
        }

        int subLen;
        char subStr[101];
        for (subLen = minLen; subLen > 0; subLen--) {                //子串长度
            for (int j = 0; j <= minLen - subLen; j++) {            //子串起始地址
                strncpy(subStr, str[minLenIndex] + j, subLen);
                subStr[subLen] = 0;
                int k;
                for (k = 0; k < strNum; k++) {                    //与strNum个字符串对比
                    if (strstr(str[k], subStr) == NULL && strstr(strReverse(str[k]), subStr) == NULL)//strrev()ms自己的库函数
                        break;                                    //有一个字符串没对上就break，下一个子串比较
                }
                if (k == strNum) {                                //此刻的从j开始的长度subLen的子串满足要求
                    printf("%d\n", subLen);
                    goto nextCase;
                }
            }
        }

        if (subLen == 0)                                            //长度为0了都没找到
            printf("0\n");
        nextCase:;
    }
}

int __548451main() {
    subStr();
    //char str[] = "ABCD";			//char* str在静态分配区，会导致strrev中发生写入位置冲突，不允许被修改
    //printf("%s\n", strrev(str));
    return 0;
}
