#ifndef TREE_LEARNER_H
#define TREE_LEARNER_H

#include "Mushroom.h"
#include "TreeNode.h"
#include "Parser.h"
#include <map>
#include <cmath>

class TreeLearner{
public:
    map<char, int> getMapByFeatureName(string featureName, vector<Mushroom> mushrooms);
    TreeNode* decisionTreeLearning(vector<Mushroom> mushrooms, vector<string> featureNames, vector<Mushroom> parents, vector<Mushroom> all, int depthLimit, int currDepth);
    int allSameClass(vector<Mushroom> mushrooms);
    TreeNode* pluralityVal(vector<Mushroom> mushrooms);
    double H(string featureName, vector<Mushroom> mushrooms);
    double Gain(string featureName, vector<Mushroom> mushrooms);
    bool Test(TreeNode* root, Mushroom m);
};
#endif
