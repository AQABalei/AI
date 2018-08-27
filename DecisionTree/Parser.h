#ifndef PARSER_H
#define PARSER_H

#include "Mushroom.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <set>

using namespace std;

class Parser{
public:
	vector<string> fnames;

	int getPos(vector<string> vec, string temp){
		vector<string>::iterator it;
		it = find(vec.begin(), vec.end(), temp);
		return it - vec.begin();
	}

	int getPosForDouble(vector<double> vec, double temp){
		vector<double>::iterator it;
		it = find(vec.begin(), vec.end(), temp);
		return it - vec.begin();
	}

	vector<Mushroom> parse(string fileName){
		vector<Mushroom> mushrooms;
		ifstream input(fileName.c_str());
		if(!input.fail()){
			string curr;
			stringstream ss;
			getline(input, curr);
			vector<string> propNames;
			ss << curr;
			while(ss.good()){
				string substr;
				getline(ss, substr, ',');
				propNames.push_back(substr);
				set<char> useless;
			}
			fnames = propNames;
			stringstream ss1;
			while(getline(input, curr)){
				vector<string> properties;
				ss1 << curr;
				while(ss1.good()){
					string i;
					getline(ss1, i, ',');
					properties.push_back(i);
				}
				ss1.clear();
				Mushroom m(properties[getPos(propNames, "capshape")][0],
					   properties[getPos(propNames, "capsurface")][0],
					   properties[getPos(propNames, "capcolor")][0],
					   properties[getPos(propNames, "bruises")][0],
					   properties[getPos(propNames, "odor")][0],
					   properties[getPos(propNames, "gillattachment")][0],
					   properties[getPos(propNames, "gillspacing")][0],
					   properties[getPos(propNames, "gillsize")][0],
					   properties[getPos(propNames, "gillcolor")][0],
					   properties[getPos(propNames, "stalkshape")][0],
					   properties[getPos(propNames, "stalkroot")][0],
					   properties[getPos(propNames, "stalksurfaceabovering")][0],
					   properties[getPos(propNames, "stalksurfacebelowring")][0],
					   properties[getPos(propNames, "stalkcolorabovering")][0],
					   properties[getPos(propNames, "stalkcolorbelowring")][0],
					   properties[getPos(propNames, "veiltype")][0],
					   properties[getPos(propNames, "veilcolor")][0],
					   properties[getPos(propNames, "ringnumber")][0],
					   properties[getPos(propNames, "ringtype")][0],
					   properties[getPos(propNames, "sporeprintcolor")][0],
					   properties[getPos(propNames, "population")][0],
					   properties[getPos(propNames, "habitat")][0],
					   properties[getPos(propNames, "poisonous")][0]);
				mushrooms.push_back(m);
			}
		}
		return mushrooms;
	}
};
#endif