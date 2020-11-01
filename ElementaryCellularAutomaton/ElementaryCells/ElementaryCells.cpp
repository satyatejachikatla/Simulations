#include <vector>
#include <ElementaryCells/ElementaryCells.hpp>

inline int mod(int value,int m) {
	int modulo = value % m;
	if (modulo < 0) modulo += m;

	return modulo;
}

bool ElementaryCells::UpdateRule(int i) {
	int index= AtCellsId(i-1) << 2 | AtCellsId(i) << 1 |  AtCellsId(i+1);
	return rule[index];
}

ElementaryCells::ElementaryCells(std::vector<bool>& rule,int ncells,bool wrap_ends) {

	//Init Rule as empty
	this->rule.resize(8,0);

	for(int i=0;i<rule.size();i++) this->rule[i] = rule[i];

	cells = new std::vector<bool>();
	cells_temp = new std::vector<bool>();

	cells->resize(ncells,0);
	cells_temp->resize(ncells,0);

	this->wrap_ends = wrap_ends;

	// Init the middle cell to be true
	(*cells)[cells->size()/2] = true;
}
ElementaryCells::~ElementaryCells() {
	delete cells;
	delete cells_temp;
}

bool ElementaryCells::AtCellsId(int i) {
	if ( wrap_ends ) {
		return (*cells)[mod(i,cells->size())];
	} else {
		if ( 0 < i && i < cells->size() ) return (*cells)[i];
		return false;
	}
}

void ElementaryCells::Step(int count,std::vector<bool>& ret) {
	std::vector<bool> *t;

	for(int c=0;c<count;c++){
		for(int i=0;i<cells->size();i++) (*cells_temp)[i] = UpdateRule(i);
		t = cells_temp;
		cells_temp = cells;
		cells = t;
	}
	for(int i=0;i<cells->size();i++) ret[i] = (*cells)[i];
}
