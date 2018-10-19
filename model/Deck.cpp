#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <queue>

#include "Deck.h"
#include "Card.h"

using namespace std;

Deck::Deck() {
	// Iterate through deck and initialize cards.
	// Deck made up of 4 suits: 'S' (spades), 'C' (clubs), 'H' (hearts), 'D' (diamonds)
	// Each suit has types '2-9', 'X for 10', 'J, Q, K, A'
	char suits[4] = {'S', 'C', 'H', 'D'};
	char types[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};

	for (int i = 0; i < 52; i++) {
		this->game_deck.push(new Card(suits[i/13], types[i%13]));
	}

	shuffle_deck();
	// print_deck();
	this->top_of_deck = this->game_deck.front();
}

Deck::Deck(vector<Card*> pre_loaded_deck) {
	for (int i = 0; i < pre_loaded_deck.size(); i++) 
		this->game_deck.push(pre_loaded_deck[i]);
	
	this->top_of_deck = this->game_deck.front();
}

Card* Deck::draw_card() {
	// Need to handle if deck is empty
	if (game_deck.empty()) {
		cout << "Deck is empty. Round has ended." << endl;
		return new Card();
	}

	Card * card_drawn = this->top_of_deck;
	game_deck.pop();
	this->top_of_deck = game_deck.front();	

	return card_drawn;			
}


void Deck::shuffle_deck() {	
	random_shuffle(&this->game_deck.front(), &this->game_deck.back());		
}

bool Deck::is_empty() {
	return game_deck.empty();
}

int Deck::get_num_cards_left() const {
	return this->game_deck.size();
}

string Deck::get_deck_string() const {
	queue<Card*> game_deck_copy = this->game_deck;
	string deck_str = "";
	for (int i = 0; i < game_deck_copy.size(); i++) {
		deck_str += game_deck_copy.front()->get_card_string() + " ";
		game_deck_copy.pop();
	}

	return deck_str;
}
	


