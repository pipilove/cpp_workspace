/**	�����������ŵ��ȣ��㷨��������ϰ��3.3��	*/
#include <iostream>
using namespace std;

int main(){
	int i,n,j,k,max=0,nmax;
	cout<<"�������������";
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	int *a=new int[n];//��̬��a,b�����ڴ�
	int *b=new int[n];
	cout<<"���봦���A,B������ҵ��ʱ��";
	for(i=0;i<n;i++){
		cin>>a[i];
		if(a[i]>max)
			max=a[i];
	}
	for(i=0;i<n;i++){
		cin>>b[i];
		if(b[i]>max)
			max=b[i];
	}
	//for test
	/*cout<<endl;
	for(i=0;i<n;i++)
		cout<<a[i]<<"*";
	for(i=0;i<n;i++)
		cout<<b[i]<<"*";
	cout<<endl;*/
	nmax=n*max;//A��B����ʱ��i��j�����ֵ

	bool ***p=new bool**[nmax+1];//��̬������άbool��������
	for(i=0;i<=nmax;i++)
		p[i]=new bool*[nmax+1];
	for(i=0;i<=nmax;i++)
		for(j=0;j<=nmax;j++)
			p[i][j]=new bool[n+1];

	for(i=0;i<=nmax;i++)//��ʼ��bool����
		for(j=0;j<=nmax;j++){
			p[i][j][0]=true;
			for(k=1;k<=n;k++)
				p[i][j][k]=false;
		};

	for(k=1;k<=n;k++)//ʵ�ֶ�̬�滮�㷨
		for(i=0;i<=nmax;i++)
			for(j=0;j<=nmax;j++){
				if(i-a[k-1]>=0){
					p[i][j][k]=p[i-a[k-1]][j][k-1];
					//cout<<"p["<<i<<"]["<<j<<"]["<<k<<"]="<<p[i][j][k]<<endl;
				}
				if(j-b[k-1]>=0){
					p[i][j][k]=(p[i][j][k]||p[i][j-b[k-1]][k-1]);//����һ����Ϊtrue
					//cout<<"*p["<<i<<"]"<<"["<<j<<"]"<<"["<<k<<"]="<<p[i][j][k]<<endl;
				}
			};

	int mintime=nmax,tempmax;
	for(i=0;i<=nmax;i++)//������̵�ʱ��
		for(j=0;j<=nmax;j++)
				if(p[i][j][n]){
					tempmax=(i>j)? i:j;
					if(tempmax<mintime)
						mintime=tempmax;
				};
	cout<<"���ʱ��Ϊ��"<<mintime<<endl;

	void traceback();//ʵ�֣�����

	system("pause");
	return 0;
}

void traceback(){
}