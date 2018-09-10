#include <iostream>

#include "Tournament.h"
#include "Round.h"

using namespace std;

Tournament::Tournament() {
	Round r1(0);
	this->current_round = &r1;
}

void Tournament::print_welcome() {
	cout << "Welcome to Casino C++! Round " << current_round->get_round_num() << " is about to begin!" << endl;
}


