#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>

#include "Tree.h"
using namespace std;

class DecisionTree {
private:

	struct attrItem
	{
		std::vector<int>  itemNum;  //itemNum[0] = itemLine.size()记录总共相同的项有多少个
								    //itemNum[1] = H1类的个数
		                            //itemNum[2] = H2类的个数
		                            //itemNum[3] = H3类的个数
		                            //itemNum[4] = H4类的个数
		set<int>		  itemLine;//记录行号
	};

	struct attributes
	{
		string attriName;   //属性名称
		vector<double> statResult; //保存当前的Info值
		map<string, attrItem*> attriItem;//属性值与该属性对应的数目以及该属性下分类为yes的数目及对应的行号
	}; 

	vector<attributes*> statTree;
	int attriNum;
	vector<vector<string>> infos;
	vector<vector<string>> test_infos;
	map<string, int> attr_clum; //属性名与列号的映射
	
public:
	DecisionTree(){
		attriNum = 0;
	}
	vector<vector<string>>& getInfos()
	{
		return infos;
	}
	vector<attributes*>& getStatTree()
	{
		return statTree;
	}
	int pretreatment(string filename, set<int>& readLineNum, vector<int>& readClumNum);
	int Testinput(string filename);
	int statister(vector<vector<string>>& infos, vector<attributes*>& statTree, 
					set<int>& readLine, vector<int>& readClumNum,vector<int>& TNM_num);
	int compuDecisiNote(vector<attributes*>& statTree, vector<int>& TNM_num, int lineNum, vector<int>& readClumNum);
	double info_D(vector<int>& TNM_num, int sum);
	void resetStatTree(vector<attributes*>& statTree, vector<int>& readClumNum);
	double Info_attr(map<string, attrItem*>& attriItem, double& splitInfo, int lineNum);
	void CreatTree(TreeNode* treeHead, vector<attributes*>& statTree, vector<vector<string>>& infos,
				  set<int>& readLine, vector<int>& readClumNum, int deep);
};
