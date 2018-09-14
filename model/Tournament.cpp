#include <iostream>
#include <vector>

#include "Tournament.h"
#include "Round.h"
#include "Player.h"

using namespace std;

Tournament::Tournament() {
	this->rounds_played = 0;
	this->game_players.push_back(new Human());
	this->game_players.push_back(new Computer());
}

void Tournament::print_welcome() {
	cout << "Welcome to Casino C++! Round " << this->current_round->get_round_num() << " is about to begin!" << endl;
}

void Tournament::start_round() {
	this->rounds_played += 1;
	Round game_round(rounds_played, game_players);
	this->current_round = &game_round;	
	print_welcome();
	this->current_round->start_game();
}

void Tournament::end_round() {
	cout << "Round has ended. Player 1 scored: " << game_players[0]->get_score() << ". Player 2 scored: " << game_players[1]->get_score() << endl; 
}


