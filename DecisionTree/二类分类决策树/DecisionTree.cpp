#include "DecisionTree.h"

int main(int argc, char* argv[]){
	string filename = "source.txt";
	DecisionTree dt ;
	int attr_node = 0;
	TreeNode* treeHead = nullptr;
	set<int> readLineNum;  //��¼ÿһ�е��к�
	vector<int> readClumNum;//���������У�0��ʾ����
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
* @function pretreatment Ԥ������������������ݣ���������Ϣ��������Ա��
* @param: filename �ļ���
* @param: readLineNum ��ʹ����set
* @param: readClumNum ��������set
* @return int ���غ���ִ��״̬
*/
int DecisionTree::pretreatment(string filename, set<int>& readLineNum, vector<int>& readClumNum)
{
	ifstream read(filename.c_str());
	string itemline = "";
	getline(read, itemline);
	istringstream iss(itemline);
	string attr = "";
	//�����һ�У�������
	while(iss >> attr)
	{
		attributes* s_attr = new attributes();
		s_attr->attriName = attr;
		//��ʼ��������
		statTree.push_back(s_attr);
		//��ʼ������ӳ��
		attr_clum[attr] = attriNum;//�Ѷ�Ӧ��������ӳ�䵽��Ӧ���б����
		attriNum++;
		//��ʼ������������
		readClumNum.push_back(0);
		s_attr = nullptr;
	}

	int i  = 0;
	//��Ӿ�������
	while(true)
	{
		getline(read, itemline);//����ÿһ�У���ÿһ�е����Բ�ֿ��󣬲���infos�У��γ���Ϣ����
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
		readLineNum.insert(i);//����ÿһ�е��к�
		i++;
	}
	read.close();
	return 0;
}

int DecisionTree::statister(vector<vector<string>>& infos, vector<attributes*>& statTree, 
							set<int>& readLine, vector<int>& readClumNum)//readLine���Ǽ�¼ÿһ���кŵ�����
{
	//yes��������
	int deciNum = 0;
	//ͳ��ÿһ��
	set<int>::iterator iter_end = readLine.end();
	for (set<int>::iterator line_iter = readLine.begin(); line_iter != iter_end; ++line_iter)
	{
		bool decisLine = false;
		if (infos[*line_iter][attriNum - 1] == "yes")
		{
			decisLine = true;//����������ǲ���yes
			deciNum++; //���ã���Ϊ�����ĺ;��������ڼ���ʱ�Զ��ͼ����������
		}
		//�������δ����������Ϊ�����У�����ͳ��
		for (int i = 0; i < attriNum - 1; i++)
		{
			if (readClumNum[i] == 0)
			{
				std::string tempitem = infos[*line_iter][i];//��ȡ��line_iter�еĵ�i�����Ե�����ֵ
				auto map_iter = statTree[i]->attriItem.find(tempitem);
				//�����stateTree[i]��attriItem��������û���ҵ����½�һ�����
				if (map_iter == (statTree[i]->attriItem).end())
				{
					//�½�
					attrItem* attritem = new attrItem();
					attritem->itemNum.push_back(1);//����1ֵ��Ϊ���������
					decisLine ? attritem->itemNum.push_back(1) : attritem->itemNum.push_back(0);//���������yes������1,�������0
					attritem->itemLine.insert(*line_iter);//��¼����к�
					//����������->itemӳ��
					(statTree[i]->attriItem)[tempitem] = attritem;
					attritem = nullptr;
				}
				else
				{
					(map_iter->second)->itemNum[0]++;//���°���������
					(map_iter->second)->itemLine.insert(*line_iter);
					if(decisLine)
					{
						(map_iter->second)->itemNum[1]++;//���°�����yes��Ŀ
					}
				}
			}
		}
	}
	return deciNum;
}

/*
* @function CreatTree �ݹ�DFS���������������
* @param: treeHead Ϊ���ɵľ�����
* @param: statTree Ϊ״̬����������̬���£�����������DFS�����ݸ��£����Բ���ÿ���½�״̬��
* @param: infos ������Ϣ
* @param: readLine ��ǰ��infos����Ҫ����ͳ�Ƶ��������ɺ��������
* @param: readClumNum �����������
* @param: deep ����������ȣ����ڴ�ӡ
* @return void
*/
void DecisionTree::CreatTree(TreeNode* treeHead, vector<attributes*>& statTree, vector<vector<string>>& infos, 
							 set<int>& readLine, vector<int>& readClumNum, int deep)
{
	//�п�ͳ�Ƶ���
	if (readLine.size() != 0)
	{
		string treeLine = "";
		//for (int i = 0; i < deep; i++)
		//{
		//	treeLine += "--";
	//	}
		//��������������������еݹ�
		resetStatTree(statTree, readClumNum);
		//ͳ�Ƶ�ǰreadLine�е����ݣ�����ͳ���ļ������ԡ���Щ�У�
		//������statTree�����ڹ���һ��statTree�����������ô��棩��������Ŀ����Ϣ��
		int deciNum = statister(getInfos(), statTree, readLine, readClumNum);
		int lineNum = readLine.size();
		int attr_node = compuDecisiNote(statTree, deciNum, lineNum, readClumNum);//��������Ϊ�ֲ�����
		//���б�����
		readClumNum[attr_node] = 1;
		//��������
		TreeNode* treeNote = new TreeNode();
		treeNote->m_sAttribute = statTree[attr_node]->attriName;//���ýڵ��������
		treeNote->m_iDeciNum = deciNum;               //���ýڵ��Ӧ�ķ���Ϊyes�ĸ���
		treeNote->m_iUnDecinum = lineNum - deciNum;   //���ýڵ���಻Ϊ
		if (treeHead == nullptr)
		{
			treeHead = treeNote; //����
		}
		else
		{
			treeHead->m_vChildren.push_back(treeNote); //�ӽڵ�
		}
		cout << "�ڵ�-"<< treeLine << ">" << statTree[attr_node]->attriName << " " << deciNum << " " << lineNum - deciNum << endl;
		bool flag=false;
		if(statTree[attr_node]->attriItem.size()==1&&readClumNum[0]==1&&readClumNum[1]==1&&readClumNum[2]==1&&readClumNum[3]==1)
		{
			flag=true;
		}
	
		//�Ӻ��ӷ�֧���еݹ�
		for(map<string, attrItem*>::iterator map_iterator = statTree[attr_node]->attriItem.begin();
			map_iterator != statTree[attr_node]->attriItem.end(); ++map_iterator)
		{
			//��ӡ��֧
			int sum = map_iterator->second->itemNum[0];
			int deci_Num = map_iterator->second->itemNum[1];
			cout <<statTree[attr_node]->attriName<< "�ķ�֧--"<< treeLine << ">" << map_iterator->first << endl;
			//�ݹ���㡢����
		
			if (deci_Num != 0 && sum != deci_Num &&!flag)
			{
				//������Ч����
				set<int> newReadLineNum = map_iterator->second->itemLine;
				//DFS
				CreatTree(treeNote, statTree, infos, newReadLineNum, readClumNum, deep + 1);
			}
			else
			{
				//����Ҷ�ӽڵ�
				TreeNode* treeEnd = new TreeNode();
				treeEnd->m_sAttribute = statTree[attr_node]->attriName;
				treeEnd->m_iDeciNum = deci_Num;
				treeEnd->m_iUnDecinum = sum - deci_Num;
				treeNote->m_vChildren.push_back(treeEnd);
				//��ӡҶ��
				if(flag)
				{
					cout <<statTree[attr_node]->attriName<< "�ķ�֧--"<< map_iterator->first <<"��Ҷ��---"<< treeLine << ">yes or no" << " " << sum << endl;
				}
				else if (deci_Num == 0)
				{
					cout <<statTree[attr_node]->attriName<< "�ķ�֧--"<< map_iterator->first <<"��Ҷ��---"<<treeLine << ">no" << " " << sum << endl;
				}
				else
				{
					cout <<statTree[attr_node]->attriName<< "�ķ�֧--"<< map_iterator->first <<"��Ҷ��---"<< treeLine  << ">yes" << " " << deci_Num <<endl;
				}
			}
		}
		//��ԭ�����п�����
		readClumNum[attr_node] = 0;
	}
}
/*
* @function compuDecisiNote ����C4.5
* @param: statTree Ϊ״̬����������̬���£�����������DFS�����ݸ��£����Բ���ÿ���½�״̬��
* @param: deciNum Yes��������
* @param: lineNum ����set������
* @param: readClumNum ���ڼ����set
* @return int ��Ϣ���������Ժ�
*/
int DecisionTree::compuDecisiNote(vector<attributes*>& statTree, int deciNum, int lineNum, vector<int>& readClumNum)
{
	double max_temp = -1;
	int max_attribute = 0;
	//�ܵ�yes�е���Ϣ��
	double infoD = info_D(deciNum, lineNum);
	for (int i = 0; i < attriNum - 1; i++)
	{
		//����δ�����������Ե�Info
		if (readClumNum[i] == 0)
		{
			double splitInfo = 0.0;
			//info
			double info_temp = Info_attr(statTree[i]->attriItem, splitInfo, lineNum);//��������Ե�Infoֵ
			statTree[i]->statResult.push_back(info_temp);
			//gain
			double gain_temp = infoD - info_temp;
			statTree[i]->statResult.push_back(gain_temp);
			//split_info
			statTree[i]->statResult.push_back(splitInfo);
			//gain_info
			double temp = gain_temp;
			statTree[i]->statResult.push_back(temp);
			//�õ����ֵ*/
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
* @function Info_attr info_D ����Ϣ��
* @param: deciNum ��Ч��Ϣ��
* @param: sum ����Ϣ��
* @return double ����Ϣ������
*/
double DecisionTree::info_D(int deciNum, int sum)
{
	double pi = (double)deciNum / (double)sum;
	double result = 0.0;
	if (pi == 1.0 || pi == 0.0)
	{
		return result;
	}
	result = pi * (log(pi) / log((double)2)) + (1 - pi)*(log(1 - pi)/log((double)2));
	return -result;
}
/*
* @function Info_attr ����Ϣ��
* @param: deciNum ��Ч��Ϣ��
* @param: sum ����Ϣ��
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
		 splitInfo += pi * (log(pi) / log((double)2));
		 double sub_attr = info_D(item->second->itemNum[1], item->second->itemNum[0]);
		 result += pi * sub_attr;
	}
	splitInfo = -splitInfo;
	return result;
}
/*
* @function resetStatTree ����״̬��
* @param: statTree ״̬��
* @param: readClumNum ��Ҫ���������set
* @return void
*/
//���δ�����������Ե�statTree
void DecisionTree::resetStatTree(vector<attributes*>& statTree, vector<int>& readClumNum)
{
	for (int i = 0; i < readClumNum.size() - 1; i++)
	{
		if (readClumNum[i] == 0)//δ������i��
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