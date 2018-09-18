#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Card.h"

using namespace std;

class Move {
	private:
		Card* card_played;
		vector<Card*> cards_built;
		vector<Card*> cards_captured;	
	public:
		Move(Card* a_card_played, vector<Card*> a_cards_built, vector<Card*> a_cards_captured);
		Card* get_card_played();
		vector<Card*> get_cards_built();
		vector<Card*> get_cards_captured();
};

#endif

