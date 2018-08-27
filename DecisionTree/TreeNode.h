#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <string>
#include <vector>
#include <map>	

using namespace std;

struct TreeNode{
	std::string featureName;
    //char fValue;
	bool poisonous = false;
    bool isLeaf = false;
	int featureIndex;
	TreeNode* parent;
	map<char, TreeNode*> children;
	//std::vector<TreeNode*> children;
};

#endif
