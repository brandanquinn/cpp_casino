#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

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

Round::Round(int a_round_num, vector<Player*> a_game_players, vector<Card*> a_deck_list, vector<Card*> a_table_cards, vector<Build*> a_current_builds) {
	this->round_num = a_round_num;
	this->game_deck = new Deck(a_deck_list);
	// create and use table constructor with cards + builds
	this->game_table = new Table(a_table_cards, a_current_builds);
	this->game_players = a_game_players;
	this->game_view = new Display;
}

int Round::get_round_num() {
	return this->round_num;
}

void Round::start_game(bool human_is_first, bool loaded_game) {
	if (!loaded_game) {
		deal_hands(game_players);
		deal_to_table(game_table);
	}
		
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

	player_one->set_game_table(this->game_table);
	player_two->set_game_table(this->game_table);
	
	player_one->set_is_playing(true);

	this->game_view->print_welcome(this->round_num);
	this->game_view->update_view(this->game_players, this->game_table);

	while (!this->game_deck->is_empty() || !(player_one->hand_is_empty() && player_two->hand_is_empty())) {	
		// cout << "Seg fault occurs before move selection." << endl;
		if (player_one->hand_is_empty() && player_two->hand_is_empty() && !this->game_deck->is_empty()) { 
			deal_hands(game_players);
			this->game_view->update_view(this->game_players, this->game_table);
		}
		while (!possible_move_selected && !player_one->hand_is_empty()) {
			pair<Card*, char> move_pair = player_one->play();
			if (player_one->get_player_string() == "Computer") {
				possible_move_selected = make_move(move_pair.second, move_pair.first, player_one);
			} else {
				if (move_pair.second == 't') {
					trail(move_pair.first, player_one);
					possible_move_selected = true;
				} else if (move_pair.second == 'c') {
					possible_move_selected = capture(move_pair.first, player_one);
				} else if (move_pair.second == 'b') {
					possible_move_selected = build(move_pair.first, player_one);
				} else {
					// save game
					// call deserialization function
					possible_move_selected = save_game();
					cout << "Game saved." << endl;
				
				}
			}
		}
		player_one->set_is_playing(false);
		player_two->set_is_playing(true);
		this->game_view->update_view(this->game_players, this->game_table);
		possible_move_selected = false;
		while (!possible_move_selected && !player_two->hand_is_empty()) {
			pair<Card*, char> move_pair = player_two->play();
			if (player_two->get_player_string() == "Computer") {
				possible_move_selected = make_move(move_pair.second, move_pair.first, player_two);
			} else {
				if (move_pair.second == 't') {
					trail(move_pair.first, player_two);
					possible_move_selected = true;
				} else if (move_pair.second == 'c') {
					possible_move_selected = capture(move_pair.first, player_two);
				} else if (move_pair.second == 'b') {
					possible_move_selected = build(move_pair.first, player_two);
				} else {
					// save game
					// call deserialization function
					possible_move_selected = save_game();
					cout << "Game saved." << endl;
				
				}
			}
		}
		player_one->set_is_playing(true);
		player_two->set_is_playing(false);
		this->game_view->update_view(this->game_players, this->game_table);
		possible_move_selected = false;	
	}

}

bool Round::make_move(char move_type, Card* card_selected, Player* game_player) {
	if (move_type == 'c') {
		vector<Build*> capturable_builds; 
	
		vector<Build*> current_builds = this->game_table->get_current_builds();
		for (int i = 0; i < current_builds.size(); i++) {
			if (current_builds[i]->get_sum_card()->get_card_string() == card_selected->get_card_string() || 
			(current_builds[i]->get_build_owner() != game_player->get_player_string() && current_builds[i]->get_sum_card()->get_value() == card_selected->get_value()) ) {
				capturable_builds.push_back(current_builds[i]);	
			}
		}

		int played_value = card_selected->get_value();
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

		vector<vector<Card*>> selected_sets;

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
		vector<Card*> pile_additions;

		game_player->discard(card_selected);
		this->game_table->remove_cards(capturable_cards);	
		this->game_table->remove_sets(selected_sets);
		this->game_table->remove_builds(capturable_builds);	

		pile_additions.push_back(card_selected);
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
		game_player->add_to_pile(pile_additions);
		return true;
	} else if (move_type == 'b') {
		// Get value of card selected
		// Have player select card to play into the build.
		int selected_value = card_selected->get_value();
		vector<Card*> player_hand = game_player->get_hand();
		bool extending_build = false;

		if (card_selected->get_locked_to_build()) {
			for (int i = 0; i < player_hand.size(); i++) {
				if (create_build(card_selected, player_hand[i], true, game_player)) {
					return true;
				}
			}
		} else {
			for (int i = 0; i < player_hand.size(); i++) {
				if (create_build(card_selected, player_hand[i], false, game_player)) {
					return true;
				}
			}
		}
	} else if (move_type == 't') {
		trail(card_selected, game_player);
		return true;
	}

	return false;
}

bool Round::create_build(Card* card_selected, Card* card_played, bool extending_build, Player* game_player) {	
	// If that card has value >= locked card: return false
	vector<Card*> table_cards = this->game_table->get_table_cards();
	vector<Card*> filtered_cards = table_cards;
	int selected_value = card_selected->get_value();
	int played_value = card_played->get_value();
	if (played_value >= selected_value) return false;
	// Provide options to build with on table.
	bool build_created = false;
	vector<Card*> build_cards;
	build_cards.push_back(card_played);
	
	while (true) {
		// Filter available cards to remove all cards with value + played_value > locked card val
		filtered_cards = filter_build_options(filtered_cards, played_value, selected_value);
		if (filtered_cards.empty()) return false;
		int best_card_selection = 0;
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

		Card* build_card = filtered_cards[best_card_selection];
		build_cards.push_back(build_card);
		remove_card_from_vector(filtered_cards, build_card);
		
		if (played_value + build_card->get_value() == selected_value && !extending_build) {

			// create build and update model
			Build* b1 = new Build(build_cards, selected_value, card_selected, game_player->get_player_string());
			this->game_table->add_build(b1);
			card_played->set_part_of_build(true);
			card_played->set_build_buddies(build_cards);
			build_card->set_part_of_build(true);
			game_player->discard(card_played);
			this->game_table->add_to_table_cards(card_played);
			card_selected->set_locked_to_build(true);
			
			return true;			 
		} else if (played_value + build_card->get_value() == selected_value && extending_build) {

			// create build and update model
			Build* b1 = get_correct_build(card_selected);
			b1->extend_build(build_cards);
			card_played->set_part_of_build(true);
			card_played->set_build_buddies(build_cards);
			build_card->set_part_of_build(true);
			game_player->discard(card_played);
			this->game_table->add_to_table_cards(card_played);
			
			return true;	
		}
		// Need to build with more cards on the table.
		played_value = get_set_value(build_cards);
	}
}

bool Round::save_game() {
	// Open '/serialization/save_game.txt' for writing
	// Write Round: round_num
	// newline
	// For both players:
	// Player:
	// \t Score: player_score
	// \t Hand: player_hand
	// \t Pile: player_pile
	// newline
	// Table: get table string from view and print it.
	// newline
	// Build Owner: print each build from left to right with respective owner
	// newline
	// Deck: game_deck
	// Next Player: use player->get_is_playing();
	const char *file_name = "serialization/save_game.txt";
	ofstream save_file(file_name);
	string next_player;
	if (save_file.is_open()) {
		// Round
		save_file << "Round: " << this->round_num << "\n\n";

		// Player info
		// Computer
		save_file << "Computer: \n";
		save_file << "\t Score: " << this->game_players[1]->get_score() << endl;
		save_file << "\t Hand: " << this->game_players[1]->get_hand_string() << endl;
		save_file << "\t Pile: " << this->game_players[1]->get_pile_string() << "\n\n";

		// Human
		save_file << "Human: \n";
		save_file << "\t Score: " << this->game_players[0]->get_score() << endl;
		save_file << "\t Hand: " << this->game_players[0]->get_hand_string() << endl;
		save_file << "\t Pile: " << this->game_players[0]->get_pile_string() << "\n\n";

		// Table
		save_file << "Table: " << this->game_table->get_table_string() << "\n\n";

		// Builds
		save_file << "Build Owner: " << get_build_strings() << "\n\n";

		// Deck
		save_file << "Deck: " << this->game_deck->get_deck_string() << "\n\n";

		// Next Player
		if (this->game_players[0]->get_is_playing()) next_player = "Human";
		else next_player = "Computer";
		save_file << "Next Player: " << next_player; 
	}

	return false;

}

string Round::get_build_strings() {
	string build_strings = "";
	vector<Build*> current_builds = this->game_table->get_current_builds();

	for (int i = 0; i < current_builds.size(); i++) {
		build_strings += current_builds[i]->get_build_string() + " ";
	}

	return build_strings;
}

bool Round::deal_hands(vector<Player*> game_players) {
	for (int i = 0; i < 4; i++) {
		Card* new_card =  game_deck->draw_card();
		if (new_card->get_suit() == 'X') return false;
		game_players[0]->add_to_hand(new_card);
	}
	for (int i = 0; i < 4; i++) {
		Card* new_card =  game_deck->draw_card();
		if (new_card->get_suit() == 'X') return false;
		game_players[1]->add_to_hand(new_card);
 	}
	
	return true;
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
	vector<Build*> capturable_builds = game_move->get_capturable_builds();
	vector<vector<Card*>> selected_sets;

	if (capturable_cards.empty() && capturable_sets.empty() && capturable_builds.empty()) {
		cout << "No cards on the table can be captured with this card." << endl;
		return false;
	}

	if (!capturable_builds.empty()) {
		cout << "Would you like to capture? (y/n)" << endl;
		for (int i = 0; i < capturable_builds.size(); i++) {
			vector<vector<Card*>> temp_build_cards = capturable_builds[i]->get_total_build_cards();
			if (temp_build_cards.size() > 1) cout << "[ ";
			for (int j = 0; j < temp_build_cards.size(); j++) {
				cout << "[ ";
				for (int k = 0; k < temp_build_cards[j].size(); k++) {
					cout << temp_build_cards[j][k]->get_card_string() << " ";
				}
				cout << "]";
			}
			if (temp_build_cards.size() > 1) cout << " ]";
			cout << endl;
		}
		
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
		
		int set_selection = -1;
		while (set_selection != 0) {
			cout << "List of capturable sets:" << endl;
			for (int i = 0; i < capturable_sets.size(); i++) {
				cout << "Subset (" << i+1 << ") ";
				for (int j = 0; j < capturable_sets[i].size(); j++) {
					cout << capturable_sets[i][j]->get_card_string() << " ";
				}
				cout << endl;
			}
			cout << "Select which sets you'd like to capture. Input '0' when you are finished." << endl;
			cout << "Input: ";
			cin >> set_selection;
			if (set_selection == 0) break;
			if (set_selection <= 0 || set_selection > capturable_sets.size()) {
				cout << "Input not recognized. Try again." << endl;
			} else {
				selected_sets.push_back(capturable_sets[set_selection-1]);	
				// remove cards in selected_sets from capturable_sets
				remove_selected_set(capturable_sets, capturable_sets[set_selection-1]);
			}	
		} 	
	}

	
	game_player->discard(card_played);
	this->game_table->remove_cards(capturable_cards);	
	this->game_table->remove_sets(selected_sets);
	this->game_table->remove_builds(capturable_builds);	

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
	game_player->add_to_pile(pile_additions);
	return true;			
}

void Round::remove_selected_set(vector<vector<Card*>> &total_sets, vector<Card*> selected_set) {
	// if any cards within the selected_set exist in total_subset; remove subset
	
	for (int i = 0; i < selected_set.size(); i++) {
		for (int j = 0; j < total_sets.size(); j++) {
			if (count(total_sets[j].begin(), total_sets[j].end(), selected_set[i]))
				total_sets.erase(total_sets.begin() + j);	
		}
	}
}

bool Round::build(Card* card_selected, Player* game_player) {
	// Get value of card selected
	// Have player select card to play into the build.
	int selected_value = card_selected->get_value();
	vector<Card*> player_hand = game_player->get_hand();
	int card_num = 0;
	bool extending_build = false;

	if (card_selected->get_locked_to_build()) {
		extending_build = true;
		// Player should be prompted to extend a build to a multi-build.
		while (card_num < 1 || card_num > player_hand.size()) {
		cout << "Which card would you like to extend your build with? (Enter # of card position, leftmost being 1): ";
		cin >> card_num;
		if (card_num < 1 || card_num > player_hand.size())
			cout << "Invalid number input. Try again." << endl;
		}
	} else {
		while (card_num < 1 || card_num > player_hand.size()) {
			cout << "Which card would you like to add to the build? (Enter # of card position, leftmost being 1): ";
			cin >> card_num;
			if (card_num < 1 || card_num > player_hand.size())
				cout << "Invalid number input. Try again." << endl;
		}
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
			if (card_num == 0) break;
			if (card_num < 1 || card_num > filtered_cards.size()) {
				cout << "Invalid number input. Try again" << endl;	
			} 
		}
		// At this point we have a locked card for the build to sum to | card_selected
		// A card selected to play into a build (1) | card_played
		// And a card on the board to build with (2) | build_card
		// If (1) + (2) = locked card value, ask user if they'd like to complete build.
		
		if (card_num == 0 && build_cards.size() == 1) {
			cout << "0 was input, returning to move selection." << endl;
			return false;
		}

		Card* build_card = filtered_cards[card_num-1];
		build_cards.push_back(build_card);
		remove_card_from_vector(filtered_cards, build_card);
		
		
		if (played_value + build_card->get_value() == selected_value && !extending_build) {
			// Needs to print all cards in build_cards
			cout << "Would you like to create the build of: [ "; 
			print_vector_cards(build_cards); 
			cout << "] (y/n)? " << endl;
			char user_input;
			while (user_input != 'y' && user_input != 'n') {
				cin >> user_input;
				if (user_input != 'y' && user_input != 'n') {
					cout << "Input not recognized. Try again." << endl;
				}
			}
			if (user_input == 'y') {
				// create build and update model
				Build* b1 = new Build(build_cards, selected_value, card_selected, game_player->get_player_string());
				this->game_table->add_build(b1);
				card_played->set_part_of_build(true);
				card_played->set_build_buddies(build_cards);
				build_card->set_part_of_build(true);
				game_player->discard(card_played);
				this->game_table->add_to_table_cards(card_played);
				card_selected->set_locked_to_build(true);
				
				return true;
			} else {
				return false;
			}			 
		} else if (played_value + build_card->get_value() == selected_value && extending_build) {
			cout << "Would you like to extend your build with: [ "; 
			print_vector_cards(build_cards); 
			cout << "] (y/n)? " << endl;
			char user_input;
			while (user_input != 'y' && user_input != 'n') {
				cin >> user_input;
				if (user_input != 'y' && user_input != 'n') {
					cout << "Input not recognized. Try again." << endl;
				}
			}
			if (user_input == 'y') {
				// create build and update model
				Build* b1 = get_correct_build(card_selected);
				b1->extend_build(build_cards);
				card_played->set_part_of_build(true);
				card_played->set_build_buddies(build_cards);
				build_card->set_part_of_build(true);
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

Build* Round::get_correct_build(Card* my_card) {
	vector<Build*> total_builds = this->game_table->get_current_builds();
	for (int i = 0; i < total_builds.size(); i++) {
		if (total_builds[i]->get_sum_card()->get_card_string() == my_card->get_card_string())
			return total_builds[i];
	}

	return NULL;
}

void Round::print_vector_cards(vector<Card*> card_list) {
	for (int i = 0; i < card_list.size(); i++) {
		cout << card_list[i]->get_card_string() << " ";
	}
}

vector<Card*> Round::filter_build_options(vector<Card*> available_cards, int played_value, int build_sum) {
	vector<Card*> filtered_options;
	// Iterate through avail_cards
	// If avail_card val + played_val < build_sum
	// Add avail_card to filtered vector
	// Return filtered vector
	if (available_cards.empty()) cout << "No cards available in filter_options." << endl;
	cout << "Played value: " << played_value << " Build sum: " << build_sum << endl;

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
	vector<Build*> capturable_builds; 
	// if (card_played->get_locked_to_build()) {
	// 		// give option to capture your build
	// 		// if yes selected, get other builds that can be captured and offer them.
	// 			// Then, continue with algo
	// 		// if no, return Move obj with empty capturable_cards / sets 
	// 		vector<Build*> current_builds = this->game_table->get_current_builds();
	// 		for (int i = 0; i < current_builds.size(); i++) {
	// 			if (current_builds[i]->get_sum_card()->get_card_string() == card_played->get_card_string() || 
	// 			(current_builds[i]->get_player_of_build() != game_player && current_builds[i]->get_sum_card()->get_value() == card_played->get_value()) ) {
	// 				capturable_builds.push_back(current_builds[i]);	
	// 			}
	// 		}
	// }
	vector<Build*> current_builds = this->game_table->get_current_builds();
	for (int i = 0; i < current_builds.size(); i++) {
		if (current_builds[i]->get_sum_card()->get_card_string() == card_played->get_card_string() || 
		(current_builds[i]->get_build_owner() != game_player->get_player_string() && current_builds[i]->get_sum_card()->get_value() == card_played->get_value()) ) {
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

int Round::get_set_value(vector<Card*> card_set) {
	int value_sum = 0;
	for (int i = 0; i < card_set.size(); i++) {
		value_sum += card_set[i]->get_value();
	}
	return value_sum;
}

void Round::remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove) {
	card_list.erase(remove(card_list.begin(), card_list.end(), card_to_remove), card_list.end());
}

