#include "DecisionTree.h"

int main(int argc, char* argv[]){
	string filename = "source.txt";
	DecisionTree dt ;
	int attr_node = 0;
	TreeNode* treeHead = nullptr;
	set<int> readLineNum;  //记录每一行的行号
	vector<int> readClumNum;//可用属性列，0表示可用
	int deep = 0;
	if (dt.pretreatment(filename, readLineNum, readClumNum) == 0)
	{
		dt.CreatTree(treeHead, dt.getStatTree(), dt.getInfos(), readLineNum, readClumNum, deep);
	}


	int A;
	cin>>A;
	return 0;
}
/*
* @function pretreatment 预处理函数，负责读入数据，并生成信息矩阵和属性标记
* @param: filename 文件名
* @param: readLineNum 可使用行set
* @param: readClumNum 可用属性set
* @return int 返回函数执行状态
*/
int DecisionTree::pretreatment(string filename, set<int>& readLineNum, vector<int>& readClumNum)
{
	ifstream read(filename.c_str());
	string itemline = "";
	getline(read, itemline);
	istringstream iss(itemline);
	string attr = "";
	//读入第一行，属性名
	while(iss >> attr)
	{
		attributes* s_attr = new attributes();
		s_attr->attriName = attr;
		//初始化属性名
		statTree.push_back(s_attr);
		//初始化属性映射
		attr_clum[attr] = attriNum;//把对应的属性名映射到相应的列标号上
		attriNum++;
		//初始化可用属性列
        readClumNum.push_back(0);
		s_attr = nullptr;
	}
	int i  = 0;
	//添加具体数据
	while(true)
	{
		getline(read, itemline);//读入每一行，把每一行的属性拆分开后，插入infos中，形成信息矩阵
		if(itemline == "" || itemline.length() <= 1)
		{
			break;
		}
		vector<string> infoline;
		istringstream stream(itemline);
		string item = "";
		while(stream >> item)
		{
			infoline.push_back(item);
		}

		infos.push_back(infoline);
		readLineNum.insert(i);//加入每一行的行号
		i++;
	}
	read.close();
	return 0;
}


/*
* @function Testinput 预处理函数，负责读入test数据，并生成信息矩阵和属性标记
* @param: filename 文件名
* @return int 返回函数执行状态
*/
int DecisionTree::Testinput(string filename)
{
	ifstream read(filename.c_str());
	string itemline = "";
	
	//添加具体数据
	while(true)
	{
		getline(read, itemline);//读入每一行，把每一行的属性拆分开后，插入infos中，形成信息矩阵
		if(itemline == "" || itemline.length() <= 1)
		{
			break;
		}
		vector<string> infoline;
		istringstream stream(itemline);
		string item = "";
		while(stream >> item)
		{
			infoline.push_back(item);
		}

		test_infos.push_back(infoline);
	
	}
	read.close();
	return 0;
}






int DecisionTree::statister(vector<vector<string>>& infos, vector<attributes*>& statTree, 
							set<int>& readLine, vector<int>& readClumNum,vector<int>& TNM_num)//readLine就是记录每一行行号的容器
{
	//yes的总行数
	int deciNum = 0;
	//统计每一行
	set<int>::iterator iter_end = readLine.end();
	for (set<int>::iterator line_iter = readLine.begin(); line_iter != iter_end; ++line_iter)
	{
		int decisLine = 0;
		if (infos[*line_iter][attriNum - 1] == "H1")
		{
			decisLine = 1;//标记最后分类是不是yes
			TNM_num[1]++; //无用，因为子树的和就是他，在计算时自动就加完这个数了
		}
		if (infos[*line_iter][attriNum - 1] == "H2")
		{
			decisLine = 2;//标记最后分类是不是yes
			TNM_num[2]++; //无用，因为子树的和就是他，在计算时自动就加完这个数了
		}
		if (infos[*line_iter][attriNum - 1] == "H3")
		{
			decisLine = 3;//标记最后分类是不是yes
			TNM_num[3]++; //无用，因为子树的和就是他，在计算时自动就加完这个数了
		}
		if (infos[*line_iter][attriNum - 1] == "H4")
		{
			decisLine = 4;//标记最后分类是不是yes
			TNM_num[4]++; //无用，因为子树的和就是他，在计算时自动就加完这个数了
		}
		//如果该列未被锁定并且为属性列，进行统计
		for (int i = 0; i < attriNum - 1; i++)
		{
			if (readClumNum[i] == 0)
			{
				std::string tempitem = infos[*line_iter][i];//获取第line_iter行的第i个属性的属性值
				auto map_iter = statTree[i]->attriItem.find(tempitem);
				//如果在stateTree[i]的attriItem属性项中没有找到，新建一项加入
				if (map_iter == (statTree[i]->attriItem).end())
				{
					//新建
					attrItem* attritem = new attrItem();
					attritem->itemNum.push_back(1);//加入1值作为该项的行数
					attritem->itemNum.push_back(0);attritem->itemNum.push_back(0);
					attritem->itemNum.push_back(0);attritem->itemNum.push_back(0);//初始化四个位置，用于记录各个类的数目
					attritem->itemNum[decisLine]++;
					attritem->itemLine.insert(*line_iter);//记录项的行号
					//建立属性名->item映射
					(statTree[i]->attriItem)[tempitem] = attritem;
					attritem = nullptr;
				}
				else
				{
					(map_iter->second)->itemNum[0]++;//更新包含的行数
					(map_iter->second)->itemLine.insert(*line_iter);					
					(map_iter->second)->itemNum[decisLine]++;//更新包含的yes数目
				}
			}
		}
	}
	return deciNum;
}

/*
* @function CreatTree 递归DFS创建并输出决策树
* @param: treeHead 为生成的决定树
* @param: statTree 为状态树，此树动态更新，但是由于是DFS对数据更新，所以不必每次新建状态树
* @param: infos 数据信息
* @param: readLine 当前在infos中所要进行统计的行数，由函数外给出
* @param: readClumNum 读入的数据列
* @param: deep 决定树的深度，用于打印
* @return void
*/
void DecisionTree::CreatTree(TreeNode* treeHead, vector<attributes*>& statTree, vector<vector<string>>& infos, 
							 set<int>& readLine, vector<int>& readClumNum, int deep)
{
	//有可统计的行
	if (readLine.size() != 0)
	{
		string treeLine = "";
		//for (int i = 0; i < deep; i++)
		//{
		//	treeLine += "--";
	//	}
		//清空其他属性子树，进行递归
		resetStatTree(statTree, readClumNum);
		vector<int> TNM_num;
	                                //TNM_num[0] = H1类的个数
		                            //TNM_num[1] = H2类的个数
		                            //TNM_num[2] = H3类的个数
		                            //TNM_num[3] = H4类的个数
		//初始化TNM分类计数
		TNM_num.push_back(0);TNM_num.push_back(0);TNM_num.push_back(0);TNM_num.push_back(0);TNM_num.push_back(0);

		//统计当前readLine中的数据：包括统计哪几个属性、哪些行，
		//并生成statTree（由于公用一个statTree，所有用引用代替），并返回目的信息数
		int deciNum = statister(getInfos(), statTree, readLine, readClumNum, TNM_num);
		int lineNum = readLine.size();
		int attr_node = compuDecisiNote(statTree, TNM_num, lineNum, readClumNum);//本条复制为局部变量
		//该列被锁定
		readClumNum[attr_node] = 1;
		//建立树根
		TreeNode* treeNote = new TreeNode();
		treeNote->m_sAttribute = statTree[attr_node]->attriName;//设置节点的属性名
		//treeNote->m_iDeciNum = deciNum;               //设置节点对应的分类为yes的个数
	//	treeNote->m_iUnDecinum = lineNum - deciNum;   //设置节点分类不为
		if (treeHead == nullptr)
		{
			treeHead = treeNote; //树根
		}
		else
		{
			treeHead->m_vChildren.push_back(treeNote); //子节点
		}
		cout << "节点-"<< treeLine << ">" << statTree[attr_node]->attriName << " " << endl;
		bool flag=false;
		if(statTree[attr_node]->attriItem.size()==1&&readClumNum[0]==1&&readClumNum[1]==1&&readClumNum[2]==1&&readClumNum[3]==1)
		{
			flag=true;
		}
	
		//从孩子分支进行递归
		for(map<string, attrItem*>::iterator map_iterator = statTree[attr_node]->attriItem.begin();
			map_iterator != statTree[attr_node]->attriItem.end(); ++map_iterator)
		{
			//打印分支
			int sum = map_iterator->second->itemNum[0];
			int deci_Num = map_iterator->second->itemNum[1];
			cout <<statTree[attr_node]->attriName<< "的分支--"<< treeLine << ">" << map_iterator->first << endl;
			//递归计算、创建
			if(flag)
			{
				TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
			//	treeEnd->m_iDeciNum = deci_Num;
			//	treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
				cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<< treeLine << ">all" << " " << sum << endl;
			}
			else if (TNM_num[1]!=0 && TNM_num[2]==0 && TNM_num[3]==0 && TNM_num[4]==0)
				{
					TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
			//	treeEnd->m_iDeciNum = deci_Num;
			//	treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H1" << " " << sum << endl;
				}
				else if (TNM_num[1]==0 && TNM_num[2]!=0 && TNM_num[3]==0 && TNM_num[4]==0)
				{
					TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
			//	treeEnd->m_iDeciNum = deci_Num;
			//	treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H2" << " " << sum << endl;
				}
				else if (TNM_num[1]==0 && TNM_num[2]==0 && TNM_num[3]!=0 && TNM_num[4]==0)
				{
					TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
			//	treeEnd->m_iDeciNum = deci_Num;
			//	treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H3" << " " << sum << endl;
				}
				else if (TNM_num[1]==0 && TNM_num[2]==0 && TNM_num[3]==0 && TNM_num[4]!=0)
				{
					TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
			//	treeEnd->m_iDeciNum = deci_Num;
			//	treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H4" << " " << sum << endl;
				}
				else
				{
					//计算有效行数
				set<int> newReadLineNum = map_iterator->second->itemLine;
				//DFS
				CreatTree(treeNote, statTree, infos, newReadLineNum, readClumNum, deep + 1);
				}



/*
		
			if (TNM_num[1]!=0 || TNM_num[2]!=0 || TNM_num[3]!=0 || TNM_num[4]!=0 && !flag)
			{
				//计算有效行数
				set<int> newReadLineNum = map_iterator->second->itemLine;
				//DFS
				CreatTree(treeNote, statTree, infos, newReadLineNum, readClumNum, deep + 1);
			}
			else
			{
				//建立叶子节点
				TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
			//	treeEnd->m_iDeciNum = deci_Num;
			//	treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
				//打印叶子
				if(flag)
				{
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<< treeLine << ">yes or no" << " " << sum << endl;
				}
				else if (TNM_num[1]!=0 && TNM_num[2]==0 && TNM_num[3]==0 && TNM_num[4]==0)
				{
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H1" << " " << sum << endl;
				}
				else if (TNM_num[1]==0 && TNM_num[2]!=0 && TNM_num[3]==0 && TNM_num[4]==0)
				{
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H2" << " " << sum << endl;
				}
				else if (TNM_num[1]==0 && TNM_num[2]==0 && TNM_num[3]!=0 && TNM_num[4]==0)
				{
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H3" << " " << sum << endl;
				}
				else if (TNM_num[1]==0 && TNM_num[2]==0 && TNM_num[3]==0 && TNM_num[4]!=0)
				{
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<<treeLine << ">H4" << " " << sum << endl;
				}
				else
				{
					cout <<statTree[attr_node]->attriName<< "的分支--"<< map_iterator->first <<"的叶子---"<< treeLine  << ">all" << " " << deci_Num <<endl;
				}
			}*/
		}
		//还原属性列可用性
		readClumNum[attr_node] = 0;
	}
}
/*
* @function compuDecisiNote 计算C4.5
* @param: statTree 为状态树，此树动态更新，但是由于是DFS对数据更新，所以不必每次新建状态树
* @param: deciNum Yes的数据量
* @param: lineNum 计算set的行数
* @param: readClumNum 用于计算的set
* @return int 信息量最大的属性号
*/
int DecisionTree::compuDecisiNote(vector<attributes*>& statTree, vector<int>& TNM_num, int lineNum, vector<int>& readClumNum)
{
	double max_temp = -1;
	int max_attribute = 0;
	//总的yes行的信息量
	double infoD = info_D(TNM_num, lineNum);
	for (int i = 0; i < attriNum - 1; i++)
	{
		//计算未被锁定的属性的Info
		if (readClumNum[i] == 0)
		{
			double splitInfo = 0.0;
			//info
			double info_temp = Info_attr(statTree[i]->attriItem, splitInfo, lineNum);//计算该属性的Info值
			statTree[i]->statResult.push_back(info_temp);
			//gain
			double gain_temp = infoD - info_temp;
			statTree[i]->statResult.push_back(gain_temp);
			//split_info
			statTree[i]->statResult.push_back(splitInfo);
			//gain_info
			double temp = gain_temp;
			statTree[i]->statResult.push_back(temp);
			//得到最大值*/
			if (temp > max_temp)
			{
				max_temp = temp;
				max_attribute = i;
			}
		}
	}
	return max_attribute;
}
/*
* @function Info_attr info_D 总信息量
* @param: deciNum 有效信息数
* @param: sum 总信息量
* @return double 总信息量比例
*/
double DecisionTree::info_D(vector<int>& TNM_num, int sum)
{
	double result=0.0;
	double pi;
	for(int i=1;i<TNM_num.size();i++)
	{
	   pi = (double)TNM_num[i] / (double)sum;
	   if(pi!=0)
	   {
          result = result+pi * (log(pi) / log((double)4));
	   }
	}
	return -result;
}
/*
* @function Info_attr 总信息量
* @param: deciNum 有效信息数
* @param: sum 总信息量
* @return double 
*/
double DecisionTree::Info_attr(map<string, attrItem*>& attriItem, double& splitInfo, int lineNum)
{
	double result = 0.0;
	for (map<string, attrItem*>::iterator item = attriItem.begin();
		 item != attriItem.end();
		 ++item
		)
	{
		 double pi = (double)(item->second->itemNum[0]) / (double)lineNum;
		 splitInfo += pi * (log(pi) / log((double)4));
		 double sub_attr = info_D(item->second->itemNum, item->second->itemNum[0]);
		 result += pi * sub_attr;
	}
	splitInfo = -splitInfo;
	return result;
}
/*
* @function resetStatTree 清理状态树
* @param: statTree 状态树
* @param: readClumNum 需要清理的属性set
* @return void
*/
//清除未被锁定的属性的statTree
void DecisionTree::resetStatTree(vector<attributes*>& statTree, vector<int>& readClumNum)
{
	for (int i = 0; i < readClumNum.size() - 1; i++)
	{
		if (readClumNum[i] == 0)//未被锁定i行
		{
			map<string, attrItem*>::iterator it_end = statTree[i]->attriItem.end();
			for (map<string, attrItem*>::iterator it = statTree[i]->attriItem.begin();
				it != it_end; it++)
			{
				delete it->second;
			}
			statTree[i]->attriItem.clear();
			statTree[i]->statResult.clear();
		}
	}
}