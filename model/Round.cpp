#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "Round.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include "Card.h"
#include "Table.h"
#include "Move.h"

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
	this->game_view->print_welcome(this->round_num);
	this->game_view->update_view(this->game_players, this->game_table);	
	// Player plays, returns pair for move selected.
	// Create Round function to update model using info from pair.
	// Update game_view after each play
	pair<Card*, char> move_pair = game_players[0]->play();
	if (move_pair.second == 't') {
		trail(move_pair.first, game_players[0]);
	} else if (move_pair.second == 'c') {
		capture(move_pair.first, game_players[0]);
	}
	
}

void Round::deal_hands(vector<Player*> game_players) {
	for (int i = 0; i < 4; i++) {
		game_players[0]->add_to_hand(game_deck->draw_card());
	}
	for (int i = 0; i < 4; i++) {
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

void Round::trail(Card* card_played, Player* game_player) {
	// Remove card from players hand
	// Add card to table_cards
	// Update view
	game_player->discard(card_played);
	this->game_table->add_to_table_cards(card_played);
	this->game_view->update_view(this->game_players, this->game_table);
}

bool Round::capture(Card* card_played, Player* game_player) {
	// Check to see if any capture can be made
	// If no capture can be made at the time, return false.
	// Else list capture options.
	// Remove card from players hand, add to vector
	// Remove card(s) captured from table, add to vector
	// Add vector to pile
	// Update view
	cout << "Capture using: " << card_played->get_card_string() << endl;	
}

Move* Round::get_capturable_cards(Card* card_played, Player* game_player) {
	// Get value of card played
	// Check values of cards on board, if matches exist add to vector
	// (Eventually - check list of build values on board)
	// Check all possible sets of cards, if value of sets match card value, add to 2d vector
	// Return Move obj generated with (card_played, capturable_cards, capturable_sets) 
}
