#include <iostream>

#include "Tournament.h"
#include "Round.h"

using namespace std;

Tournament::Tournament() {
	this->rounds_played = 0;
}

void Tournament::print_welcome() {
	cout << "Welcome to Casino C++! Round " << this->current_round->get_round_num() << " is about to begin!" << endl;
}

void Tournament::start_round() {
	this->rounds_played += 1;
	Round game_round(rounds_played);
	this->current_round = &game_round;	
	print_welcome();
}


