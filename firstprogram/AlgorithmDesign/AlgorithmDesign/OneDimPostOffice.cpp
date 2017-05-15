/*	一维邮局选址问题	
*快排实现的	试用中位数重新编写？？？
*/
#include<iostream>
#include<ctime>
#include<cmath>
using namespace std;

struct Node{
	double value;//x的值
	double weight;//x的权值
};

//产生一个随机下标，用其对应的数组元素作为一趟快速的主元
int random(int m,int n){
	srand((unsigned)time(NULL));
	return m + (rand()%(n-m+1));//1°随机数产生算法
}

//一趟快速排序
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

//一趟随机化快速排序
int random_qartition(Node *nodes,int begin,int end){
	int q = random(begin,end);
	Node temp = nodes[end];
	nodes[end]=nodes[q];
	nodes[q]=temp;
	return partition(nodes,begin,end);
}

//随机化快速排序
void random_fast_sort(Node *nodes,int begin,int end){
	if(begin<end){
		int p = random_qartition(nodes,begin,end);
		random_fast_sort(nodes,begin,p-1);
		random_fast_sort(nodes,p+1,end);
	}
}

//得到带权的中位数
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
	cout<<"请输入数据个数："<<endl;
	int n;
	cin>>n;
	Node *nodes=new Node[n];

	int i;
	double sum = 0.0;
	cout<<"请输入每一点值和其权值"<<endl;
	for(i=0;i<n;i++){
		cin>>nodes[i].value>>nodes[i].weight;
		sum+=nodes[i].weight;
	}

	random_fast_sort(nodes,0,n-1);
	cout<<"邮局位置为："<<endl;
	Node node = GetMidWeight(nodes,0,n-1,sum);
	cout<<node.value<<endl;
	cout<<"总代价为："<<endl;
	double sumValue = 0.0;
	for(i=0;i<n;i++)
	{
		sumValue+=abs(nodes[i].value-node.value);
	}
	cout<<sumValue<<endl;
	system("pause");
	return 0;
}