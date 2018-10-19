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

Table* Player::get_game_table() const {
	return this->game_table;
}

void Player::set_game_table(Table* a_game_table) {
	this->game_table = a_game_table;
}

int Player::get_score() const {
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

vector<Card*> Player::get_pile() const {
	return this->pile;
}

void Player::discard(Card* removed_card) {
	this->hand.erase(remove(hand.begin(), hand.end(), removed_card), hand.end());
}

vector<Card*> Player::get_hand() const {
	return this->hand;
}

void Player::clear_hand() {
	this->hand.clear();
}

void Player::clear_pile() {
	this->pile.clear();
}

bool Player::hand_is_empty() {
	return this->hand.empty();
}
	
void Player::set_is_playing(bool a_is_playing) {
	this->is_playing = a_is_playing;
}

bool Player::get_is_playing() const {
	return this->is_playing;
}

void Player::set_hand(vector<Card*> a_hand) {
	this->hand = a_hand;
}
		
		
void Player::set_pile(vector<Card*> a_pile) {
	this->pile = a_pile;
}

string Player::get_hand_string() const {
	string hand_str = "";
	for (int i = 0; i < hand.size(); i++) {
		hand_str += hand[i]->get_card_string() + " ";
	}

	return hand_str;
}

string Player::get_pile_string() const {
	string pile_str = "";
	for (int i = 0; i < pile.size(); i++) {
		pile_str += pile[i]->get_card_string() + " ";
	}

	return pile_str;
}

void Player::set_player_string(string a_player_string) {
	this->player_string = a_player_string;
}
		
string Player::get_player_string() const {
	return this->player_string;
}

pair<Card*, char> Player::get_help() {
	// AI Priority List
	// 1. Evaluate best possible capture set for each card in hand. Make the move that captures the most cards.
	// 2. If you control a build, try to extend it.
	// 3. Make the first build you can find, if possible. Check possibilities from highest value -> lowest.
	// 4. Trail the card with the lowest value.
	pair<Card*, char> move_pair;

	int max_build_index = 0, max_capture_index = 0;
	vector<int> build_values, capture_values;

	for (int i = 0; i < hand.size(); i++) {
		build_values.push_back(assess_builds(hand[i]));
	}
	max_build_index = get_max_score(build_values);

	if (build_values[max_build_index] == 0) {
		// capture
		for (int i = 0; i < hand.size(); i++) {
			capture_values.push_back(assess_capture(hand[i]));
		}
		max_capture_index = get_max_score(capture_values);

		if (capture_values[max_capture_index] == 0) {
			// trail
			int min_val = 15;
			int min_index = 0;
			for (int i = 0; i < hand.size(); i++) {
				if (hand[i]->get_value() < min_val) {
					min_val = hand[i]->get_value();
					min_index = i;
				}
			}
			move_pair.first = hand[min_index];
			move_pair.second = 't';
		} else {
			// capture
			move_pair.first = hand[max_capture_index];
			move_pair.second = 'c';
		}
	} else {
		// build
		move_pair.first = hand[max_build_index];
		move_pair.second = 'b';
	}

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

int Player::assess_builds(Card* card_selected) {
	// Get value of card selected
	// Have player select card to play into the build.
	int selected_value = card_selected->get_value();

	vector<int> possible_build_vals;

	if (card_selected->get_locked_to_build()) {
		for (int i = 0; i < hand.size(); i++) {
			possible_build_vals.push_back(create_builds(card_selected, hand[i], true));
		}
	} else {
		
		for (int i = 0; i < hand.size(); i++) {
			possible_build_vals.push_back(create_builds(card_selected, hand[i], false));
		}
	}

	return possible_build_vals[get_max_score(possible_build_vals)];
}

int Player::create_builds(Card* card_selected, Card* card_played, bool extending_build) {
	// If that card has value >= locked card: return false
	int selected_value = card_selected->get_value();
	if (card_played->get_value() >= selected_value) {
		return 0;
	}
	vector<Card*> table_cards = this->game_table->get_table_cards();
	vector<Card*> filtered_cards = table_cards;
	int played_value = card_played->get_value();
	// Provide options to build with on table.
	bool build_created = false;
	vector<Card*> build_cards;
	build_cards.push_back(card_played);
	while (!build_created) {
		// Filter available cards to remove all cards with value + played_value > locked card val
		filtered_cards = filter_build_options(filtered_cards, played_value, selected_value);
		if (filtered_cards.empty()) {
			return 0;
		}
		int best_card_selection;
		int min_value = 15;
		for (int i = 0; i < filtered_cards.size(); i++) {
			if (played_value + filtered_cards[i]->get_value() == selected_value) {
				best_card_selection = i;
				break;
			}
			// If no possible build currently exists, pick lowest value to find build later.
			if (filtered_cards[i]->get_value() < min_value) {
				best_card_selection = i;
				min_value = filtered_cards[i]->get_value();
			}

		}
		// At this point we have a locked card for the build to sum to | card_selected
		// A card selected to play into a build (1) | card_played
		// And a card on the board to build with (2) | build_card
		// If (1) + (2) = locked card value, ask user if they'd like to complete build.
	
		build_cards.push_back(filtered_cards[best_card_selection]);
		remove_card_from_vector(filtered_cards, filtered_cards[best_card_selection]);
		
		if (played_value + build_card->get_value() == selected_value && !extending_build) {
				
			return build_cards.size();
					 
		} else if (played_value + build_card->get_value() == selected_value && extending_build) {

			// create build and update model
			Build* b1 = get_correct_build(card_selected);

			vector<vector<Card*>> temp_build_cards = b1->get_total_build_cards();
			int score = 0;
			for (int i = 0; i < temp_build_cards.size(); i++) {
				for (int j = 0; j < temp_build_cards[i].size(); j++)
					score++;
			}
			
			return score;	
		}
		// Need to build with more cards on the table.
		played_value = get_set_value(build_cards);		
	}
}

vector<Card*> Player::filter_build_options(vector<Card*> available_cards, int played_value, int build_sum) {
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

Build* Player::get_correct_build(Card* my_card) {
	vector<Build*> total_builds = this->game_table->get_current_builds();
	for (int i = 0; i < total_builds.size(); i++) {
		if (total_builds[i]->get_sum_card()->get_card_string() == my_card->get_card_string())
			return total_builds[i];
	}

	return NULL;
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

int Player::get_max_score(vector<int> scores) {
	int max_val = 0;
	int max_index = 0;

	for (int i = 0; i < scores.size(); i++) {
		if (max_val < scores[i]) {
			max_val = scores[i];
			max_index = i;
		}
	}

	return max_index;
}

void Player::remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove) {
	card_list.erase(remove(card_list.begin(), card_list.end(), card_to_remove), card_list.end());
}

bool Player::get_captured_last() const {
	return this->captured_last;
}

void Player::set_captured_last(bool a_captured_last) {
	this->captured_last = a_captured_last;
}