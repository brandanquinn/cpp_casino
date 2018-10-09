#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Card.h"
#include "Build.h"

using namespace std;

class Move {
	private:
		Card* card_played;
		vector<Card*> capturable_cards;
		vector<vector<Card*>> capturable_sets;
		vector<Build*> capturable_builds;

	public:
		Move(Card* a_card_played, vector<Card*> a_capturable_cards, vector<vector<Card*>> a_capturable_sets, vector<Build*> a_capturable_builds);
		Card* get_card_played();
		vector<Card*> get_capturable_cards();
		vector<vector<Card*>> get_capturable_sets();
		vector<Build*> get_capturable_builds();
};

#endif

