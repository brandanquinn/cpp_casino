#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>

#include "Card.h"

class Player {
	private:
		int score;
		vector<Card*> hand;
		vector<Card*> pile;
		bool is_playing;
	public:
		Player();
		virtual pair<Card*, char> play() = 0;
		int get_score();
		void set_score(int a_score);
		void add_to_hand(Card* new_card);
		void add_to_pile(vector<Card*> captured_cards);
		vector<Card*> get_pile();
		void discard(Card* removed_card);
		vector<Card*> get_hand();
		void clear_hand();
		bool hand_is_empty();
		void set_is_playing(bool a_is_playing);
		bool get_is_playing();
};

#endif

