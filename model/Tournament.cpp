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
	this->rounds_played = 1;
	this->card_count = 0;
	this->game_players.push_back(new Human());
	this->game_players.push_back(new Computer());
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
		start_round(true);
	else
		if(!load_saved_game())
			cout << "Save file does not exist." << endl; 
}

bool Tournament::load_saved_game() {
	const char * files[4] = {"serialization/case1.txt", "serialization/case2.txt", "serialization/case3.txt", "serialization/save_game.txt"};
	char *file_name;
	int input = 0;
	cout << "(1) serialization case 1" << endl;
	cout << "(2) serialization case 2" << endl;
	cout << "(3) serialization case 3" << endl;
	cout << "(4) saved game file" << endl;

	while (input != 1 && input != 2 && input != 3 && input != 4) {
		cout << "Which file would you like to load: ";
		cin >> input;
		if (input != 1 && input != 2 && input != 3 && input != 4) cout << "Invalid input. Try again." << endl;
	}
	ifstream save_file(files[input-1]);
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

	if (card_count < 52) {
		cout << "Corrupt save file. Exiting game." << endl;
		return false;
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

	this->rounds_played = current_round_num;

	Round game_round(rounds_played, game_players, deck_list, table_cards, current_builds);
	this->current_round = &game_round;
	this->current_round->start_game(human_next, true, vector<Card*>());
	if (game_players[0]->get_hand().size() == 0 && game_players[1]->get_hand().size() == 0) {
		end_round();
	}
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


	line.erase(remove(line.begin(), line.end(), '['), line.end());
	line.erase(remove(line.begin(), line.end(), ']'), line.end());

	// cout << "Line after removing brackets: " << line << endl;

	// trying to figure out how to set part of build / build buddies so display class can handle properly.
	vector<Card*> table_cards_list = parse_cards_from_file(line);
	// Temporary vector to hold current build cards.

	// Current builds
	// Check part of build cards against current build cards to set build buddies

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

	int build_str_val;

	for (int i = 0; i < owner_list.size(); i++) {
		build_str_val = get_build_str_val(build_strings[i]);
		if (owner_list[i] == "Human") {
			for (int j = 0; j < player_hand.size(); j++) {
				if (player_hand[j]->get_value() == build_str_val) {
					// Sum card found
					// Create build here:
					build_list.push_back(new Build(get_build_cards(build_strings[i]), build_str_val, player_hand[j], "Human"));
					player_hand[j]->set_locked_to_build(true);
				}
			}
		} else {
			for (int j = 0; j < computer_hand.size(); j++) {
				if (computer_hand[j]->get_value() == build_str_val) {
					// Sum card found
					// Create build here:
					build_list.push_back(new Build(get_build_cards(build_strings[i]), build_str_val, computer_hand[j], "Computer"));
					computer_hand[j]->set_locked_to_build(true);
				}
			}
		}
	}

	return build_list;
}

vector<vector<Card*>> Tournament::get_build_cards(string build_str) {
	vector<vector<Card*>> total_build_cards;

	// To see if build_str is a multi-build
	int bracket_count = 0;
	for (int i = 0; i < build_str.size(); i++) {
		if (build_str[i] == '[') bracket_count++;
	}

	// Remove overarching brackets if multi-build
	if (bracket_count > 1) {
		build_str.erase(0, 1);
		build_str.erase(build_str.size() - 1);
	}
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
	if (parsed_str.empty()) return cards_vec;
	do {
		string card_str;
		parser >> card_str;
		// cout << "Card string in stringstream: " << card_str << endl;
		if (!card_str.empty()) {
			cards_vec.push_back(new Card(card_str[0], card_str[1]));
			this->card_count++;
		}
	} while (parser);
	
	parser.clear();
	return cards_vec;
}

vector<Card*> Tournament::get_deck_list() {
	vector<Card*> temp_vec;
	const char* deck_file = "serialization/deck.txt";

	ifstream deck_parser(deck_file);

	if (!deck_parser.good()) {
		cout << "Deck file does not exist." << endl;
		return temp_vec;
	}

	string line;
	int line_count = 0;
	if (deck_parser.is_open()) {
		while (getline(deck_parser, line)) {
			if (!line.empty()) {
				temp_vec.push_back(new Card(line[0], line[1]));
				line_count++;
			}
		}
	}

	if (line_count < 52) {
		cout << "Invalid deck loaded. Check save file and try again." << endl;
		return vector<Card*>();
	} else {
		return temp_vec;
	}

}

void Tournament::start_round(bool first_round) {
	this->rounds_played;	
	Round game_round(rounds_played, game_players);
	this->current_round = &game_round;
	vector<Card*> deck_list;

	char user_input = ' ';
	while (user_input != 'n') {
		cout << "Would you like to load a deck from file? (y/n) ";
		cin >> user_input;

		if (user_input != 'y' && user_input != 'n') {
			cout << "Invalid input. Try again." << endl;
		}

		if (user_input == 'y') {
			deck_list = get_deck_list();
			if (deck_list.empty()) {
				cout << "Deck not properly loaded from file. Try again." << endl;
			} else {
				break;
			}
		}
	}

	
	

	if (first_round) {
		this->current_round->start_game(coin_toss(), false, deck_list);
	} else {
		if (this->game_players[0]->get_captured_last())
			this->current_round->start_game(true, false, deck_list);
		else
			this->current_round->start_game(false, false, deck_list);
	}

	if (game_players[0]->get_hand().size() == 0 && game_players[1]->get_hand().size() == 0) {
		end_round();
	} 
}

void Tournament::end_round() {
	this->rounds_played++;
	// Compute scores, if player's score is >= 21, they are declared the victor and the game is over
	// Else reset deck, clear hands, and piles
	// Start new round.
	cout << "Final pile for Player 1: " << this->game_players[0]->get_pile_string() << endl;
	cout << "Final pile for Player 2: " << this->game_players[1]->get_pile_string() << endl;
	compute_player_scores();
	if (this->game_players[0]->get_score() >= 21 && this->game_players[1]->get_score() >= 21) {
		// tie
		cout << "Game has ended, both players have tied." << endl;
		cout << "Final Score for Player 1: " << this->game_players[0]->get_score() << endl;
		cout << "Final Score for Player 2: " << this->game_players[1]->get_score() << endl;
	} else if (this->game_players[0]->get_score() >= 21) {
		cout << "Game has ended, Player 1 is the victor!" << endl;
		cout << "Final Score for Player 1: " << this->game_players[0]->get_score() << endl;
		cout << "Final Score for Player 2: " << this->game_players[1]->get_score() << endl;
	} else if (this->game_players[1]->get_score() >= 21) {
		cout << "Game has ended, Player 2 is the victor!" << endl;
		cout << "Final Score for Player 1: " << this->game_players[0]->get_score() << endl;
		cout << "Final Score for Player 2: " << this->game_players[1]->get_score() << endl;
	} else {
		this->game_players[0]->clear_hand();
		this->game_players[1]->clear_hand();
		this->game_players[0]->clear_pile();
		this->game_players[1]->clear_pile();
		this->current_round->get_game_table()->clear_table_cards();
		cout << "Round has ended. Player 1 has score: " << this->game_players[0]->get_score() << ". Player 2 has score: " << this->game_players[1]->get_score() << endl; 
		cout << "Starting new round. Good luck!" << endl;
		start_round(false); 
	}
}

void Tournament::compute_player_scores() {
	// score info init
	int p1_current_score = this->game_players[0]->get_score();
	vector<Card*> p1_current_pile = this->game_players[0]->get_pile();

	int p2_current_score = this->game_players[1]->get_score();
	vector<Card*> p2_current_pile = this->game_players[1]->get_pile();

	cout << "Player 1 has pile of size: " << p1_current_pile.size() << endl;
	cout << "Player 2 has pile of size: " << p2_current_pile.size() << endl;
	// Scoring for pile size
	if (p1_current_pile.size() > p2_current_pile.size()) {
		p1_current_score += 3;
	} else if (p2_current_pile.size() > p1_current_pile.size()) {
		p2_current_score += 3;
	}

	// Scoring for spades count / 10 of diamonds / 2 of spades / ace count
	int p1_spades_count = 0, p2_spades_count = 0;
	for (int i = 0; i < p1_current_pile.size(); i++) {
		if (p1_current_pile[i]->get_suit() == 'S')
			p1_spades_count++;
		if (p1_current_pile[i]->get_type() == 'A')
			p1_current_score++;
		if (p1_current_pile[i]->get_card_string() == "DX")
			p1_current_score += 2;
		if (p1_current_pile[i]->get_card_string() == "S2")
			p1_current_score++;
	
	}
	cout << "Player 1 has: " << p1_spades_count << " spades cards." << endl;
	for (int i = 0; i < p2_current_pile.size(); i++) {
		if (p2_current_pile[i]->get_suit() == 'S')
			p2_spades_count++;
		if (p2_current_pile[i]->get_type() == 'A')
			p2_current_score++;
		if (p2_current_pile[i]->get_card_string() == "DX")
			p2_current_score += 2;
		if (p2_current_pile[i]->get_card_string() == "S2")
			p2_current_score++;
	}
	cout << "Player 2 has: " << p2_spades_count << " spades cards." << endl;
	if (p1_spades_count > p2_spades_count) p1_current_score++;
	else if (p2_spades_count > p1_spades_count) p2_current_score++;

	this->game_players[0]->set_score(p1_current_score);
	this->game_players[1]->set_score(p2_current_score);

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



