#include <iostream>
#include <vector>

#include "../model/Tournament.h"
#include "../model/Round.h"
#include "../model/Player.h"
#include "../model/Deck.h"
#include "../model/Table.h"
#include "../model/Build.h"
#include "Display.h"

using namespace std;

Display::Display() {
	
}

void Display::update_view(vector<Player*> game_players, Table* game_table) {
	print_line_break();
	print_cards(game_players, game_table);
	print_scores(game_players);
	print_line_break();
}

void Display::print_welcome(int round_num) {
	cout << "Welcome to Casino C++! Round " << round_num+1 << " is about to begin!" << endl;
}

void Display::print_line_break() {
	cout << "----------------------------------------------------------" << endl;
}

void Display::print_cards(vector<Player*> game_players, Table* game_table) {
	vector<Card*> human_card_list = game_players[0]->get_hand();
	vector<Card*> human_pile = game_players[0]->get_pile();
	vector<Card*> comp_card_list = game_players[1]->get_hand();
	vector<Card*> comp_pile = game_players[1]->get_pile();
	// vector<vector<Card*>> table_card_list = game_table->get_total_table_cards();
	vector<Card*> table_card_list = game_table->get_flattened_card_list();
	vector<Build*> build_list = game_table->get_current_builds();
	
	cout << "Player pile: ";
	for (int i = 0; i < human_pile.size(); i++) {
		cout << human_pile[i]->get_card_string() << " ";
	}
	cout << endl;

	print_line_break();

	if (game_players[0]->get_is_playing()) cout << "[x] Player hand: ";
	else cout << "Player hand: ";
	for (int i = 0; i < human_card_list.size(); i++) {
		if (human_card_list[i]->get_locked_to_build()) 
			cout << "*" << human_card_list[i]->get_card_string() << " ";
		else
			cout << human_card_list[i]->get_card_string() << " ";
	}
	cout << endl;	

	cout << "Table cards: ";

	int mb_size = 0, build_size = 0;
	bool in_mb = false, in_build = false;

	for (int i = 0; i < table_card_list.size(); i++) {
		if (i == mb_size && in_mb) {
			cout << "] ";
			in_mb = false;
		} 
		if (i == build_size && in_build) { 
			cout << "] ";
			in_build = false;
		}

		if (game_table->is_part_of_multi_build(table_card_list[i]) && !in_mb) {
			in_mb = true;
			mb_size = i + game_table->get_size_of_multi_build(table_card_list[i]);
			cout << "[ ";
		}
		if (table_card_list[i]->get_part_of_build() && !in_build) {
			in_build = true;
			build_size = i + game_table->get_size_of_single_build(table_card_list[i]);
			// cout << "build size for: " << table_card_list[i]->get_card_string() << " is: " << build_size << endl;
			cout << "[ ";
		}
		
		cout << table_card_list[i]->get_card_string() << " ";
		
	}

	cout << endl;

	if (game_players[1]->get_is_playing()) cout <<  "[x] Computer hand: ";
	else cout << "Computer hand: ";	
	for (int i = 0; i < comp_card_list.size(); i++) {
		if (comp_card_list[i]->get_locked_to_build())
			cout << "*" << comp_card_list[i]->get_card_string() << " ";
		else
			cout << comp_card_list[i]->get_card_string() << " ";
	}		
	cout << endl;

	print_line_break();

	cout << "Computer pile: ";
	for (int i = 0; i < comp_pile.size(); i++) {
		cout << comp_pile[i]->get_card_string() << " ";
	}
	cout << endl;
	
	print_line_break();	

	
}

void Display::print_scores(vector<Player*> game_players) {
	cout << "Player score: " << game_players[0]->get_score() << endl;
	cout << "Computer score: " << game_players[1]->get_score() << endl; 
}

