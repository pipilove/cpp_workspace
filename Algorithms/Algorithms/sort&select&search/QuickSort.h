/*	����	2013.10.23	*/
//һ�㻮�ֺ���
int partition(int* A,int p,int r);
//ͬʱ�����ͬԪ�������һ�㻮�ֺ���
//int partition(int* A,int p,int r);
//������ֺ���
int randomizedPartition(int* A,int p,int r);
//����汾hoare-partition
void hoarePartition(int* A,int p,int r);

//ѡ���iС��Ԫ��
int select(int *a,int p,int r,int i);
//���ѡ���iС��Ԫ��???����Ϊ�˷����±꣩
int randomizedSelect(int *a,int p,int r,int i);
//�����λ�����ֺ���
int midRandomPartition(int* A,int p,int r);

//һ���������
void quickSort(int* A,int p,int r);
//�����������
void randomizedQuickSort(int* A,int p,int r);
//�����λ����������
void midRandomizedQuickSort(int* A,int p,int r);
//����Ŀ���hoare
void hoareQuickSort(int* A,int p,int r);
