#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Round.h"

using namespace std;

class Tournament {
	private:
		Round* current_round;
		int rounds_played;
	public:
		Tournament();
		void print_welcome();
		void start_round();
};

#endif
