#include <iostream>

#include "Round.h"

using namespace std;

Round::Round(int a_round_num) {
	this->round_num = a_round_num;
}

int Round::get_round_num() {
	return this->round_num;
}
