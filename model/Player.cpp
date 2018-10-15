#include <iostream>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "Card.h"
#include "Move.h"
#include "Build.h"

using namespace std;

Player::Player() {
	set_score(0);	
	set_is_playing(false);
}

Table* Player::get_game_table() {
	return this->game_table;
}

void Player::set_game_table(Table* a_game_table) {
	this->game_table = a_game_table;
}

int Player::get_score() {
	return this->score;
}

void Player::set_score(int a_score) {
	this->score = a_score;
}

void Player::add_to_hand(Card* new_card) {
	hand.push_back(new_card);
}

void Player::add_to_pile(vector<Card*> captured_cards) {
	for (int i = 0; i < captured_cards.size(); i++) {
		this->pile.push_back(captured_cards[i]);
	}	
}

vector<Card*> Player::get_pile() {
	return this->pile;
}

void Player::discard(Card* removed_card) {
	this->hand.erase(remove(hand.begin(), hand.end(), removed_card), hand.end());
}

vector<Card*> Player::get_hand() {
	return this->hand;
}

void Player::clear_hand() {
	this->hand.clear();
}

bool Player::hand_is_empty() {
	return this->hand.empty();
}
	
void Player::set_is_playing(bool a_is_playing) {
	this->is_playing = a_is_playing;
}

bool Player::get_is_playing() {
	return this->is_playing;
}

void Player::set_hand(vector<Card*> a_hand) {
	this->hand = a_hand;
}
		
		
void Player::set_pile(vector<Card*> a_pile) {
	this->pile = a_pile;
}

string Player::get_hand_string() {
	string hand_str = "";
	for (int i = 0; i < hand.size(); i++) {
		hand_str += hand[i]->get_card_string() + " ";
	}

	return hand_str;
}

string Player::get_pile_string() {
	string pile_str = "";
	for (int i = 0; i < pile.size(); i++) {
		pile_str += pile[i]->get_card_string() + " ";
	}

	return pile_str;
}

void Player::set_player_string(string a_player_string) {
	this->player_string = a_player_string;
}
		
string Player::get_player_string() {
	return this->player_string;
}

pair<Card*, char> Player::get_help() {
	// AI Priority List
	// 1. Evaluate best possible capture set for each card in hand. Make the move that captures the most cards.
	// 2. If you control a build, try to extend it.
	// 3. Make the first build you can find, if possible. Check possibilities from highest value -> lowest.
	// 4. Trail the card with the lowest value.
	pair<Card*, char> move_pair;

	vector<int> capture_values;
	for (int i = 0; i < hand.size(); i++) {
		capture_values.push_back(assess_capture(hand[i]));
	}

	int max_value = 0;
	int max_index = 0;
	for (int i = 0; i < capture_values.size(); i++) {
		if (capture_values[i] > max_value) {
			max_value = capture_values[i];
			max_index = i;
		}
	}

	move_pair.first = hand[max_index];
	move_pair.second = 'c';

	

	return move_pair;
}

int Player::assess_capture(Card* card_played) {
	// Check to see if any capture can be made
	// If no capture can be made at the time, return false.
	// Else list capture options.
	// Remove card from players hand, add to vector
	// Remove card(s) captured from table, add to vector
	// Add vector to pile
	// Update view

	Move* game_move = generate_capture_move(card_played);
	vector<Card*> capturable_cards = game_move->get_capturable_cards();
	vector<Card*> pile_additions;	
	vector<vector<Card*>> capturable_sets = game_move->get_capturable_sets();
	vector<Build*> capturable_builds = game_move->get_capturable_builds();
	vector<vector<Card*>> selected_sets;

	if (capturable_cards.empty() && capturable_sets.empty() && capturable_builds.empty()) {
		return 0;
	}

	if (!capturable_sets.empty()) {
		// Give selection of sets to capture as well:
		int max_set_size = 0;
		int best_set_index = 0;
		int set_selection = -1;
		while (!capturable_sets.empty()) {
			for (int i = 0; i < capturable_sets.size(); i++) {
				if (capturable_sets[i].size() > max_set_size) { 
					max_set_size = capturable_sets[i].size();
					best_set_index = i;
				}
			}
			selected_sets.push_back(capturable_sets[best_set_index]);	
			// remove cards in selected_sets from capturable_sets
			remove_selected_set(capturable_sets, capturable_sets[best_set_index]);	
		} 	
	}


	pile_additions.push_back(card_played);
	for (int i = 0; i < capturable_cards.size(); i++) {
		pile_additions.push_back(capturable_cards[i]);
	}
	for (int i = 0; i < selected_sets.size(); i++) {
		for (int j = 0; j < selected_sets[i].size(); j++) {
			pile_additions.push_back(selected_sets[i][j]);
		}
	}
	for (int i = 0; i < capturable_builds.size(); i++) {
		capturable_builds[i]->get_sum_card()->set_locked_to_build(false);
		vector<vector<Card*>> temp_build_cards = capturable_builds[i]->get_total_build_cards();
		for (int j = 0; j < temp_build_cards.size(); j++) {
			for (int k = 0; k < temp_build_cards[j].size(); k++) {
				pile_additions.push_back(temp_build_cards[j][k]);
			}
		}
	}

	return pile_additions.size();
	// game_player->add_to_pile(pile_additions);
	// return true;			
}

Move* Player::generate_capture_move(Card* card_played) {
	// Get value of card played
	// Check values of cards on board, if matches exist add to vector
	// (Eventually - check list of build values on board)
	// Check all possible sets of cards, if value of sets match card value, add to 2d vector
	// Return Move obj generated with (card_played, capturable_cards, capturable_sets)
	vector<Build*> capturable_builds; 
	
	vector<Build*> current_builds = this->game_table->get_current_builds();

	for (int i = 0; i < current_builds.size(); i++) {
		if (current_builds[i]->get_sum_card()->get_card_string() == card_played->get_card_string() || 
		(current_builds[i]->get_build_owner() != get_player_string() && current_builds[i]->get_sum_card()->get_value() == card_played->get_value()) ) {
			capturable_builds.push_back(current_builds[i]);	
		}
	}

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
	return new Move(card_played, capturable_cards, capturable_sets, capturable_builds);		
}

int Player::get_set_value(vector<Card*> card_set) {
	int value_sum = 0;
	for (int i = 0; i < card_set.size(); i++) {
		value_sum += card_set[i]->get_value();
	}
	return value_sum;
}

void Player::remove_selected_set(vector<vector<Card*>> &total_sets, vector<Card*> selected_set) {
	// if any cards within the selected_set exist in total_subset; remove subset
	
	for (int i = 0; i < selected_set.size(); i++) {
		for (int j = 0; j < total_sets.size(); j++) {
			if (count(total_sets[j].begin(), total_sets[j].end(), selected_set[i]))
				total_sets.erase(total_sets.begin() + j);	
		}
	}
}