#ifndef MUSHROOM_H
#define MUSHROOM_H
#include <string>

using namespace std;

class Mushroom{
public:
	char capShape;
	char capSurface;
	char capColor;
	char bruises;
	char odor;
	char gillAttachment;
	char gillSpacing;
	char gillSize;
	char gillColor;
	char stalkShape;
	char stalkRoot;
	char stalkSurfaceAboveRing;
	char stalkSurfaceBelowRing;
	char stalkColorAboveRing;
	char stalkColorBelowRing;
	char veilType;
	char veilColor;
	char ringNumber;
	char ringType;
	char sporePrintColor;
	char population;
	char habitat;
	char poisonous;

	char getFeature(string temp){
		if(temp == "capshape"){
			return capShape;
		}
		else if(temp == "capsurface"){
			return capSurface;
		}
		else if(temp == "capcolor"){
			return capColor;
		}
		else if(temp == "bruises"){
			return bruises;
		}
		else if(temp == "odor"){
			return odor;
		}
		else if(temp == "gillattachment"){
			return gillAttachment;
		}
		else if(temp == "gillspacing"){
			return gillSpacing;
		}
		else if(temp == "gillsize"){
			return gillSize;
		}
		else if(temp == "gillcolor"){
			return gillColor;
		}
		else if(temp == "stalkshape"){
			return stalkShape;
		}
		else if(temp == "stalkroot"){
			return stalkRoot;
		}
		else if(temp == "stalksurfaceabovering"){
			return stalkSurfaceAboveRing;
		}
		else if(temp == "stalksurfacebelowring"){
			return stalkSurfaceBelowRing;
		}
		else if(temp == "stalkcolorabovering"){
			return stalkColorAboveRing;
		}
		else if(temp == "stalkcolorbelowring"){
			return stalkColorBelowRing;
		}
		else if(temp == "veiltype"){
			return veilType;
		}
		else if(temp == "veilcolor"){
			return veilColor;
		}
		else if(temp == "ringnumber"){
			return ringNumber;
		}
		else if(temp == "ringtype"){
			return ringType;
		}
		else if(temp == "sporeprintcolor"){
			return sporePrintColor;
		}
		else if(temp == "population"){
			return population;
		}
		else if(temp == "habitat"){
			return habitat;
		}
		else if(temp == "poisonous"){
			return poisonous;
		}
	}
	
	Mushroom(char a, char b, char c, char d, char e, char f, 
			 char g, char h, char i, char j, char k, char l, 
			 char m, char n, char o, char p, char q, char r, 
			 char s, char t, char u, char v, char w)
	{
		capShape = a; capSurface = b; capColor = c; bruises = d; odor = e;
		gillAttachment = f; gillSpacing = g; gillSize = h; gillColor = i; 
		stalkShape = j; stalkRoot = k; stalkSurfaceAboveRing = l; 
		stalkSurfaceBelowRing = m; stalkColorAboveRing = n; stalkColorBelowRing = o; 
		veilType = p; veilColor = q; ringNumber = r; ringType = s; sporePrintColor = t; 
		population = u; habitat = v; poisonous = w;
	}
};
#endif