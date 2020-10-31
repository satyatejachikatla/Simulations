#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

inline int mod(int value,int m) {
	int modulo = value % m;
	if (modulo < 0) modulo += m;

	return modulo;
}


class ElementaryCells {

private:

	std::vector<bool> rule;
	std::vector<bool> *cells;
	std::vector<bool> *cells_temp;

	bool wrap_ends;

	bool UpdateRule(int i) {
		int index= AtCellsId(i-1) << 2 | AtCellsId(i) << 1 |  AtCellsId(i+1);
		return rule[index];
	}

public:
	ElementaryCells() = delete;
	ElementaryCells(std::vector<bool>& rule,int ncells,bool wrap_ends) {

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
	~ElementaryCells() {
		delete cells;
		delete cells_temp;
	}

	bool AtCellsId(int i) {
		if ( wrap_ends ) {
			return (*cells)[mod(i,cells->size())];
		} else {
			if ( 0 < i && i < cells->size() ) return (*cells)[i];
			return false;
		}
	}

	void Step(int count,std::vector<bool>& ret) {
		std::vector<bool> *t;

		for(int c=0;c<count;c++){
			for(int i=0;i<cells->size();i++) (*cells_temp)[i] = UpdateRule(i);
			t = cells_temp;
			cells_temp = cells;
			cells = t;
		}
		for(int i=0;i<cells->size();i++) ret[i] = (*cells)[i];
	}
};


void display(std::vector<bool> buff) {
	for(int i=0;i<buff.size();i++)
		std::cout << buff[i] << " ";
	std::cout << endl;
}

int main (int argc,char** argv) {

	int size = 50;
	std::vector<bool> rule{0,1,1,1,1,0,0,0}; // Rule 30

	ElementaryCells Wolfman(rule,size,true);
	std::vector<bool> buff(size);

	while(true) {
		Wolfman.Step(1,buff);
		display(buff);
		usleep(10000);
	}
	return 0;
}