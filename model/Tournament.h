#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <vector>

#include "Round.h"
#include "Player.h"

using namespace std;

class Tournament {
	private:
		Round* current_round;
		int rounds_played;
		vector<Player*> game_players;
	public:
		Tournament();
		void show_start_screen();
		bool load_saved_game();
		// Before we start the round, we want to display a screen for the player
		// This screen will either give the option to Start a New Game or Load Saved Game
			// show_start_screen() ? 
		// If new game is selected, call start_round() as is.
		// Else, load_saved_game() is called
			// If serialization file exists, load in:
				// Current Round #
				// Computer player score, hand, and pile
				// Human player score, hand, and pile
				// Table with builds / loose cards
					// Build owner 
				// Current deck
				// Who is playing next    
		// load the serialization file from the serialization directory within /bin
		void start_round();
		void end_round();
		bool coin_toss();
};

#endif
