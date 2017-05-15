#include "Set.h"
#include <iostream>

using namespace std;


void Set::ShowElement() const            //展示集合内的元素
{
    if (n != 0) {
        cout << "{ ";
        for (int i = 0; i < n - 1; i++) {
            cout << pS[i] << ", ";
        }
        cout << pS[n - 1] << " }";
    } else {
        cout << "inthe Set is Empty!";
    }
}

bool Set::IsEmpt()                //判空
{
    return n == 0;
}

int Set::size()                //判定集合大小
{
    return n;
}

void Set::clear()                //clear掉Set中的所有元素
{
    if (pS) {
        delete[]pS;
        pS = NULL;
        n = 0;
    }
}

bool Set::IsElement(int e) const    //判断e是否属于集合Set
{
    for (int i = 0; i < n; i++) {
        if (pS[i] == e) {
            return true;
        }
    }
    return false;
}


bool Set::IsSubset(const Set &s) const    //判断s是否包含于集合Set
{
    if (s.n > n) {
        return false;
    }
    for (int i = 0; i < s.n; i++) {
        if (!IsElement(s.pS[i])) {
            return false;
        }
    }
    return true;
}


bool Set::IsEqual(const Set &s) const        //判断集合是否相等
{
    if (n != s.n) {
        return false;
    }
    if (IsSubset(s)) {
        return true;
    }
    return false;
}


Set &Set::insert(int e)        //将e插入集合Set中
{
    if (IsElement(e)) {
        return *this;           //集合具有互异性，返回原有的Set
    }
    Set temp;
    for (int i = 0; i < n; i++) {
        temp.insert(pS[i]);
    }
    n++;
    if (pS != NULL) {
        delete[]pS;
    }
    pS = new int[n];
    for (int i = 1; i < n; i++) {
        pS[i] = temp.pS[i];
    }
    pS[n] = e;
    cout << "Insert successfully!" << std::endl;
    return *this;
}


Set &Set::deleteElement(int e) {        //查找并删除元素e
    if (!IsElement(e)) {
        cout << "Empty set!";
    } else {
        Set tempe;
        for (int i = 0; i < n; i++) {
            tempe.insert(pS[i]);
        }
        n--;
        if (pS != NULL) {
            delete[]pS;
        }
        pS = new int[n];
        int j = 1;
        for (int i = 0; i < n; i++) {
            if (tempe.pS[i] != e) {
                pS[j] = tempe.pS[i];
                j++;
            }
        }
        cout << "Deleted successfully!";
    }
    return *this;
}


Set Set::Union(const Set &s) const {        //求集合的并
    Set Union;
    for (int i = 0; i < n; i++) {
        Union.insert(pS[i]);
    }
    for (int i = 0; i < s.n; i++) {
        if (!IsElement(s.pS[i])) {
            Union.insert(s.pS[i]);
        }
    }
    return Union;
}


Set Set::intersection(const Set &s) const {        //求集合的交
    Set Inter;
    for (int i = 0; i < s.n; i++) {
        if (IsElement(s.pS[i])) {
            Inter.insert(s.pS[i]);
        }
    }
    return Inter;
}


Set Set::difference(const Set &s) const {        //求集合的差
    Set Diff;
    for (int i = 0; i < n; i++) {
        if (!(s.IsElement(pS[i]))) {
            Diff.insert(pS[i]);
        }
    }
    return Diff;
}
