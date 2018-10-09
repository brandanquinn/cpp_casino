#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "Tournament.h"
#include "Round.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Build.h"
#include "../view/Display.h"

using namespace std;

Tournament::Tournament() {
	this->rounds_played = 0;
	this->game_players.push_back(new Human());
	this->game_players.push_back(new Human());
}

void Tournament::show_start_screen() {
	// Give the option to Start New game or Load saved game
	cout << "Welcome to CPP Casino by BQ!" << endl;
	cout << "(1) Start New Game" << endl;
	cout << "(2) Load Saved Game" << endl;
	int user_input;

	while (user_input != 1 && user_input != 2) {
		cout << "Select a menu option from above: ";
		cin >> user_input;
		if (user_input != 1 && user_input != 2)
			cout << "Invalid option. Try again." << endl;
	}

	if (user_input == 1)
		start_round();
	else
		if(!load_saved_game())
			cout << "Save file does not exist." << endl; 
}

bool Tournament::load_saved_game() {
	const char *file_name = "serialization/save.txt";
	ifstream save_file(file_name);
	if (!save_file.good()) return false;
	int current_round_num, computer_score, player_score;
	vector<Card*> player_hand, player_pile, computer_hand, computer_pile, deck_list, table_cards;
	// vector<vector<Card*>> total_table_cards;
	vector<Build*> current_builds;
	vector<string> build_strings;
	Deck* current_deck = NULL;	
	bool human_next;
	
	

	string line;
	int line_num = 0;	
	if (save_file.is_open()) {
		while (getline(save_file, line)) {
			// current_round
			switch (line_num) {
				case 0: 
					current_round_num = stoi(line.substr(line.find(':') + 1));
					break;
				case 3:
					computer_score = stoi(line.substr(line.find(':') + 1));
					break;
				case 4:
					computer_hand = parse_cards_from_file(line);
					break;	
				case 5:
					computer_pile = parse_cards_from_file(line);
					break;
				case 8:
					player_score = stoi(line.substr(line.find(':') + 1));
					break;
				case 9:
					player_hand = parse_cards_from_file(line);
					break;
				case 10:
					player_pile = parse_cards_from_file(line);
					break;
				case 12:
					// Table:
					build_strings = parse_builds(line.substr(line.find(':') + 1));
					table_cards = get_table_cards(line.substr(line.find(':')+ 1));
					break;
				case 14:
					// Build Owner:
					current_builds = get_build_objects(build_strings, line.substr(line.find(':') + 1), player_hand, computer_hand);
					break;
				case 16:
					deck_list = parse_cards_from_file(line);
					// current_deck = new Deck(deck_list);
					break;
				case 18:
					// Next Player:
					string next_player = line.substr(line.find(':') + 1);
					// Removes excess white space from parsed string.	
					next_player.erase(remove(next_player.begin(), next_player.end(), ' '), next_player.end());
					// Sets human_next boolean based on parsed Next Player value.
					next_player == "Human" ? human_next = true : human_next = false;
					break;
			}
					

			line_num++;
		}
		save_file.close();
	}

	table_cards = modify_table_cards(table_cards, current_builds);

	// set up human player
	game_players[0]->set_hand(player_hand);
	game_players[0]->set_pile(player_pile);
	game_players[0]->set_score(player_score);

	// set up computer player
	game_players[1]->set_hand(computer_hand);
	game_players[1]->set_pile(computer_pile);
	game_players[1]->set_score(computer_score);

	// for (int i = 0; i < table_cards.size(); i++) {
	// 	if (table_cards[i]->get_part_of_build())
	// 		cout << table_cards[i]->get_card_string() << " is a part of a build." << endl;
	// 	else
	// 		cout << table_cards[i]->get_card_string() << " is not part of a build." << endl;
	// }

	Round game_round(rounds_played, game_players, deck_list, table_cards, current_builds);
	this->current_round = &game_round;
	this->current_round->start_game(human_next, true);
	
	return true;
}

vector<Card*> Tournament::modify_table_cards(vector<Card*> table_cards_list, vector<Build*> current_builds) {
	for (int i = 0; i < current_builds.size(); i++) {
		vector<vector<Card*>> total_build_cards = current_builds[i]->get_total_build_cards();
		for (int j = 0; j < total_build_cards.size(); j++) {
			for (int k = 0; k < total_build_cards[j].size(); k++) {
				for (int l = 0; l < table_cards_list.size(); l++) {
					if (total_build_cards[j][k]->get_card_string() == table_cards_list[l]->get_card_string()) {
						table_cards_list[l]->set_build_buddies(total_build_cards[j]);
						table_cards_list[l]->set_part_of_build(true);
						// cout << "Found a match." << endl;
					}
				}
				// Get card string; check if card string is in temp_build_cards vector.
				// Might have to create temp vectors to hold the card strings. 
			}
		}
	}
	return table_cards_list;
}

vector<Card*> Tournament::get_table_cards(string line) {
	// remove brackets and garbage from line then call parse_cards_from_file() and return that vector
	// need to set any card within brackets to be part of build

	// [ [C6 S3] [S9] ] C8 CJ HA 

	int index_of_last_bracket = 0;
	int sum_spaces = 0;
	// iterator to get position of last closing bracket
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ']') index_of_last_bracket = i;
	}

	// find sum_spaces - equivalent to how many loose cards there in a list of table cards.
	for (int i = index_of_last_bracket; i < line.size(); i++) {
		if (line[i] == ' ') sum_spaces++;
	}

	cout << sum_spaces << endl;
	// line.size() - index_of_last_bracket = ?

	line.erase(remove(line.begin(), line.end(), '['), line.end());
	line.erase(remove(line.begin(), line.end(), ']'), line.end());

	// trying to figure out how to set part of build / build buddies so display class can handle properly.
	vector<Card*> table_cards_list = parse_cards_from_file(line);
	// Temporary vector to hold current build cards.

	// Current builds
	// Check part of build cards against current build cards to set build buddies.
	
	cout << "Table build func is happening" << endl;

	return table_cards_list;
}

vector<string> Tournament::parse_builds(string line) {
	// line contains list of cards on the table.
	// Need to strip individual builds from line and create Build objects using those strings.
	vector<Build*> total_builds;
	// Counter variables to keep track of build brackets
	int open_bracket_counter = 0;
	int closed_bracket_counter = 0;
	// Boolean for algo to know whether characters of the string should be added to the build string.
	bool in_build = false;
	// Container / variable to keep track of the parsed build strings.
	vector<string> total_build_str;
	string build_str = "";
	// Iterate through line representing table cards
	// Parses out builds on the table as strings and adds them to the total_build_str vector
	// We will return those strings to the load_saved_game file to be used in the creation of build objects.
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '[') {
			open_bracket_counter++;
			in_build = true;
		} else if (line[i] == ']' && closed_bracket_counter != open_bracket_counter) {
			closed_bracket_counter++;
		}
		if (in_build) build_str += line[i];
		if (closed_bracket_counter == open_bracket_counter && closed_bracket_counter != 0) {
			in_build = false;
			total_build_str.push_back(build_str);
			build_str.clear();
			open_bracket_counter = 0;
			closed_bracket_counter = 0;
		}
	}
	// Here we have a vector of build strings. Can now create a Build object with each one.
	
	return total_build_str;
}

vector<Build*> Tournament::get_build_objects(vector<string> build_strings, string line, vector<Card*> player_hand, vector<Card*> computer_hand) {
	vector<Build*> build_list;
	// First thing we need to do is parse line and get a build owner for each build.
	// Search line for each string in build_strings
	for (int i = 0; i < build_strings.size(); i++) {
		size_t position = line.find(build_strings[i]);
		// int found_index = line.find(build_strings[i]);
		if (position != string::npos) {
			line.erase(position, build_strings[i].length());
		} else {
			cout << "not found" << endl;
		}
	}

	istringstream owner_parser(line);
	vector<string> owner_list;
	do {
		string temp;
		owner_parser >> temp;
		if (!temp.empty()) owner_list.push_back(temp);
	} while (owner_parser);

	owner_parser.clear();

	// Ordered list of build owners.
	// For each owner, we create a build
	// Select the first card in the players hand that can be used and lock it to the build.
	// Build(vector<Card*> a_build_cards, int a_sum, Card* a_sum_card, Player* a_build_owner)
	
	int build_str_val = get_build_str_val(build_strings[0]);

	for (int i = 0; i < owner_list.size(); i++) {
		if (owner_list[i] == "Human") {
			for (int j = 0; j < player_hand.size(); j++) {
				if (player_hand[j]->get_value() == build_str_val) {
					// Sum card found
					// Create build here:
					build_list.push_back(new Build(get_build_cards(build_strings[i]), build_str_val, player_hand[j], game_players[0]));
					player_hand[j]->set_locked_to_build(true);
					return build_list;
				}
			}
		} else {
			for (int j = 0; j < computer_hand.size(); j++) {
				if (computer_hand[j]->get_value() == build_str_val) {
					// Sum card found
					// Create build here:
					build_list.push_back(new Build(get_build_cards(build_strings[i]), build_str_val, computer_hand[j], game_players[1]));
					computer_hand[j]->set_locked_to_build(true);
					return build_list;
				}
			}
		}
	}
}

vector<vector<Card*>> Tournament::get_build_cards(string build_str) {
	vector<vector<Card*>> total_build_cards;
	// Remove overarching brackets
	build_str.erase(0, 1);
	build_str.erase(build_str.size() - 1);
	// If no more brackets exist, call parse_cards_from_file, push_back returned vector and return
	// Call parse_cards_from_file on each element of build.
	bool bracket_found = false;
	string sub_build = "";
	for (int i = 0; i < build_str.length(); i++) {
		if (build_str[i] == '[') bracket_found = true;
		if (build_str[i] == ']')  {
			// end of build string
			bracket_found = false;
			vector<Card*> build_cards = parse_cards_from_file(sub_build);
			total_build_cards.push_back(build_cards);
			// build_cards.clear();
			sub_build.clear();
		}
		if (bracket_found == true && build_str[i] != '[')
			sub_build+=build_str[i];
	}

	return total_build_cards;
}

int Tournament::get_build_str_val(string build_str) {
	// Find # of '[' in string.
	int bracket_counter = 0;
	for (int i = 0; i < build_str.length(); i++) {
		if (build_str[i] == '[') bracket_counter++;
	}
	// bracket counter = # of builds
	build_str.erase(remove(build_str.begin(), build_str.end(), '['), build_str.end());
	build_str.erase(remove(build_str.begin(), build_str.end(), ']'), build_str.end());

	vector<Card*> build_cards = parse_cards_from_file(build_str);

	int build_sum = 0;
	for (int i = 0; i < build_cards.size(); i++)
		build_sum += build_cards[i]->get_value();

	// To account for repeated brackets within multi-builds.
	if (bracket_counter > 1) bracket_counter -= 1;

	return build_sum / bracket_counter;

	// parse_cards_from_file()
	// get sum value of cards and divide by bracket_counter to get build sum.
}

// Used to test serialization.
void Tournament::print_cards(vector<Card*> card_list) {
	for (int i = 0; i < card_list.size(); i++)
		cout << card_list[i]->get_card_string() << " ";
	cout << endl;
}


vector<Card*> Tournament::parse_cards_from_file(string line) {
	string parsed_str = line.substr(line.find(':') + 1);
	// cout << "Parsed string in func: " << parsed_str << endl;
	istringstream parser(parsed_str);
	vector<Card*> cards_vec;
	do {
		string card_str;
		parser >> card_str;
		// cout << "Card string in stringstream: " << card_str << endl;
		if (!card_str.empty())
			cards_vec.push_back(new Card(card_str[0], card_str[1]));
	} while (parser);
	
	parser.clear();
	return cards_vec;
}

void Tournament::start_round() {
	this->rounds_played += 1;	
	Round game_round(rounds_played, game_players);
	this->current_round = &game_round;	
	this->current_round->start_game(coin_toss(), false);
}

void Tournament::end_round() {
	cout << "Round has ended. Player 1 scored: " << game_players[0]->get_score() << ". Player 2 scored: " << game_players[1]->get_score() << endl; 
	this->game_players[0]->clear_hand();
	this->game_players[1]->clear_hand();
	this->current_round->get_game_table()->clear_table_cards();
}

bool Tournament::coin_toss() {
	char call_input;
	
	while (call_input != 'h' && call_input != 't') {
		cout << "We will flip a coin to determine who goes first!" << endl;
		cout << "Enter (h) for heads; or (t) for tails: ";
		cin >> call_input;
		if (call_input != 'h' && call_input != 't') {
			cout << "Invalid input. Try again!" << endl;
		}	
	}
	int call_to_int;
	if (call_input == 'h') call_to_int = 0;
	else call_to_int = 1;	

	int flip = (rand()%2);
	
	if (call_to_int == flip) { 
		cout << "Good call! You will go first." << endl;
		return true;
	}
	else {
		cout << "That was the wrong call. You will go second." << endl;
		return false;	
	}
}



