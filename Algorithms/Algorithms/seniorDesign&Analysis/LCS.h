#define ITEMTYPE char
#include <vector>
using namespace std;

//最长公共子序列
vector< vector<int> > lcs(vector<ITEMTYPE> X,vector<ITEMTYPE> Y,vector< vector<int> > &B);
//printf the optimal solution of lcs
void printfLCS(vector< vector<int> > B,vector<ITEMTYPE> X,int i,int j);
//printf the optimal solution of lcs according to Z without B
void printfLCSZ(vector< vector<int> > Z,vector<ITEMTYPE> X,int i,int j);
