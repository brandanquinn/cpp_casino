#include <iostream>
#include <vector>

#include "../model/Tournament.h"
#include "../model/Round.h"
#include "../model/Player.h"
#include "../model/Deck.h"
#include "../model/Table.h"
#include "Display.h"

using namespace std;

Display::Display() {
	
}

void Display::update_view(vector<Player*> game_players, Table* game_table) {
	print_cards(game_players, game_table);
	print_scores(game_players);
}

void Display::print_welcome(int round_num) {
	cout << "Welcome to Casino C++! Round " << round_num << " is about to begin!" << endl;
}


void Display::print_cards(vector<Player*> game_players, Table* game_table) {
	vector<Card*> human_card_list = game_players[0]->get_hand();
	vector<Card*> comp_card_list = game_players[1]->get_hand();
	vector<Card*> table_card_list = game_table->get_table_cards();

	cout << "Player hand: ";
	for (int i = 0; i < human_card_list.size(); i++) {
		cout << human_card_list[i]->get_card_string() << " ";
	}
	cout << endl;	

	cout << "Table hand: ";
	for (int i = 0; i < table_card_list.size(); i++) {
		cout << table_card_list[i]->get_card_string() << " ";
	}
	cout << endl;

	cout << "Computer hand: ";
	for (int i = 0; i < comp_card_list.size(); i++) {
		cout << comp_card_list[i]->get_card_string() << " ";
	}		
	cout << endl;

	
}

void Display::print_scores(vector<Player*> game_players) {
	cout << "Player score: " << game_players[0]->get_score() << endl;
	cout << "Computer score: " << game_players[1]->get_score() << endl; 
}
