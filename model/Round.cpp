#include <iostream>
#include <string>
#include <vector>

#include "Round.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include "Card.h"

using namespace std;

Round::Round(int a_round_num, vector<Player*> a_game_players) {
	this->round_num = a_round_num;
	this->game_deck = new Deck;
	this->game_players = a_game_players;
}

int Round::get_round_num() {
	return this->round_num;
}

void Round::start_game() {
	deal_hands(game_players);

	game_players[0]->play();
	game_players[1]->play();		
}

void Round::deal_hands(vector<Player*> game_players) {
	for (int i = 0; i < 4; i++) {
		game_players[0]->add_to_hand(game_deck->draw_card());
		game_players[1]->add_to_hand(game_deck->draw_card());
	} 
}

