/*
 �ṩ����ȫ�ֱ�����x1�� x2�����ֵΪ0x12345678��0x12345679��������ֵ���Ϊ�丳ֵ

Ϊ0x22334455��0x11223344.

׫д�������£�

*/
struct StdInfo{
   char name[20];//ѧ������
   char no[30];//ѧ��
};

//�ú�����дinfo��������Ա����
void getStudentNameInfo(struct StdInfo * info);

//�ú�������ָ����ִ�г���һ�ζ�̬������ڴ��ϣ�����ֵΪ���ڴ���ַ
void * makeProgram(int expectedBase);

//px1Offset��px2Offsetָ������������ʵ������Ҫ��д�����������������зֱ�洢����ĿҪ��������ĳ����б���x1��x2���ó���ͷ����ƫ������
void getVarOffset(int * px1Offset, int * px2Offset);

