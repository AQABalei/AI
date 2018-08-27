#ifndef PUZZLE_8_SOLVER_H
#define PUZZLE_8_SOLVER_H

#include <string>
#include "Puzzle8StateManager.h"
#include "Puzzle8PQ.h"

void WeightedAStar(std::string puzzle, double w, int & cost, int & expansions);

#endif
