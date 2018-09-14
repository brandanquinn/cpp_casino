#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <vector>

#include "Round.h"
#include "Player.h"

using namespace std;

class Tournament {
	private:
		void print_welcome();
		Round* current_round;
		int rounds_played;
		vector<Player*> game_players;
	public:
		Tournament();
		void start_round();
		void end_round();
};

#endif
