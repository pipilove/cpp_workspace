/****************************************************************************/
/*�̽������ȵ����㷨��SPF����ʱ��Ƭ��ת�����㷨��RR����ģ��ʵ�� ƤƤ 2014-6-19  */
/****************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct pcb {
	int come_time;		//���̿�ʼʱ��
	int serve_time;		//���̷���ʱ��
	int run_time;		//����������ʱ��
	char name[10];		//������
	int ID;				//����ID
	struct pcb *next;
} PCB;

PCB *creat(int n);
void Menue(PCB *head,int n);
PCB *CopyPlist(PCB *head);
void Print( PCB *head);
void SPF(PCB *head);
void RR(PCB *head,int timeturn,int n);

/************************************************************************/
/*                               *������������*                         */
/************************************************************************/
PCB *creat(int n) {
	PCB *head,*p,*q;
	FILE * fp;
	fp = fopen("plist.txt","r");

	head=(PCB*)malloc(sizeof(PCB));
	if( !head ){
		printf("pcb head malloc fail...\n");
		system("pause");
		exit(0);
	}
	// assert(head=(PCB*)malloc(sizeof(PCB)));  

	head->next=NULL;
	while(n--) {
		p=head;
		if( ( q=(PCB*)malloc(sizeof(PCB))) == NULL) {
			printf("malloc fail...\n");
			system("pause");
			exit(0);
		}
		fscanf(fp,"%s",q->name);
		fscanf(fp,"%d",&q->ID);
		fscanf(fp,"%d",&q->come_time);
		fscanf(fp,"%d",&q->serve_time);
		q->run_time = 0;

		if(p->next==NULL) {        //�ڲ���ڵ�ʱ�����̿�ʼʱ������
			q->next=NULL;
			p->next=q;
		} else {
			while (p->next!=NULL && q->come_time >p->next->come_time )
				p=p->next;
			q->next=p->next;
			p->next=q;
		}
	}

	fclose(fp);
	return head;
}


/************************************************************************/
/*                        *������������*                                */
/************************************************************************/
PCB *CopyPlist(PCB *head1) {
	PCB *head2;	//������ͷ���
	PCB *p2;
	PCB *p1=head1->next;
	PCB *node=NULL;

	head2=(PCB*)malloc(sizeof(PCB));
	if( !head2 ){
		printf("pcb head2 malloc fail...\n");
		system("pause");
		exit(0);
	}
	p2=head2;

	while(p1!=NULL) {
		node = (PCB*)malloc(sizeof(PCB));
		if( !node ){
			printf("pcb node malloc fail...\n");
			system("pause");
			exit(0);
		}

		strcpy(node->name,p1->name);	//��������!!
		node->come_time=p1->come_time;
		node->serve_time=p1->serve_time;
		node->run_time=p1->run_time;
		node->ID=p1->ID;

		node->next=NULL;				//����head2������
		p2->next=node;

		p2=p2->next;					//ָ�����
		p1=p1->next;
	}
	return head2;
}


/********************************��ӡ���*****************************************/
void Print(  PCB *head) {
	head=head->next;
	puts("������    ����ID    ����ʱ��     ����ʱ��");
	//for(i=0; i<len; i++,head=head->next)
	while(head != NULL){
		printf("%5s %10d %10d %10d\n",head->name,head->ID,head->come_time,head->serve_time);
		head = head->next;
	}
}

/************************************************************************/
/*                            *�̽�������*                              */
/************************************************************************/
void SPF(PCB *head){
	PCB *Head=CopyPlist(head);			//���ı�ԭ����plist
	PCB *p = Head->next;
	PCB *pnext,*insert_pos,*insert_pos_pre;
	PCB * first_pcb,*q;
	PCB * wait_queue_head = (PCB *)malloc(sizeof(PCB));				//�ȴ�����
	int current_time = 0;

	wait_queue_head->next = NULL;

	//���������̰�serve_time��С������뵽wait_queue��
	while(p != NULL && p->come_time <= current_time){
		if(wait_queue_head->next == NULL){
			wait_queue_head->next = p;
			p = p->next;
			wait_queue_head->next->next = NULL;
		}else{
			insert_pos = wait_queue_head->next;
			while(insert_pos != NULL && p->serve_time > insert_pos->serve_time){
				insert_pos_pre = insert_pos;
				insert_pos = insert_pos->next;
			}
			pnext = p->next;
			p->next = insert_pos_pre->next;
			insert_pos_pre->next = p;
			p = pnext;
		}
	}

next_sched1:
	first_pcb = wait_queue_head->next;
	if( first_pcb == NULL ){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
		printf("���н��̶��Ѿ��������\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		Sleep(500);
		return 0;
	}
	current_time += first_pcb->serve_time;
	/* ��ʾ��ǰ������ɵĽ��̺;����Ľ��� */
	printf("--��ǰ��ɽ���(current_time:%2d)��%s", current_time,first_pcb -> name);
	/* ��������ɽ���ȥ�� */
	wait_queue_head = wait_queue_head -> next;		//û��free????????

	//���������̰�serve_time��С������뵽wait_queue��
	while(p != NULL && p->come_time <= current_time){
		if(wait_queue_head->next == NULL){
			wait_queue_head->next = p;
			p = p->next;
			wait_queue_head->next->next = NULL;
		}else{
			insert_pos = wait_queue_head->next;
			insert_pos_pre = wait_queue_head;
			while(insert_pos != NULL && p->serve_time > insert_pos->serve_time){
				insert_pos_pre = insert_pos;
				insert_pos = insert_pos->next;
			}
			pnext = p->next;
			p->next = insert_pos_pre->next;
			insert_pos_pre->next = p;
			p = pnext;
		}
	}

	//��ǰʱ�̵ȴ�����
	printf("  --�ȴ������ǣ�");
	q = first_pcb -> next;
	while(q != NULL) {
		printf("%s ", q -> name);
		q = q -> next;
	}
	printf("\n");
	

	Sleep(800);
	goto next_sched1;

}


/************************************************************************/
/*                            *ʱ��Ƭ��ת*                              */
/************************************************************************/
void RR(PCB *head,int timeturn,int n) {
	PCB *Head=CopyPlist(head);			//���ı�ԭ����plist
	PCB *p = Head->next;
	PCB *pnext;
	PCB * first_pcb,*q;
	PCB * wait_queue_head = (PCB *)malloc(sizeof(PCB));				//�ȴ�����
	PCB * wait_queue_tail;
	int current_time = 0;
	int i;

	wait_queue_head->next = NULL;
	wait_queue_tail = wait_queue_head;

	while(p != NULL && p->come_time <= current_time){/*
													 pnext = p->next;
													 p->next = wait_queue_head->next;
													 wait_queue_head->next = p;
													 p = pnext;*/
		wait_queue_tail->next = p;
		wait_queue_tail = wait_queue_tail->next;
		p = p->next;					//������֮ǰ
		wait_queue_tail->next = NULL;
	}

next_sched:	
	first_pcb = wait_queue_head->next;

	/* ��ʾ��ǰ���еĽ��̺;����Ľ��� */
	q = first_pcb -> next;
	printf("--��ǰ����(current_time:%2d)��%s", current_time,first_pcb -> name);
	printf("  --�ȴ������ǣ�");
	while(q != NULL) {
		printf("%s ", q -> name);
		q = q -> next;
	}
	printf("\n");

	//��������ʱ��ʱ��仯
	for(i = 0;i < timeturn;i++){
		first_pcb -> run_time++;
		if( (first_pcb -> run_time) == (first_pcb -> serve_time) ){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			printf("����%s�Ѿ��������\n", first_pcb -> name);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			Sleep(500);

			wait_queue_head = wait_queue_head -> next;
			i++;
			break;
		}
	}
	current_time += i;

	//��first_pcb���뵽��β֮ǰ��������ӵ����Ľ���
	while(p != NULL && p->come_time <= current_time){/*
													 pnext = p->next;
													 p->next = wait_queue_head->next;
													 wait_queue_head->next = p;
													 p = pnext;*/
		wait_queue_tail->next = p;
		wait_queue_tail = wait_queue_tail->next;
		p = p->next;					//������֮ǰ
		wait_queue_tail->next = NULL;

	}

	//�жϽ����Ƿ��������
	if(wait_queue_head->next == NULL) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
		printf("���н��̶��Ѿ��������\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		Sleep(500);
		return 0;
	}

	/* �����׵Ľ��̷ŵ���β��֮ǰ�ڶ�λ���̻��cpuʱ��Ƭ */
	if( (first_pcb -> run_time) != (first_pcb -> serve_time) ){
		/*q = first_pcb;
		while(q -> next != NULL) 
		q = q -> next;*/
		q = wait_queue_tail;
		wait_queue_tail = first_pcb;		//˳�����ͺ󣡣���

		q -> next = first_pcb;
		first_pcb = first_pcb -> next;
		q -> next -> next = NULL;
		wait_queue_head->next = first_pcb;
	}
	Sleep(800);
	goto next_sched;
}


/************************************************************************/
/*                            *�˵�*                                    */
/************************************************************************/
void Menue(PCB *head,int n) {
	int choice;//ѡ��
	int	timeturn;//ʱ��Ƭ

	while(1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		printf("		1.����������\n");
		printf("		2.ʱ��Ƭ��ת\n");
		printf("		3.�˳�	\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		printf("ѡ��\n");
		scanf("%d",&choice);
		switch(choice) {
		case 1:
			SPF(head);
			system("pause");
			system("cls");
			break;
		case 2:
			printf("����ʱ��Ƭ��\n");
			scanf("%d",&timeturn);
			RR(head,timeturn,n);
			system("pause");
			system("cls");
			break;
		case 3:
			exit(0);
		default:
			printf("����������������룺\n");
			Sleep(500);
			system("cls");
			break;
		}
	}
}



/*****************************������*************************************/
void main() {
	int n;			//����n������
	PCB *head;
	printf("process num:\n");
	scanf("%d",&n);
	head = creat(n);

	Print(head);	//�������������Ϣ����

	Menue(head,n);	//����ѡ�����
	system("pause");
}
