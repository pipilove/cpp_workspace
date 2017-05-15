/*	һά�ʾ�ѡַ����	
*����ʵ�ֵ�	������λ�����±�д������
*/
#include<iostream>
#include<ctime>
#include<cmath>
using namespace std;

struct Node{
	double value;//x��ֵ
	double weight;//x��Ȩֵ
};

//����һ������±꣬�����Ӧ������Ԫ����Ϊһ�˿��ٵ���Ԫ
int random(int m,int n){
	srand((unsigned)time(NULL));
	return m + (rand()%(n-m+1));//1������������㷨
}

//һ�˿�������
int partition(Node *nodes,int begin,int end){
	int i = begin-1,j=begin;
	double x = nodes[end].value;
	while(j<end){
		if(nodes[j].value<=x){
			i++;
			Node temp = nodes[i];
			nodes[i]=nodes[j];
			nodes[j]=temp;
		}
		j++;
	}
	Node temp = nodes[end];
	nodes[end]=nodes[i+1];
	nodes[i+1]=temp;
	return i+1;
}

//һ���������������
int random_qartition(Node *nodes,int begin,int end){
	int q = random(begin,end);
	Node temp = nodes[end];
	nodes[end]=nodes[q];
	nodes[q]=temp;
	return partition(nodes,begin,end);
}

//�������������
void random_fast_sort(Node *nodes,int begin,int end){
	if(begin<end){
		int p = random_qartition(nodes,begin,end);
		random_fast_sort(nodes,begin,p-1);
		random_fast_sort(nodes,p+1,end);
	}
}

//�õ���Ȩ����λ��
Node GetMidWeight(Node *nodes,int begin,int end,double SumWeight)
{
	double midSum = 0.0;
	int i;
	for(i=begin;i<=end;i++)
	{
		midSum+=nodes[i].weight;
		if(midSum>=SumWeight/2)
			break;
	}
	return nodes[i];
}

int main(int argc, char* argv[]){
	cout<<"���������ݸ�����"<<endl;
	int n;
	cin>>n;
	Node *nodes=new Node[n];

	int i;
	double sum = 0.0;
	cout<<"������ÿһ��ֵ����Ȩֵ"<<endl;
	for(i=0;i<n;i++){
		cin>>nodes[i].value>>nodes[i].weight;
		sum+=nodes[i].weight;
	}

	random_fast_sort(nodes,0,n-1);
	cout<<"�ʾ�λ��Ϊ��"<<endl;
	Node node = GetMidWeight(nodes,0,n-1,sum);
	cout<<node.value<<endl;
	cout<<"�ܴ���Ϊ��"<<endl;
	double sumValue = 0.0;
	for(i=0;i<n;i++)
	{
		sumValue+=abs(nodes[i].value-node.value);
	}
	cout<<sumValue<<endl;
	system("pause");
	return 0;
}