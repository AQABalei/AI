//
//  TreeLearner.cpp
//  360
//
//  Created by Zhong Chu on 10/29/17.
//  Copyright © 2017 Zhong Chu. All rights reserved.
//

#include "TreeLearner.h"
#include <iostream>
using namespace std;

map<char, int> TreeLearner::getMapByFeatureName(string featureName, vector<Mushroom> mushrooms){
    map<char, int> ret;
    for(int i=0; i<mushrooms.size(); ++i){
        char fv = mushrooms[i].getFeature(featureName);
        if(ret.find(fv) == ret.end()){
            ret[fv] = 1;
        }
        else{
            int temp = ret[fv] + 1;
            ret.erase(fv);
            ret[fv] = temp;
        }
    }
    return ret;
}

TreeNode* TreeLearner::decisionTreeLearning(vector<Mushroom> mushrooms, vector<string> featureNames, vector<Mushroom> parents, vector<Mushroom> all, int depthLimit, int currDepth){
    if(mushrooms.empty()){
        return pluralityVal(parents);
    }
    else if(allSameClass(mushrooms) != -1){
        TreeNode* ret = new TreeNode();
        ret->isLeaf = true;
        ret->poisonous = (mushrooms[0].getFeature("poisonous") == '1');
        return ret;
    }
    else if(featureNames.empty()){
        return pluralityVal(mushrooms);
    }
    if(depthLimit != -1 && depthLimit == currDepth){
        return pluralityVal(mushrooms);
    }
    else{
        string A = "";
        double arena = -1;
        int record = 0;
        for(int i=0; i<featureNames.size(); ++i){
            double candidate = Gain(featureNames[i], mushrooms);
            if(candidate > arena){
                A = featureNames[i];
                arena = candidate;
                record = i;
            }
        }
        featureNames.erase(featureNames.begin()+record);
        TreeNode* tree = new TreeNode();
        tree->featureName = A;
        map<char, int> sort = getMapByFeatureName(A, all);
        for(map<char, int>::iterator it = sort.begin(); it != sort.end(); ++it){
            vector<Mushroom> toPass;
            for(int i=0; i<mushrooms.size(); ++i){
                if(mushrooms[i].getFeature(A) == it->first){
                    toPass.push_back(mushrooms[i]);
                }
            }
            TreeNode* subtree = decisionTreeLearning(toPass, featureNames, mushrooms, all, depthLimit, currDepth+1);
            tree->children.emplace(it->first, subtree);
        }
        return tree;
    }
}

int TreeLearner::allSameClass(vector<Mushroom> mushrooms){
    int pCounter = 0;
    int npCounter = 0;
    for(int i=0; i<mushrooms.size(); ++i){
        if(mushrooms[i].getFeature("poisonous") == '1'){
            pCounter++;
        }
        else{
            npCounter++;
        }
    }
    if(pCounter == 0 || npCounter == 0){
        if(pCounter != 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    return -1;
}

TreeNode* TreeLearner::pluralityVal(vector<Mushroom> mushrooms){
    int c = 0;
    int size = mushrooms.size();
    for(int i=0; i<size; ++i){
        if(mushrooms[i].getFeature("poisonous") == '1'){
            c++;
        }
    }
    TreeNode* ret = new TreeNode();
    ret->isLeaf = true;
    if(c >= size/2){
        ret->poisonous = true;
        return ret;
    }
    ret->poisonous = false;
    return ret;
}

double TreeLearner::H(string featureName, vector<Mushroom> mushrooms){
    map<char, int> poisonous;
    map<char, int> noPoisonous;
    for(int i=0; i<mushrooms.size(); ++i){
        char fv = mushrooms[i].getFeature(featureName);
        if(mushrooms[i].getFeature("poisonous") == '1'){
            if(poisonous.find(fv) == poisonous.end()){
                poisonous[fv] = 1;
            }
            else{
                int temp = poisonous[fv] + 1;
                poisonous.erase(fv);
                poisonous[fv] = temp;
            }
        }
        else if(mushrooms[i].getFeature("poisonous") == '0'){
            if(noPoisonous.find(fv) == noPoisonous.end()){
                noPoisonous[fv] = 1;
            }
            else{
                int temp = noPoisonous[fv] + 1;
                noPoisonous.erase(fv);
                noPoisonous[fv] = temp;
            }
        }
    }
    int total_size = mushrooms.size();
    double h = 0;
    for(map<char, int>::iterator itp = poisonous.begin(); itp != poisonous.end(); ++itp){
        for(map<char, int>::iterator itnp = noPoisonous.begin(); itnp != noPoisonous.end(); ++itnp){
            if(itnp->first == itp->first){
                double currShapeNum = itnp->second + itp->second;
                double tempITNP = itnp->second / currShapeNum;
                double tempITP = itp->second / currShapeNum;
                double temp = (currShapeNum/total_size) * (tempITP * log2(tempITP) + tempITNP * log2(tempITNP));
                h += temp;
            }
        }
    }
    return -h;
}

double TreeLearner::Gain(string featureName, vector<Mushroom> mushrooms){
    double pos_counter = 0;
    double size = mushrooms.size();
    for(int i=0; i<size; ++i){
        if(mushrooms[i].getFeature("poisonous") == '1'){
            pos_counter ++;
        }
    }
    double pos_counterOverSize = pos_counter/size;
    double temp = -((pos_counterOverSize* log2(pos_counterOverSize)
                     + (1-pos_counterOverSize) * log2(1-pos_counterOverSize)));
    double gain = temp - H(featureName, mushrooms);
    return gain;
}

bool TreeLearner::Test(TreeNode* root, Mushroom m){
    if(root->isLeaf == true){
        bool result = root->poisonous;
        return result;
    }
    else{
        return Test(root->children.at(m.getFeature(root->featureName)), m);
    }
}