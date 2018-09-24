#include <iostream>
#include <vector>
#include <random>

#include "Tournament.h"
#include "Round.h"
#include "Player.h"
#include "../view/Display.h"

using namespace std;

Tournament::Tournament() {
	this->rounds_played = 0;
	this->game_players.push_back(new Human());
	this->game_players.push_back(new Human());
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



