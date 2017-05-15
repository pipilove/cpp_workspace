/*
 提供两个全局变量，x1， x2，其初值为0x12345678和0x12345679用两条赋值语句为其赋值

为0x22334455和0x11223344.

撰写程序如下：

*/
struct StdInfo{
   char name[20];//学生姓名
   char no[30];//学号
};

//该函数填写info的两个成员变量
void getStudentNameInfo(struct StdInfo * info);

//该函数生成指定的执行程序到一段动态分配的内存上，返回值为该内存首址
void * makeProgram(int expectedBase);

//px1Offset和px2Offset指向两个整数，实现者需要填写这两个整数。整数中分别存储了题目要求所构造的程序中变量x1和x2到该程序头部的偏移量。
void getVarOffset(int * px1Offset, int * px2Offset);

