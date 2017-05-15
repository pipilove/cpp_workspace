// Jonse.cpp : Defines the entry point for the console application.
/*	µ•¡¥±ÌÀ„∑®	*/
#include <iostream>
using namespace std;

typedef struct Jonse {
    int code;
    struct Jonse  * next;
} Jonse,* JonsePtr;

Jonse * Create(int n) {
    JonsePtr head,p;
    head=new Jonse;
    head->code=0;
    head->next=head;
    for(int i=n-1; i>=1; i--) {
        p=new Jonse;
        p->code=i;
        p->next=head->next ;
        head->next=p;
    }
    return head;
}

void ShowList(Jonse * Jonse1) {
    JonsePtr p=Jonse1;
    cout<<p->code<<" ";
    while (p->next!=Jonse1) {
        p=p->next;
        cout<<p->code<<" ";
    }
    cout<<endl;
}

Jonse * JonseOut(Jonse * h,int n,int m) {
    Jonse * p=h;
    while(n!=1) {
        int j=0;
        while(++j<m-1) {
            h=h->next;
        }
        p=h->next;
        h->next=h->next->next ;
        h=h->next ;
        free(p);
        n--;
    }
    return h;
}

void __24184121main() {
    int n,m;
    cout<<"Please input the number of people: ";
    cin>>n;
    JonsePtr Jonse1=Create(n);
    ShowList(Jonse1);
    cout<<"Please input the out number M: ";
    cin>>m;
    Jonse * Last=JonseOut(Jonse1,n,m);
    cout<<"The last one alive has the number of: "<<Last->code<<endl;
    system("pause");
}
