#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Card.h"

class Player {
	private:
		int score;
		vector<Card*> hand;
	public:
		Player();
		virtual void play() = 0;
		int get_score();
		void set_score(int a_score);
		void add_to_hand(Card* new_card);
		vector<Card*> get_hand();
};

#endif

