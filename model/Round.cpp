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

void Round::start_game(bool human_is_first) {
	deal_hands(game_players);
	deal_to_table(game_table);
		
	// Player plays, returns pair for move selected.
	// Create Round function to update model using info from pair.
	// Update game_view after each play
	bool possible_move_selected = false;
	Player* player_one;
	Player* player_two;
	if (human_is_first) { 
		player_one = game_players[0];
		player_two = game_players[1];
	}
	else { 
		player_one = game_players[1];	
		player_two = game_players[0];
	}
	
	player_one->set_is_playing(true);

	cout << "Human playing: " << game_players[0]->get_is_playing() << endl;
	cout << "Computer playing: " << game_players[1]->get_is_playing() << endl;
	this->game_view->print_welcome(this->round_num);
	this->game_view->update_view(this->game_players, this->game_table);
	
	while (!this->game_deck->is_empty()) {	
		if (player_one->hand_is_empty() && player_two->hand_is_empty()) { 
			deal_hands(game_players);
			this->game_view->update_view(this->game_players, this->game_table);
		}
		while (!possible_move_selected) {
			pair<Card*, char> move_pair = player_one->play();
			if (move_pair.second == 't') {
				trail(move_pair.first, player_one);
				possible_move_selected = true;
			} else if (move_pair.second == 'c') {
				possible_move_selected = capture(move_pair.first, player_one);
			} else {
				possible_move_selected = build(move_pair.first, player_one);
			}
		}
		player_one->set_is_playing(false);
		player_two->set_is_playing(true);
		this->game_view->update_view(this->game_players, this->game_table);
		possible_move_selected = false;
		while (!possible_move_selected) {
			pair<Card*, char> move_pair = player_two->play();
			if (move_pair.second == 't') {
				trail(move_pair.first, player_two);
				possible_move_selected = true;
			} else if (move_pair.second == 'c') {
				possible_move_selected = capture(move_pair.first, player_two);
			} else {
				possible_move_selected = build(move_pair.first, player_two);
			}
		}
		player_one->set_is_playing(true);
		player_two->set_is_playing(false);
		this->game_view->update_view(this->game_players, this->game_table);
		possible_move_selected = false;	
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
	game_player->set_is_playing(false);
	
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
	vector<vector<Card*>> capturable_sets = game_move->get_capturable_sets();
	vector<vector<Card*>> selected_sets;

	if (capturable_cards.empty() && capturable_sets.empty()) {
		cout << "No cards on the table can be captured with this card." << endl;
		return false;
	}

	if (!capturable_cards.empty()) {	
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
	}
	if (!capturable_sets.empty()) {
		// Give selection of sets to capture as well:
		for (int i = 0; i < capturable_sets.size(); i++) {
			cout << "Subset (" << i+1 << ") ";
			for (int j = 0; j < capturable_sets[i].size(); j++) {
				cout << capturable_sets[i][j]->get_card_string() << " ";
			}
			cout << endl;
		}
		int set_selection = -1;
			while (set_selection != 0) {
			cout << "Select which subsets you'd like to capture. Input '0' when you are finished." << endl;
			cout << "Input: ";
			cin >> set_selection;
			if (set_selection == 0) break;
			if (set_selection <= 0 || set_selection > capturable_sets.size()) {
				cout << "Input not recognized. Try again." << endl;
			} else {
				selected_sets.push_back(capturable_sets[set_selection-1]);	
			}	
		} 	
	}

		
	game_player->discard(card_played);
	this->game_table->remove_cards(capturable_cards);	
	this->game_table->remove_sets(selected_sets);	

	pile_additions.push_back(card_played);
	for (int i = 0; i < capturable_cards.size(); i++) {
		pile_additions.push_back(capturable_cards[i]);
	}
	for (int i = 0; i < selected_sets.size(); i++) {
		for (int j = 0; j < selected_sets[i].size(); j++) {
			pile_additions.push_back(selected_sets[i][j]);
		}
	}
	game_player->add_to_pile(pile_additions);
	return true;			
}

bool Round::build(Card* card_selected, Player* game_player) {
	// Get value of card selected
	// Have player select card to play into the build.
	int selected_value = card_selected->get_value();
	vector<Card*> player_hand = game_player->get_hand();
	int card_num = 0;
	while (card_num < 1 || card_num > player_hand.size()) {
		cout << "Which card would you like to add to the build? (Enter # of card position, leftmost being 1): ";
		cin >> card_num;
		if (card_num < 1 || card_num > player_hand.size())
			cout << "Invalid number input. Try again." << endl;
	}	
	Card* card_played = player_hand[card_num-1];
	// If that card has value >= locked card: return false
	if (card_played->get_value() >= selected_value) {
		cout << "Card selected cannot be used in this build." << endl;
		return false;
	}
	vector<Card*> table_cards = this->game_table->get_table_cards();
	vector<Card*> filtered_cards = table_cards;
	int played_value = card_played->get_value();
	// Provide options to build with on table.
	card_num = 0;
	bool build_created = false;
	vector<Card*> build_cards;
	build_cards.push_back(card_played);
	while (!build_created) {
		// Filter available cards to remove all cards with value + played_value > locked card val
		filtered_cards = filter_build_options(filtered_cards, played_value, selected_value);
		if (filtered_cards.empty()) {
			cout << "No cards can be used for this build." << endl;
			return false;
		}
		while (card_num < 1 || card_num > filtered_cards.size()) {
			cout << "Select cards to build with, enter '0' when you are done." << endl;
			for (int i = 0; i < filtered_cards.size(); i++) {
				cout << "(" << i+1 << ") " << filtered_cards[i]->get_card_string() << endl;	
			}
			cin >> card_num;
			if (card_num < 1 || card_num > filtered_cards.size()) {
				cout << "Invalid number input. Try again" << endl;	
			} 
		}
		// At this point we have a locked card for the build to sum to | card_selected
		// A card selected to play into a build (1) | card_played
		// And a card on the board to build with (2) | build_card
		// If (1) + (2) = locked card value, ask user if they'd like to complete build.
		Card* build_card = filtered_cards[card_num-1];
		build_cards.push_back(build_card);
		
		if (played_value + build_card->get_value() == selected_value) {
			cout << "Would you like to create the build of: [" << card_played->get_card_string() << " " << build_card->get_card_string() << "] (y/n)?";
			char user_input;
			while (user_input != 'y' && user_input != 'n') {
				cin >> user_input;
				if (user_input != 'y' && user_input != 'n') {
					cout << "Input not recognized. Try again." << endl;
				}
			}
			if (user_input == 'y') {
				// create build and update model
				Build* b1 = new Build(build_cards, selected_value, card_selected);
				this->game_table->add_build(b1);
				game_player->discard(card_played);
				this->game_table->add_to_table_cards(card_played);
				return true;
			} else {
				return false;
			}			 
		} 
		// Need to build with more cards on the table.
		played_value = get_set_value(build_cards);		
		card_num = 0;
		cout << "Played val: " << played_value << endl;
	}
	
}

vector<Card*> Round::filter_build_options(vector<Card*> available_cards, int played_value, int build_sum) {
	vector<Card*> filtered_options;
	// Iterate through avail_cards
	// If avail_card val + played_val < build_sum
	// Add avail_card to filtered vector
	// Return filtered vector
	for (int i = 0; i < available_cards.size(); i++) {
		if (available_cards[i]->get_value() + played_value <= build_sum)
			filtered_options.push_back(available_cards[i]); 
	}
	return filtered_options;
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
	vector<vector<Card*>> capturable_sets;
	for (int i = 0; i < avail_sets.size(); i++) {
		if (get_set_value(avail_sets[i]) == played_value && avail_sets[i].size() > 1) {
			capturable_sets.push_back(avail_sets[i]);	
		}
	}	
	return new Move(card_played, capturable_cards, capturable_sets);		
}

int Round::get_set_value(vector<Card*> card_set) {
	int value_sum = 0;
	for (int i = 0; i < card_set.size(); i++) {
		value_sum += card_set[i]->get_value();
	}
	return value_sum;
}
