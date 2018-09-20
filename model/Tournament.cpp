#include <iostream>
#include <vector>

#include "Tournament.h"
#include "Round.h"
#include "Player.h"
#include "../view/Display.h"

using namespace std;

Tournament::Tournament() {
	this->rounds_played = 0;
	this->game_players.push_back(new Human());
	this->game_players.push_back(new Computer());
}

void Tournament::start_round() {
	this->rounds_played += 1;
	Round game_round(rounds_played, game_players);
	this->current_round = &game_round;	
	this->current_round->start_game();
}

void Tournament::end_round() {
	cout << "Round has ended. Player 1 scored: " << game_players[0]->get_score() << ". Player 2 scored: " << game_players[1]->get_score() << endl; 
	this->game_players[0]->clear_hand();
	this->game_players[1]->clear_hand();
	this->current_round->get_game_table()->clear_table_cards();
}



