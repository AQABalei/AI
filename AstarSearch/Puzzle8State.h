#ifndef STATE_8_PUZZLE_H
#define STATE_8_PUZZLE_H

#include <string>
#include <cassert>
#include <iostream>
#include <vector>

// Represents an 8-puzzle state as a 3x3 array of chars. Each char can take values in range '0'-'9' (chars, not integers).
// '0' represents the blank tile.
// Provides GetKey to uniquely represent the puzzle as an integer (for hashing).
// You can extend this class to generate successors and get heuristic distance to '012345678', which is always the goal state.

class Puzzle8State {
public:
	std::string form;
	int _cost;
	Puzzle8State(std::string s = "012345678") {
		assert(s.length() == 9);
		for (int r = 0; r < 3; r++){
			for (int c = 0; c < 3; c++){
				tiles[r][c] = s[r*3 + c];
			}
		}
		form = s;
		_cost = 0;
	}

	std::vector<Puzzle8State> GenerateSuccessors(){
		std::vector<Puzzle8State> toReturn;
		int zeroPos = this->form.find('0');
		if(zeroPos == 0){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[0], copyOfForm[1]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[0], copyOfForm2[3]);
			toReturn.push_back(Puzzle8State(copyOfForm2));
		}
		else if(zeroPos == 1){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[1], copyOfForm[0]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[1], copyOfForm2[2]);
			toReturn.push_back(Puzzle8State(copyOfForm2));

			std::string copyOfForm3 = this->form;
			std::swap(copyOfForm3[1], copyOfForm3[4]);
			toReturn.push_back(Puzzle8State(copyOfForm3));
		}
		else if(zeroPos == 2){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[2], copyOfForm[1]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[2], copyOfForm2[5]);
			toReturn.push_back(Puzzle8State(copyOfForm2));
		}
		else if(zeroPos == 3){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[3], copyOfForm[0]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[3], copyOfForm2[4]);
			toReturn.push_back(Puzzle8State(copyOfForm2));

			std::string copyOfForm3 = this->form;
			std::swap(copyOfForm3[3], copyOfForm3[6]);
			toReturn.push_back(Puzzle8State(copyOfForm3));
		}
		else if(zeroPos == 4){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[4], copyOfForm[3]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[4], copyOfForm2[5]);
			toReturn.push_back(Puzzle8State(copyOfForm2));

			std::string copyOfForm3 = this->form;
			std::swap(copyOfForm3[4], copyOfForm3[1]);
			toReturn.push_back(Puzzle8State(copyOfForm3));

			std::string copyOfForm4 = this->form;
			std::swap(copyOfForm4[4], copyOfForm4[7]);
			toReturn.push_back(Puzzle8State(copyOfForm4));
		}
		else if(zeroPos == 5){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[5], copyOfForm[2]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[5], copyOfForm2[4]);
			toReturn.push_back(Puzzle8State(copyOfForm2));

			std::string copyOfForm3 = this->form;
			std::swap(copyOfForm3[5], copyOfForm3[8]);
			toReturn.push_back(Puzzle8State(copyOfForm3));
		}
		else if(zeroPos == 6){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[6], copyOfForm[3]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[6], copyOfForm2[7]);
			toReturn.push_back(Puzzle8State(copyOfForm2));
		}
		else if(zeroPos == 7){
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[7], copyOfForm[4]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[7], copyOfForm2[6]);
			toReturn.push_back(Puzzle8State(copyOfForm2));

			std::string copyOfForm3 = this->form;
			std::swap(copyOfForm3[7], copyOfForm3[8]);
			toReturn.push_back(Puzzle8State(copyOfForm3));
		}
		else{
			std::string copyOfForm = this->form;
			std::swap(copyOfForm[8], copyOfForm[7]);
			toReturn.push_back(Puzzle8State(copyOfForm));

			std::string copyOfForm2 = this->form;
			std::swap(copyOfForm2[8], copyOfForm2[5]);
			toReturn.push_back(Puzzle8State(copyOfForm2));
		}
		return toReturn;
	}

	int heuristic(){
		int toReturn = 0;
		for(int i=0; i<3; ++i){
			for(int j=0; j<3; ++j){
				if((this->tiles[i][j] - '0') != (i*3+j) && this->tiles[i][j] != '0'){
					if(this->tiles[i][j] - '0' == 1){
						toReturn += (abs(i) + abs(j-1));
					}
					else if(this->tiles[i][j] - '0' == 2){
						toReturn += (abs(i) + abs(j-2));
					}
					else if(this->tiles[i][j] - '0' == 3){
						toReturn += (abs(i-1) + abs(j));
					}
					else if(this->tiles[i][j] - '0' == 4){
						toReturn += (abs(i-1) + abs(j-1));
					}
					else if(this->tiles[i][j] - '0' == 5){
						toReturn += (abs(i-1) + abs(j-2));
					}
					else if(this->tiles[i][j] - '0' == 6){
						toReturn += (abs(i-2) + abs(j));
					}
					else if(this->tiles[i][j] - '0' == 7){
						toReturn += (abs(i-2) + abs(j-1));
					}
					else{
						toReturn += (abs(i-2) + abs(j-2));
					}
				}
			}
		}
		return toReturn;
	}

	// Key generated as an integer for the hash function in Puzzle8StateManager.
	int GetKey() {
		int key = 0;
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				key = key*10 + int(tiles[r][c] - '0');
		return key;
	}

	// Return the linearized form as a string. (You don't need to use this.)
	std::string GetLinearizedForm () {
		std::string s = "";
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				s += tiles[r][c];
		return s;
	}

	// Print the puzzle in a 3x3 layout. (You don't need to use this.)
	void Print(std::ostream & out = std::cout) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				out<<tiles[r][c]<<" ";
			}
			out<<std::endl;
		}
		//out<<GetKey()<<std::endl;
	}
	char tiles[3][3];

private:

	// tiles[r][c] is the tile (or blank) at row r (0-2) and column c (0-2)
	// 0th row is the top row, and 0th column is the leftmost column.
	
	
};

#endif
