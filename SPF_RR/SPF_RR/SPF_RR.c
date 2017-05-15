/****************************************************************************/
/*短进程优先调度算法（SPF）和时间片轮转调度算法（RR）的模拟实现 皮皮 2014-6-19  */
/****************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct pcb {
	int come_time;		//进程开始时间
	int serve_time;		//进程服务时间
	int run_time;		//进程已运行时间
	char name[10];		//进程名
	int ID;				//进程ID
	struct pcb *next;
} PCB;

PCB *creat(int n);
void Menue(PCB *head,int n);
PCB *CopyPlist(PCB *head);
void Print( PCB *head);
void SPF(PCB *head);
void RR(PCB *head,int timeturn,int n);

/************************************************************************/
/*                               *创建进程链表*                         */
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

		if(p->next==NULL) {        //在插入节点时按进程开始时间排序
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
/*                        *拷贝进程链表*                                */
/************************************************************************/
PCB *CopyPlist(PCB *head1) {
	PCB *head2;	//新链表头结点
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

		strcpy(node->name,p1->name);	//拷贝进程!!
		node->come_time=p1->come_time;
		node->serve_time=p1->serve_time;
		node->run_time=p1->run_time;
		node->ID=p1->ID;

		node->next=NULL;				//加入head2队列中
		p2->next=node;

		p2=p2->next;					//指针后移
		p1=p1->next;
	}
	return head2;
}


/********************************打印输出*****************************************/
void Print(  PCB *head) {
	head=head->next;
	puts("进程名    进程ID    到达时间     运行时间");
	//for(i=0; i<len; i++,head=head->next)
	while(head != NULL){
		printf("%5s %10d %10d %10d\n",head->name,head->ID,head->come_time,head->serve_time);
		head = head->next;
	}
}

/************************************************************************/
/*                            *短进程优先*                              */
/************************************************************************/
void SPF(PCB *head){
	PCB *Head=CopyPlist(head);			//不改变原来的plist
	PCB *p = Head->next;
	PCB *pnext,*insert_pos,*insert_pos_pre;
	PCB * first_pcb,*q;
	PCB * wait_queue_head = (PCB *)malloc(sizeof(PCB));				//等待队列
	int current_time = 0;

	wait_queue_head->next = NULL;

	//将到来进程按serve_time从小到大插入到wait_queue中
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
		printf("所有进程都已经运行完毕\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		Sleep(500);
		return 0;
	}
	current_time += first_pcb->serve_time;
	/* 显示当前运行完成的进程和就绪的进程 */
	printf("--当前完成进程(current_time:%2d)：%s", current_time,first_pcb -> name);
	/* 将队首完成进程去掉 */
	wait_queue_head = wait_queue_head -> next;		//没有free????????

	//将到来进程按serve_time从小到大插入到wait_queue中
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

	//当前时刻等待进程
	printf("  --等待进程是：");
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
/*                            *时间片轮转*                              */
/************************************************************************/
void RR(PCB *head,int timeturn,int n) {
	PCB *Head=CopyPlist(head);			//不改变原来的plist
	PCB *p = Head->next;
	PCB *pnext;
	PCB * first_pcb,*q;
	PCB * wait_queue_head = (PCB *)malloc(sizeof(PCB));				//等待队列
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
		p = p->next;					//必须在之前
		wait_queue_tail->next = NULL;
	}

next_sched:	
	first_pcb = wait_queue_head->next;

	/* 显示当前运行的进程和就绪的进程 */
	q = first_pcb -> next;
	printf("--当前进程(current_time:%2d)：%s", current_time,first_pcb -> name);
	printf("  --等待进程是：");
	while(q != NULL) {
		printf("%s ", q -> name);
		q = q -> next;
	}
	printf("\n");

	//进程运行时的时间变化
	for(i = 0;i < timeturn;i++){
		first_pcb -> run_time++;
		if( (first_pcb -> run_time) == (first_pcb -> serve_time) ){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			printf("进程%s已经运行完毕\n", first_pcb -> name);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			Sleep(500);

			wait_queue_head = wait_queue_head -> next;
			i++;
			break;
		}
	}
	current_time += i;

	//在first_pcb加入到队尾之前！！！添加到来的进程
	while(p != NULL && p->come_time <= current_time){/*
													 pnext = p->next;
													 p->next = wait_queue_head->next;
													 wait_queue_head->next = p;
													 p = pnext;*/
		wait_queue_tail->next = p;
		wait_queue_tail = wait_queue_tail->next;
		p = p->next;					//必须在之前
		wait_queue_tail->next = NULL;

	}

	//判断进程是否都运行完毕
	if(wait_queue_head->next == NULL) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
		printf("所有进程都已经运行完毕\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		Sleep(500);
		return 0;
	}

	/* 将队首的进程放到队尾，之前第二位进程获得cpu时间片 */
	if( (first_pcb -> run_time) != (first_pcb -> serve_time) ){
		/*q = first_pcb;
		while(q -> next != NULL) 
		q = q -> next;*/
		q = wait_queue_tail;
		wait_queue_tail = first_pcb;		//顺序不能滞后！！！

		q -> next = first_pcb;
		first_pcb = first_pcb -> next;
		q -> next -> next = NULL;
		wait_queue_head->next = first_pcb;
	}
	Sleep(800);
	goto next_sched;
}


/************************************************************************/
/*                            *菜单*                                    */
/************************************************************************/
void Menue(PCB *head,int n) {
	int choice;//选择
	int	timeturn;//时间片

	while(1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		printf("		1.短任务优先\n");
		printf("		2.时间片轮转\n");
		printf("		3.退出	\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		printf("选择：\n");
		scanf("%d",&choice);
		switch(choice) {
		case 1:
			SPF(head);
			system("pause");
			system("cls");
			break;
		case 2:
			printf("输入时间片：\n");
			scanf("%d",&timeturn);
			RR(head,timeturn,n);
			system("pause");
			system("cls");
			break;
		case 3:
			exit(0);
		default:
			printf("输入错误，请重新输入：\n");
			Sleep(500);
			system("cls");
			break;
		}
	}
}



/*****************************主函数*************************************/
void main() {
	int n;			//创建n个进程
	PCB *head;
	printf("process num:\n");
	scanf("%d",&n);
	head = creat(n);

	Print(head);	//首先输出进程信息链表

	Menue(head,n);	//进程选择调度
	system("pause");
}
