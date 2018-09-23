#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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
	bool possible_move_selected = false;
	
	while (!possible_move_selected) {
		pair<Card*, char> move_pair = game_players[0]->play();
		if (move_pair.second == 't') {
			trail(move_pair.first, game_players[0]);
			possible_move_selected = true;
		} else if (move_pair.second == 'c') {
			possible_move_selected = capture(move_pair.first, game_players[0]);
		}
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
	Move* game_move = generate_capture_move(card_played, game_player);
	vector<Card*> capturable_cards = game_move->get_capturable_cards();
	vector<Card*> pile_additions;	
	
	if (capturable_cards.empty()) {
		cout << "No cards on the table can be captured with this card." << endl;
		return false;
	}
	
	cout << "Would you like to capture? (y/n)" << endl;
	for (int i = 0; i < capturable_cards.size(); i++) {
		cout << "(" << i+1 << ") " << capturable_cards[i]->get_card_string() << " ";
	}
	cout << endl;
	char will_capture;
	while(will_capture != 'y' && will_capture != 'n') {
		cin >> will_capture;
		if (will_capture != 'y' && will_capture != 'n') {
			cout << "Input not recognized. Try again." << endl;
		} 
	}
	if (will_capture == 'n')
		return false;
	
	game_player->discard(card_played);
	this->game_table->remove_cards(capturable_cards);	

	pile_additions.push_back(card_played);
	for (int i = 0; i < capturable_cards.size(); i++) {
		pile_additions.push_back(capturable_cards[i]);
	}
	game_player->add_to_pile(pile_additions);
	this->game_view->update_view(this->game_players, this->game_table);
	return true;			
}


Move* Round::generate_capture_move(Card* card_played, Player* game_player) {
	// Get value of card played
	// Check values of cards on board, if matches exist add to vector
	// (Eventually - check list of build values on board)
	// Check all possible sets of cards, if value of sets match card value, add to 2d vector
	// Return Move obj generated with (card_played, capturable_cards, capturable_sets) 
	int played_value = card_played->get_value();
	vector<Card*> avail_cards = this->game_table->get_table_cards();
	vector<Card*> capturable_cards;
	// Find exact value matches
	for (int i = 0; i < avail_cards.size(); i++) {
		if (avail_cards[i]->get_value() == played_value) {
			capturable_cards.push_back(avail_cards[i]);
		}
	}	
	// Iterate through avail_cards vector
	// Take element i and  
	vector<Card*> sub_set;
	vector<vector<Card*>> avail_sets;
	vector<Card*> empty;
	avail_sets.push_back(empty);	
	for (int i = 0; i < avail_cards.size(); i++) {
		vector<vector<Card*>> temp_sets = avail_sets;
		
		for (int j = 0; j < temp_sets.size(); j++)
			temp_sets[j].push_back(avail_cards[i]);
		for (int j = 0; j < temp_sets.size(); j++) 
			avail_sets.push_back(temp_sets[j]);
	}
	for (int i = 0; i < avail_sets.size(); i++) {
		if (get_set_value(avail_sets[i]) == played_value && avail_sets[i].size() > 1) {
			for (int j = 0; j < avail_sets[i].size(); j++) {
				cout << avail_sets[i][j]->get_card_string() << " ";	
			}
			cout << endl;
		}
	}	
	return new Move(card_played, capturable_cards, vector<vector<Card*>>());		
}

int Round::get_set_value(vector<Card*> card_set) {
	int value_sum = 0;
	for (int i = 0; i < card_set.size(); i++) {
		value_sum += card_set[i]->get_value();
	}
	return value_sum;
}
