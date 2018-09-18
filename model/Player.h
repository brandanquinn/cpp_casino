#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Card.h"
#include "Move.h"

class Player {
	private:
		int score;
		vector<Card*> hand;
	//	char player_type;
	public:
		Player();
		virtual Move* play() = 0;
		int get_score();
		void set_score(int a_score);
		void add_to_hand(Card* new_card);
		void discard(Card* removed_card);
		vector<Card*> get_hand();
		void clear_hand();
};

#endif

