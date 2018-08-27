#include "Puzzle8Solver.h"

using namespace std;

void WeightedAStar(std::string puzzle, double w, int & cost, int & expansions) {
	cost = 0;
	expansions = 0;
	Puzzle8State initPS(puzzle);
	Puzzle8StateManager sm;
	Puzzle8StateManager smforCloseList;
	Puzzle8PQ openList;

	Puzzle8State finalPS;
	Puzzle8State currPS = initPS;
	while(currPS.form != finalPS.form){
		vector<Puzzle8State> Successors = currPS.GenerateSuccessors();
		for(int i=0; i<Successors.size(); ++i){
			Successors[i]._cost = currPS._cost + 1;
			double val_f = w * Successors[i].heuristic() + Successors[i]._cost;
			if(!sm.IsGenerated(Successors[i])){
				PQElement element(sm.GenerateState(Successors[i]), val_f, Successors[i]._cost);
				openList.push(element);
				sm.StateGetter.push_back(Successors[i]);
			}
			else if(sm.IsGenerated(Successors[i]) && smforCloseList.GetStateId(Successors[i]) == -1){
				if(Successors[i]._cost < sm.StateGetter[sm.GenerateState(Successors[i])]._cost){
					PQElement element(sm.GenerateState(Successors[i]), val_f, Successors[i]._cost);
					openList.push(element);
					sm.StateGetter[sm.GenerateState(Successors[i])]._cost = Successors[i]._cost;
				}
			}
			else{
				continue;
			}
		}
		currPS = sm.StateGetter[openList.top().id];
		cost = currPS._cost;
		while(smforCloseList.IsGenerated(currPS)){
			openList.pop();
		}
		openList.pop();
		expansions ++;
	}
}