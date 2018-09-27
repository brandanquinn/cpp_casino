#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <fstream>
#include <string>
#include <sstream>

#include "Tournament.h"
#include "Round.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Build.h"
#include "../view/Display.h"

using namespace std;

Tournament::Tournament() {
	this->rounds_played = 0;
	this->game_players.push_back(new Human());
	this->game_players.push_back(new Human());
}

void Tournament::show_start_screen() {
	// Give the option to Start New game or Load saved game
	cout << "Welcome to CPP Casino by BQ!" << endl;
	cout << "(1) Start New Game" << endl;
	cout << "(2) Load Saved Game" << endl;
	int user_input;

	while (user_input != 1 && user_input != 2) {
		cout << "Select a menu option from above: ";
		cin >> user_input;
		if (user_input != 1 && user_input != 2)
			cout << "Invalid option. Try again." << endl;
	}

	if (user_input == 1)
		start_round();
	else
		if(!load_saved_game())
			cout << "Save file does not exist." << endl; 
}

bool Tournament::load_saved_game() {
	const char *file_name = "serialization/save.txt";
	ifstream save_file(file_name);
	if (!save_file.good()) return false;
	int current_round_num, computer_score, player_score;
	vector<Card*> player_hand, player_pile, computer_hand, computer_pile;
	vector<vector<Card*>> total_table_cards;
	vector<Build*> current_builds;
	queue<Card*> current_deck;
	bool human_next;
	
	

	string line;
	int line_num = 0;	
	if (save_file.is_open()) {
		while (getline(save_file, line)) {
			// current_round
			switch (line_num) {
				case 0: 
					current_round_num = stoi(line.substr(line.find(':') + 1));
					break;
				case 3:
					computer_score = stoi(line.substr(line.find(':') + 1));
					break;
				case 4:
					string hand_str = line.substr(line.find(':') + 1);
					istringstream c_hand(hand_str);
					do {
						string card_str;
						c_hand >> card_str;
						computer_hand.push_back(new Card(card_str[0], card_str[1]));	
					} while (c_hand);	
					c_hand.clear();
					break;	
				case 5:
					string pile_str = line.substr(line.find(':') + 1);
					istringstream c_pile(pile_str);
					do {
						string card_str;
						c_pile >> pile_str;
						computer_pile.push_back(new Card(card_str[0], card_str[1]));
					} while (c_pile);
					c_pile.clear();
					break;
			}
			line_num++;
		}
		save_file.close();
	}	

	return true;
}

void Tournament::start_round() {
	this->rounds_played += 1;	
	Round game_round(rounds_played, game_players);
	this->current_round = &game_round;	
	this->current_round->start_game(coin_toss());
}

void Tournament::end_round() {
	cout << "Round has ended. Player 1 scored: " << game_players[0]->get_score() << ". Player 2 scored: " << game_players[1]->get_score() << endl; 
	this->game_players[0]->clear_hand();
	this->game_players[1]->clear_hand();
	this->current_round->get_game_table()->clear_table_cards();
}

bool Tournament::coin_toss() {
	char call_input;
	
	while (call_input != 'h' && call_input != 't') {
		cout << "We will flip a coin to determine who goes first!" << endl;
		cout << "Enter (h) for heads; or (t) for tails: ";
		cin >> call_input;
		if (call_input != 'h' && call_input != 't') {
			cout << "Invalid input. Try again!" << endl;
		}	
	}
	int call_to_int;
	if (call_input == 'h') call_to_int = 0;
	else call_to_int = 1;	

	int flip = (rand()%2);
	
	if (call_to_int == flip) { 
		cout << "Good call! You will go first." << endl;
		return true;
	}
	else {
		cout << "That was the wrong call. You will go second." << endl;
		return false;	
	}
}



