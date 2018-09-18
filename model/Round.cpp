#include <iostream>
#include <string>
#include <vector>

#include "Round.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include "Card.h"
#include "Table.h"

using namespace std;

Round::Round(int a_round_num, vector<Player*> a_game_players) {
	this->round_num = a_round_num;
	this->game_deck = new Deck;
	this->game_table = new Table;
	this->game_players = a_game_players;
	this->game_view = new Display;
}

int Round::get_round_num() {
	return this->round_num;
}

void Round::start_game() {
	deal_hands(game_players);
	deal_to_table(game_table);
	this->game_view->update_view(this->game_players, this->game_table, this->round_num);	
	// Player plays, returns Move object
	// Create Round function to update model using Move object info
	// Update game_view after each play
}

void Round::deal_hands(vector<Player*> game_players) {
	for (int i = 0; i < 4; i++) {
		game_players[0]->add_to_hand(game_deck->draw_card());
		game_players[1]->add_to_hand(game_deck->draw_card());
	} 
}

void Round::deal_to_table(Table* game_table) {
	for (int i = 0; i < 4; i++) {
		this->game_table->add_to_table_cards(game_deck->draw_card());
	}
}

Table* Round::get_game_table() {
	return this->game_table;
}
