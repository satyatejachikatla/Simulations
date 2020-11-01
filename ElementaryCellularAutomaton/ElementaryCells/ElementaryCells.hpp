#ifndef SIMULATION_ELEMENTARY_CELLULAR_AUTOMATON_ELEMENTARY_CELLS_
#define SIMULATION_ELEMENTARY_CELLULAR_AUTOMATON_ELEMENTARY_CELLS_

#include <vector>

class ElementaryCells {

private:

	std::vector<bool> rule;
	std::vector<bool> *cells;
	std::vector<bool> *cells_temp;

	bool wrap_ends;

	bool UpdateRule(int i);

public:
	ElementaryCells() = delete;
	ElementaryCells(std::vector<bool>& rule,int ncells,bool wrap_ends);
	~ElementaryCells();

	bool AtCellsId(int i);

	void Step(int count,std::vector<bool>& ret);
};

#endif /*SIMULATION_ELEMENTARY_CELLULAR_AUTOMATON_ELEMENTARY_CELLS_*/