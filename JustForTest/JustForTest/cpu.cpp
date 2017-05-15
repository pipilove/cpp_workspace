#include <iostream>
using namespace std;

const int MAXN = 120;
int c1[MAXN+1],c2[MAXN+1];

int __main(){
    int i,j,k,n;
    for(i=0;i<=MAXN;i++)
        c1[i]=1,c2[i]=0;
    for(i=2;i<=MAXN;i++){
        for(j=0;j<=MAXN;j++)
            for(k=0;k+j<=MAXN;k+=i)
                c2[j+k]+=c1[j];
        for(j=0;j<=MAXN;j++)
            c1[j]=c2[j],c2[j]=0;
    }
    while(cin>>n) cout<<c1[n]<<endl;
    return 0;
}
