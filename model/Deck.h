#ifndef DECK_H
#define DECK_H

#include <string>
#include <queue>
#include "Card.h"

using namespace std;

class Deck {
	private:
		// Array of Card pointers to represent deck.
		queue <Card*> game_deck;
		Card* top_of_deck;	

	public:	
		Deck();
		// Deck(string pre_loaded_deck);
		Card* draw_card();
		void shuffle_deck();
		void print_deck();
};

#endif
