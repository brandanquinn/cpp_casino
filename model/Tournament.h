#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Round.h"

using namespace std;

class Tournament {
	private:
		void print_welcome();
		Round* current_round;
		int rounds_played;
	public:
		Tournament();
		void start_round();
};

#endif
