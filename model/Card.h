#ifndef CARD_H
#define CARD_H

#include <unordered_map>

using namespace std;

class Card {
	private:
		char suit;
		char type;
		int value;
		unordered_map<char, int> type_value_pairs;	
	public:
		Card();
		Card(char a_suit, char a_type);
		void create_map();
		char get_suit();
		void set_suit(char a_suit);
		char get_type();
		void set_type(char a_type);
		int get_value();
		void set_value();
		string get_card_string();
};

#endif
