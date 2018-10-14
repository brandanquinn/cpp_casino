#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <utility>

#include "Card.h"

class Player {
	private:
		int score;
		vector<Card*> hand;
		vector<Card*> pile;
		bool is_playing;
		bool is_human;

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
		void set_hand(vector<Card*> a_hand);
		void set_pile(vector<Card*> a_pile);
		string get_hand_string();
		string get_pile_string();
		void set_is_human(bool a_is_human);
		bool get_is_human();
};

#endif

