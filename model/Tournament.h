#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <vector>

#include "Round.h"
#include "Player.h"
#include "Build.h"

using namespace std;

class Tournament {
	private:
		Round* current_round;
		int rounds_played;
		int card_count;
		vector<Player*> game_players;
		vector<Card*> parse_cards_from_file(string line);
		void print_cards(vector<Card*> card_list);
		vector<string> parse_builds(string line);
		vector<Build*> get_build_objects(vector<string> build_strings, string line, vector<Card*> player_hand, vector<Card*> computer_hand);
		int get_build_str_val(string build_str);
		vector<vector<Card*>> get_build_cards(string build_str);
		vector<Card*> get_table_cards(string line);
		vector<Card*> modify_table_cards(vector<Card*> table_cards_list, vector<Build*> current_builds);
		void compute_player_scores();
		vector<Card*> get_deck_list();

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
		void start_round(bool first_round);
		void end_round();
		bool coin_toss();
};

#endif
