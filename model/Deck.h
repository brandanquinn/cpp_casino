#ifndef DECK_H
#define DECK_H

#include <string>
#include "Card.h"

class Deck {
	private:
		// Array of Card pointers to represent deck.
		Card* game_deck[52];
		Card* top_of_deck;	

	public:	
		Deck();
		// Deck(string pre_loaded_deck);
		void draw_card();
		void shuffle_deck();
		void print_deck();
};

#endif
