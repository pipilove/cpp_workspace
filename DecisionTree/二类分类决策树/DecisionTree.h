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
		std::vector<int>  itemNum;  //itemNum[0] = itemLine.size()��¼�ܹ���ͬ�����ж��ٸ�
								    //itemNum[1] = H1��ĸ���
		                            //itemNum[2] = H2��ĸ���
		                            //itemNum[3] = H3��ĸ���
		                            //itemNum[4] = H4��ĸ���
		set<int>		  itemLine;//��¼�к�
	};

	struct attributes
	{
		string attriName;   //��������
		vector<double> statResult; //���浱ǰ��Infoֵ
		map<string, attrItem*> attriItem;//����ֵ������Զ�Ӧ����Ŀ�Լ��������·���Ϊyes����Ŀ����Ӧ���к�
	}; 

	vector<attributes*> statTree;
	int attriNum;
	vector<vector<string>> infos;
	map<string, int> attr_clum; //���������кŵ�ӳ��
	
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
	int statister(vector<vector<string>>& infos, vector<attributes*>& statTree, 
					set<int>& readLine, vector<int>& readClumNum);
	int compuDecisiNote(vector<attributes*>& statTree, int deciNum, int lineNum, vector<int>& readClumNum);
	double info_D(int deciNum, int sum);
	void resetStatTree(vector<attributes*>& statTree, vector<int>& readClumNum);
	double Info_attr(map<string, attrItem*>& attriItem, double& splitInfo, int lineNum);
	void CreatTree(TreeNode* treeHead, vector<attributes*>& statTree, vector<vector<string>>& infos,
				  set<int>& readLine, vector<int>& readClumNum, int deep);
};
