/*	�����ṹ	*/
typedef struct var{
	char* vname;	//������
	char* vproc;	//����������
	int vkind;		//�������� 0������,1���β�
	char* types;	//��������
	int vlev;		//�������
	int vadr;		//�����ڱ������е�λ��
}var;

int varTable(int vkind);
int varCheck();
int realParaCheck();
