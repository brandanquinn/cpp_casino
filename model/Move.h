#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Card.h"

using namespace std;

class Move {
	private:
		Card* card_played;
		vector<Card*> capturable_cards;
		vector<vector<Card*>> capturable_sets;
	public:
		Move(Card* a_card_played, vector<Card*> a_capturable_cards, vector<vector<Card*>> a_capturable_sets);
		Card* get_card_played();
		vector<Card*> get_capturable_cards();
		vector<vector<Card*>> get_capturable_sets();
};

#endif

