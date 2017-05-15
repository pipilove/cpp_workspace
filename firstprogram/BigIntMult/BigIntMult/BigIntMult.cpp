#include <iostream> 
#include <sstream> 
#include <string> 
 
using namespace std; 
 
//string类型转换成int类型
int string_to_num(string k)//string字符串变整数型例如str="1234"，转换为整数的1234. 
{ 
    int back; 
    stringstream instr(k); 
 
    instr>>back; 
 
    return back; 
 
} 
 
//整形数转换为string类型
string num_to_string(int intValue)
{
string result;
stringstream stream;
stream << intValue;//将int输入流
stream >> result;//从stream中抽取前面放入的int值
return result;
}
 
//在字符串str前添加s个零
string stringBeforeZero(string str,int s)
{
for(int i=0;i<s;i++)
{
str.insert(0,"0");
}
return str;
}
 
//两个大整数字符串相加，超出计算机表示范围的数也能实现相加(本函数可以实现大整数加法运算)
string stringAddstring(string str1,string str2)
{
//假定str1和str2是相等的长度，不相等时在前面自动补零，使两个字符串长度相等
if (str1.size() > str2.size()) 
{
str2 = stringBeforeZero(str2,str1.size() - str2.size());
}else if (str1.size() < str2.size()) 
{
str1 = stringBeforeZero(str1,str2.size() - str1.size());
}
 
string result;
int flag=0;//前一进位是否有标志,0代表无进位，1代表有进位
for(int i=str1.size()-1;i>=0;i--)
{
int c = (str1[i] - '0') + (str2[i] - '0') + flag;//利用ASCII码对字符进行运算,这里加上flag代表的是:当前一位有进位时加1，无进位时加0
flag = c/10;//c大于10时，flag置为1，否则为0
c %= 10;//c大于10时取模，否则为其本身
 
result.insert(0,num_to_string(c));//在result字符串最前端插入新生成的单个字符
}
if (0 != flag) //最后一为(最高位)判断，如果有进位则再添一位
{
result.insert(0,num_to_string(flag));
}
 
return result;
}
 
 
/*两个大整数字符串相减，超出计算机表示范围的数也能实现相减(在这里比较特殊，第一个参数一定大于第二个参数,
因为：a1*b0+a0*b1=(a1+a0)*(b1+b0)-(a1*b1+a0*b0) > 0 ,所以(a1+a0)*(b1+b0) > (a1*b1+a0*b0)
这个函数的两个参数，第一个代表的其实就是(a1+a0)*(b1+b0)，第二个代表的其实就是(a1*b1+a0*b0)
所以本函数里不用考虑最终得到结果为负数的情况，至于计算有关大整数负数相乘的问题可以通过其他途径判断
*/
string stringSubtractstring(string str1,string str2)
{
//对传进来的两个数进行修剪，如果前面几位有0则先去掉，便于统一处理
while ('0' == str1[0]&&str1.size()>1)
{
str1=str1.substr(1,str1.size()-1);
}
while ('0' == str2[0]&&str2.size()>1)
{
str2=str2.substr(1,str2.size()-1);
}
//使两个字符串长度相等
if (str1.size() > str2.size()) 
{
str2 = stringBeforeZero(str2,str1.size() - str2.size());
}
 
string result;
for(int i=str1.size()-1;i>=0;i--)
{
int c = (str1[i] - '0') - (str2[i] - '0');//利用ASCII码进行各位减法运算
if (c < 0) //当不够减时向前一位借位，前一位也不够位时再向前一位借位，依次如下
{
c +=10;
int prePos = i-1; 
char preChar = str1[prePos];
while ('0' == preChar) 
{
str1[prePos]='9';
prePos -= 1;
preChar = str1[prePos];
}
str1[prePos]-=1;
}
 
result.insert(0,num_to_string(c));//在result字符串最前端插入新生成的单个字符
}
return result;
}
 
 
//在字符串str后跟随s个零
string stringFollowZero(string str,int s)
{
for(int i=0;i<s;i++)
{
str.insert(str.size(),"0");
}
return str;
}
 
//分治法大整数乘法实现函数
string IntMult(string x,string y)//递归函数
{ 
//对传进来的第一个数进行修剪，如果前面几位有0则先去掉，便于统一处理
while ('0' == x[0]&&x.size()>1)
{
x=x.substr(1,x.size()-1);
}
//对传进来的第二个数进行修剪，如果前面几位有0则先去掉，便于统一处理
while ('0' == y[0]&&y.size()>1)
{
y=y.substr(1,y.size()-1);
}
/*这里的f变量代表在两个数据字符串长度不想等或者不是2的指数倍的情况下，所要统一的长度，这样做是为了让数据长度为2的n次方
 的情况下便于利用分治法处理
*/
int f=4;
/*当两字符串中有任意一个字符串长度大于2时都要通过与上面定义的f值进行比较，使其达到数据长度为2的n次方，实现方式是在前面
 补0，这样可以保证数据值大小不变
*/
if (x.size()>2 || y.size()>2) 
{
if (x.size() >= y.size()) //第一个数长度大于等于第二个数长度的情况
{
while (x.size()>f) //判断f值
{
f*=2;
}
if (x.size() != f) 
{
x = stringBeforeZero(x,f-x.size());
y = stringBeforeZero(y,f-y.size());
}
}else//第二个数长度大于第一个数长度的情况
{
while (y.size()>f) //判断f值
{
f*=2;
}
if (y.size() != f) 
{
x = stringBeforeZero(x,f-x.size());
y = stringBeforeZero(y,f-y.size());
}
}
}
 
if (1 == x.size()) //数据长度为1时,在前面补一个0(这里之所以会出现长度为1的数据是因为前面对数据修剪过)
{
x=stringBeforeZero(x,1);
}
if (1 == y.size()) //数据长度为1时,在前面补一个0(这里之所以会出现长度为1的数据是因为前面对数据修剪过)
{
y=stringBeforeZero(y,1);
}
 
if (x.size() > y.size()) //最后一次对数据校正，确保两个数据长度统一
{
y = stringBeforeZero(y,x.size()-y.size());
}
if (x.size() < y.size()) //最后一次对数据校正，确保两个数据长度统一
{
x = stringBeforeZero(x,y.size()-x.size());
}
 
    int s = x.size(); 
    string a1,a0,b1,b0; 
 
    if( s > 1) 
    { 
        a1 = x.substr(0,s/2); 
 
        a0 = x.substr(s/2,s-1); 
 
        b1 = y.substr(0,s/2); 
 
        b0 = y.substr(s/2,s-1); 
    } 
 
string result;
 
    if( s == 2) //长度为2时代表着递归的结束条件
    { 
int na = string_to_num(a1); 
        int nb = string_to_num(a0);  
        int nc = string_to_num(b1); 
        int nd = string_to_num(b0);
        result = num_to_string((na*10+nb) * (nc*10+nd)); 
    } 
    else{ //长度不为2时利用分治法进行递归运算
/***************************************************
小提示:
c = a*b = c2*(10^n) + c1*(10^(n/2)) + c0;
a = a1a0 = a1*(10^(n/2)) + a0;
b = b1b0 = b1*(10^(n/2)) + b0;
c2 = a1*b1;  c0 = a0*b0;
c1 = (a1 + a0)*(b1 + b0)-(c2 + c0);
****************************************************/
string c2 = IntMult(a1,b1);// (a1 * b1)
 
string c0 = IntMult(a0,b0);// (a0 * b0)
 
string c1_1 = stringAddstring(a1,a0);// (a1 + a0)
 
string c1_2 = stringAddstring(b1,b0);// (b1 + b0)
 
string c1_3 = IntMult(c1_1,c1_2);// (a1 + a0)*(b1 + b0)
 
string c1_4 = stringAddstring(c2,c0);// (c2 + c0)
 
string c1=stringSubtractstring(c1_3,c1_4);// (a1 + a0)*(b1 + b0)-(c2 + c0)
string s1=stringFollowZero(c1,s/2);// c1*(10^(n/2))
 
string s2=stringFollowZero(c2,s);// c2*(10^n)
 
result = stringAddstring(stringAddstring(s2,s1),c0);// c2*(10^n) + c1*(10^(n/2)) + c0
    } 
 
    return result; 
 
} 
 
void main() 
{ 
int f=1;
while (1 == f)
{
string A,B,C,D; 
string num1,num2; 
string r;
cout<<"大整数乘法运算(分治法实现)"<<endl;
cout<<"请输入第一个大整数(任意长度):";
cin>>num1;
int i=0;
//判断第一个输入的数据是否合法,当字符串中包含非数字字符时提示用户重新输入
for(i=0 ;i < num1.size();i++)
{
if (num1[i]<'0' || num1[i]>'9') 
{
cout<<"您输入的数据不合法,请输入有效的整数!"<<endl;
cin>>num1;
i=-1;
}
}
 
cout<<"请输入第二个大整数(任意长度):";
cin>>num2;
//判断第二个输入的数据是否合法,当字符串中包含非数字字符时提示用户重新输入
for(i=0 ;i < num2.size();i++)
{
if (num2[i]<'0' || num2[i]>'9') 
{
cout<<"您输入的数据不合法,请输入有效的整数!"<<endl;
cin>>num2;
i=-1;
}
}
 
r=IntMult(num1,num2); 
 
//对求得的结果进行修剪，去掉最前面的几个0
while ('0' == r[0]&&r.size()>1)
{
r=r.substr(1,r.size()-1);
}
cout<<"两数相乘结果为:"<<endl;
cout<<num1<<" "<<"*"<<" "<<num2<<" "<<"="<<" "<<r<<endl<<endl;     
}
 
}