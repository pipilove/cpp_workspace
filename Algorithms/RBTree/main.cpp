//file RBTree.cpp 
#include<iostream>  
#include<algorithm>  
#include<iterator>  
#include<vector>  
#include<sstream>  
#include"RBTree.h"
using namespace std;  
  
int main()  
{  
    RB_Tree<int,int> tree;  
    vector<int> v;  
      
    for(int i=0;i<20;++i)  
    {  
        v.push_back(i);  
    }  
    random_shuffle(v.begin(),v.end());  
    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));  
    cout<<endl;  
    stringstream sstr;  
    for(i=0;i<v.size();++i)  
    {  
        tree.Insert(v[i],i);  
        cout<<"insert:"<<v[i]<<endl;   //��ӽ��  
    }  
    for(i=0;i<v.size();++i)  
    {  
        cout<<"Delete:"<<v[i]<<endl;  
        tree.Delete(v[i]);             //ɾ�����  
        tree.InOrderTraverse();  
    }  
    cout<<endl;  
    tree.InOrderTraverse();  
    return 0;  
}  
