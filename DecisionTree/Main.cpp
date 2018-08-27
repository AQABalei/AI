#include "Parser.h"
#include "TreeLearner.h"

using namespace std;

int myrandom (int i) { return rand()%i;}

vector <Mushroom> mushrooms;

int main(int argc, const char* argv []){
	vector<Mushroom> trainingSet;
	vector<Mushroom> validationSet;
	vector<Mushroom> testingSet;
	Parser* p = new Parser();
	TreeLearner* tl = new TreeLearner();
	mushrooms = p->parse(argv[1]);
	int c = 0;
	for(int i=0; i<p->fnames.size(); ++i){
		if(p->fnames[i] == "poisonous"){
			c = i;
		}
	}
	p->fnames.erase(p->fnames.begin() + c);
	srand(time(0));
	random_shuffle(mushrooms.begin(), mushrooms.end(), myrandom);
	int trainSize = mushrooms.size() * 0.8;
	for(int i=0; i<mushrooms.size(); ++i){
		if(i < trainSize){
			trainingSet.push_back(mushrooms[i]);
		}
		else{
			testingSet.push_back(mushrooms[i]);
		}
	}
	TreeNode* root1 = tl->decisionTreeLearning(trainingSet, p->fnames, trainingSet, mushrooms, -1, -1);
	int t = 0;
	int t1 = 0;
	for(int i=0; i<trainingSet.size(); ++i){
		if((int)tl->Test(root1, trainingSet[i]) == trainingSet[i].getFeature("poisonous") - 48){
			t++;
		}
	}
	for(int i=0; i<testingSet.size(); ++i){
		if((int)tl->Test(root1, testingSet[i]) == testingSet[i].getFeature("poisonous") - 48){
			t1++;
		}
	}
	cout << "80 percent training exampls: " << endl;
	cout << "Number of correct examples: " << t << endl;
	cout << "Number of total examples: " << trainingSet.size() <<endl;
	cout << "Accuracy: " << t/trainingSet.size() << endl;

	cout << endl;

	cout << "20 percent testing examples: " << endl;
	cout << "Number of correct examples: " << t1 <<endl;
	cout << "Number of total examples: " << testingSet.size() <<endl;
	cout << "Accuracy: " << ((double)t1/testingSet.size()) << endl;

	cout << endl << endl;

	trainingSet.clear();
	testingSet.clear();
	trainSize = mushrooms.size() * 0.6;
	int validationSize = mushrooms.size() * 0.2;
	for(int i=0; i<mushrooms.size(); ++i){
		if(i < trainSize){
			trainingSet.push_back(mushrooms[i]);
		}
		else if(i >= trainSize && i <= (validationSize + trainSize)){
			validationSet.push_back(mushrooms[i]);
		}
		else{
			testingSet.push_back(mushrooms[i]);
		}
	}
	cout << "Depth" << "         " << "train" << "         " << "valid" << endl;
	vector<double> tobeMax;
	for(int j=0; j<15; ++j){
		int new_c1 = 0;
		int new_c2 = 0;
		TreeNode* root2 = tl->decisionTreeLearning(trainingSet, p->fnames, trainingSet, mushrooms, j, 0);
		for(int i=0; i<trainingSet.size(); ++i){
			if((int)tl->Test(root2, trainingSet[i]) == trainingSet[i].getFeature("poisonous") - 48){
				new_c1 ++;
			}
		}
		for(int i=0; i<validationSet.size(); ++i){
			if((int)tl->Test(root2, validationSet[i]) == validationSet[i].getFeature("poisonous") - 48){
				new_c2 ++;
			}
		}
		cout << j+1 << "          " << ((double)new_c1/trainingSet.size()) << "     " << ((double)new_c2/validationSet.size()) << endl;
		tobeMax.push_back(((double)new_c2/validationSet.size()));
	}
	int selected = p->getPosForDouble(tobeMax, *max_element(tobeMax.begin(), tobeMax.end()));
	cout << "The maximum accuracy comes from depth: " << selected+1 << endl;
	vector<Mushroom> finalSet;
	for(int i=0; i<validationSet.size(); ++i){
		finalSet.push_back(validationSet[i]);
	}
	for(int i=0; i<trainingSet.size(); ++i){
		finalSet.push_back(trainingSet[i]);
	}
	TreeNode* root3 = tl->decisionTreeLearning(finalSet, p->fnames, finalSet, mushrooms, selected, 0);
	int finalacc = 0;
	for(int i=0; i<testingSet.size(); ++i){
		if((int)tl->Test(root3, testingSet[i]) == testingSet[i].getFeature("poisonous") - 48){
			finalacc ++;
		}
	}
	cout << endl;
	cout << "Final tree with depth: " << selected+1 << endl;
	cout << "Number of correct examples: " <<finalacc <<endl;
	cout << "Number of total examples: " <<testingSet.size() <<endl;
	cout << "Accuracy: " << ((double)finalacc/testingSet.size()) << endl;
}
