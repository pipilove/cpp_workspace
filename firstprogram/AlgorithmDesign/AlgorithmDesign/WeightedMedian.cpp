/**	��Ȩ��λ���㷨	
����һ������ʱ�����λ���㷨���㷨����9.3���е�SELECT��������������O(n)ʱ�������n�����Ĵ�Ȩ��λ��
step1������SELECT��Ѱ����ֵ����ֵ���㷨���ҵ���Ԫ
step2������Ԫ�������Ϊ���Σ���A[1..q-1] < A[q] < A[q+1..r]
step3������A[1..q-1]<0.5��A[1..q]>=0.5��Ȩֵ�ͣ��Ƿ�������Ŀ�еĹ�ʽ
step4�������㣬A[q]�����������
step5���������㣬�ͼ����ݹ�ʹ�ñ��㷨���еݹ���ҡ�ƫ�����ǰ��Σ�ƫС���Һ���
*/

/*
#include <iostream>  
using namespace std;  
  
struct node{  
    int value;  //x��ֵ
    double weight;  //x��Ȩ��
};  
void Print(node *A, int len){  
    int i;  
    for(i = 1; i <= len; i++)  
        cout<<A[i].value<<' ';  
    cout<<endl;  
    for(i = 1; i <= len; i++)  
        cout<<A[i].weight<<' ';  
    cout<<endl;  
}  

int Partition(node *A, int p, int r){  
    int i = p-1, j;  
    for(j = p; j < r; j++) 
        if(A[j].value <= A[r].value){  
            i++;  
            swap(A[i], A[j]);  
        } 
    swap(A[i+1], A[r]);  
    return i+1;  
}  

node Select(node *A, int p, int r, int i);  
//��ÿһ���start��end���в������򣬲�������ֵ  

//���������value��node������в�������,��������λ��
node insertSort(node *A, int start, int end, int k){  
    int i, j;  
    for(i = 2; i <= end; i++){  
        node t = A[i];  
        for(j = i; j >= start; j--){  
            if(j == start)  
                A[j] = t;  
            else if(A[j-1].value > t.value)  
                A[j] = A[j-1];  
            else{  
                A[j] = t;  
                break;  
            }  
        }  
    }  
    return A[start+k-1];  
}  

//�ҵ���ֵ����ֵ  
node Find(node *A, int p, int r){  
    int i, j = 0;  
    int start, end, len = r - p + 1;    
    //ÿ5��Ԫ��һ�飬����Ϊstart��end����ÿһ����в������򣬲�������ֵ  
    node *B = new node[len/5+1];//��¼ÿ�����λ��
    for(i = 1; i <= len; i++){  
        if(i % 5 == 1)  
            start = i+p-1;  
        if(i % 5 == 0 || i == len){
			end = i+p-1;  
            //��ÿһ���start��end���в������򣬲�������ֵ,��������һ�飬����Ԫ�ظ�����������5  
            node ret = insertSort(A, start, end, (end-start)/2+1);  
            //��ÿһ�����ֵ�������γ�һ���µ�����  
            B[++j] = ret;   
        }  
    }  
    //����������Եݹ����Select()�ķ�ʽѰ����ֵ  
    node ret = Select(B, 1, j, (j+1)/2);  
    //delete []B;  
    return ret;  
}  

//��fΪ��Ԫ�Ļ���  
int Partition2(node *A, int p, int r, node f){  
    int i;  
    //�ҵ�f��λ�ò�������A[r]����  
    for(i = p; i < r; i++){  
        if(A[i].value == f.value){  
            swap(A[i], A[r]);  
            break;  
        }  
    }  
    return Partition(A, p, r);  
}  
//Ѱ������A[p..r]�еĵ�i���Ԫ�أ�i�Ǵ�1��ʼ���������Ǵ�p��ʼ  
node Select(node *A, int p, int r, int i){
    if(p == r)  
        return A[p];  
    //�������е��㷨���ҵ���ֵ����ֵ  
    node f = Find(A, p, r); 
    //��Ϊ��Ԫ�������е�ĳ��Ԫ�أ����ֺ��������ģ�A[p..q-1] <= f < A[q+1..r]    
    //�������ֵΪ��Ԫ�Ļ��֣�������ֵ����������A[1..len]��λ�� 
    int q = Partition2(A, p, r, f);  
    //ת��Ϊ��ֵ��������A[p..r]�е�λ��  
    int k = q - p + 1;  
    //����Ѱ�ҵ�Ԫ����Ƚ�  
    if(i == k)  
        return A[q];  
    else if(i < k)  
        return Select(A, p, q-1, i);  
    else  
        //�����Ԫ�������е�ĳ��Ԫ�أ�����һ��Ҫ����д  
        return Select(A, q+1, r, i-k);  
        //���������Ԫ���������еĸ�ĳ��Ԫ�أ�����һ��Ҫ�ĳ�Select(A, q, r, i-k+1)  
}  

//Ѱ������A[p..r]�еĵ�i���Ԫ�أ�i�Ǵ�1��ʼ���������Ǵ�p��ʼ
node Select2(node *A, int p, int r, double i){
    if(p == r)  
        return A[p];  
    //�������е��㷨���ҵ���ֵ����ֵ  
    node f = Find(A, p, r);  
    //�������ֵΪ��Ԫ�Ļ��֣�������ֵ����������A[1..len]��λ��  
    //��Ϊ��Ԫ�������е�ĳ��Ԫ�أ����ֺ��������ģ�A[p..q-1] <= f < A[q+1..r]  
    int q = Partition2(A, p, r, f);  
    //ת��Ϊ��ֵ��������A[p..r]�е�λ��  
    int k = q - p + 1;  
    //����Ѱ�ҵ�Ԫ����Ƚ�  
    double w = 0;  
    for(int j = p; j <= k; j++)  
        w += A[j].weight;  
    if(w-A[k].weight < i && w >= i)  
        return A[q];  
    else if(w-A[k].weight >= i)  
        return Select2(A, p, q-1, i);  
    else  
        //�����Ԫ�������е�ĳ��Ԫ�أ�����һ��Ҫ����д  
        return Select2(A, q+1, r, i-w);  
        //���������Ԫ���������еĸ�ĳ��Ԫ�أ�����һ��Ҫ�ĳ�Select(A, q, r, i-k+1)  
}  

int main(){  
    int n, sum = 0, i;  
    cin>>n;  
    node *A = new node[n+1];  //�����洢x������ֵ
    int *B = new int[n+1];  //�洢x��δ��񻯵�Ȩֵ

    for(i = 1; i <= n; i++){  
        A[i].value = rand() % 100;  //x������ֵ
        do
		{B[i] = rand() % 100;}
		while(B[i]==0);  
        sum = sum + B[i];  
    }  
    //��Ȩֵ��񻯣�Ȩֵ�����Ϊ1
    for(i = 1; i <= n; i++)  
        A[i].weight = (double)B[i]/sum;    //x��񻯵�Ȩֵ 
    Print(A, n); 

    //���Ȩ��λ��  
    cout<<Select2(A, 1, n, 0.5).value<<endl;  
	system("pause");
    return 0;  
}
*/