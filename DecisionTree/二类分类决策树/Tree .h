#pragma once

#include <vector>
#include <set>
#include <string>

using namespace std;

struct TreeNode 
{
	std::string               m_sAttribute;
	int						  m_iDeciNum;
	int					      m_iUnDecinum;
	std::vector<TreeNode*>    m_vChildren; 
	std::string               branch;
};

TreeNode* CreateTreeNode(string value);
void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild);
void PrintTreeNode(TreeNode* pNode);
void PrintTree(TreeNode* pRoot);
void DestroyTree(TreeNode* pRoot);
bool FindNode(TreeNode* pRoot, std::string& item);
