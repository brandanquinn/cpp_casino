#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "Human.h"
#include "Player.h"
#include "Card.h"

using namespace std;

Human::Human() {
	Player::set_score(0);
	Player::set_player_string("Human");
}

Human::Human(string a_name, int a_score) {
	set_name(a_name);
	Player::set_score(a_score);
	Player::set_player_string("Human");
}

string Human::get_name() {
	return this->name;
}

void Human::set_name(string a_name) {
	this->name = a_name;
}

pair<Card*, char> Human::play() {
	char move_option = ' ';
	pair<Card*, char> move_pair;
	vector<Card*> player_hand = Player::get_hand();
	
	while (move_option != 't' && move_option != 'b' && move_option != 'c' && move_option != 's') {
		cout << "Enter (t) to trail, (b) to build, (c) to capture, or (s) to save current game: ";
		cin >> move_option; 
		if (move_option != 't' && move_option != 'b' && move_option != 'c' && move_option != 's') {
			cout << "You entered: " << move_option << endl;
			cout << "Incorrect command entered. Try again." << endl;
		}		
	}
	if (move_option == 't') {
		int card_num = get_card_index('t');
		move_pair.first = player_hand[card_num];
	} else if (move_option == 'c') {
		// Select card to capture with
		// Return move with played card, player type, and move option
		int card_num = get_card_index('c');
		move_pair.first = player_hand[card_num];
	} else if (move_option == 'b') {
		// Select card to start a build with
		// If that card is already locked to a build; ask if you'd like to start a multi build.
		int card_num = get_card_index('b');
		move_pair.first = player_hand[card_num];
		cout << player_hand[card_num]->get_card_string() << " selected. Building towards value: " << player_hand[card_num]->get_value() << endl;
	} else {
		move_pair.first = new Card;
	}
	
	move_pair.second = move_option;
	return move_pair;	
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
			case 'b':
				cout << "Which card would you like to start or continue a build with? (Enter # of card position, leftmost being 1): ";
				break;
			default:
				cout << "Which card would you like to add to the build? (Enter # of card position, leftmost being 1): ";
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
	
