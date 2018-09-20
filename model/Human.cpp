#include <iostream>
#include <string>
#include <vector>

#include "Human.h"
#include "Player.h"
#include "Card.h"

using namespace std;

Human::Human() {
	Player::set_score(0);
}

Human::Human(string a_name, int a_score) {
	set_name(a_name);
	Player::set_score(a_score);
}

string Human::get_name() {
	return this->name;
}

void Human::set_name(string a_name) {
	this->name = a_name;
}

Move* Human::play() {
	char move_option = ' ';
	while (move_option != 't' && move_option != 'b' && move_option != 'c') {
		cout << "Enter (t) to trail, (b) to build, or (c) to capture: ";
		cin >> move_option; 
		if (move_option != 't' && move_option != 'b' && move_option != 'c') {
			cout << "You entered: " << move_option << endl;
			cout << "Incorrect command entered. Try again." << endl;
		}		
	}
	if (move_option == 't') {
		int card_num = get_card_index('t');
		vector<Card*> player_hand = Player::get_hand();
		return new Move(player_hand[card_num], 'h', 't');
	} else if (move_option == 'c') {
		// Select card to capture with
		// Return move with played card, player type, and move option
		int card_num = get_card_index('c');
		vector<Card*> player_hand = Player::get_hand();
		return new Move(player_hand[card_num], 'h', 'c');
	}
}

int Human::get_card_index(char move_type) {
	int card_num = 0;
	while (card_num < 1 || card_num > Player::get_hand().size()) {
		switch(move_type) {
			case 't': 
				cout << "Which card would you like to trail? (Enter # of card position, leftmost being 1): ";
				break;
			case 'c':
				cout << "Which card would you like to play to capture? (Enter # of card position, leftmost being 1): ";
				break;
		}
		cin >> card_num;
		if (card_num < 1 || card_num > Player::get_hand().size()) {
			cout << "Invalid number input. Try again." << endl;
		}
	}
	// To account for array indexing in C++ 
	return card_num -1;
}
	
