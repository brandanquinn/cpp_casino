#ifndef CARD_H
#define CARD_H

#include <unordered_map>
#include <vector>

using namespace std;

class Card {
	private:
		char suit;
		char type;
		int value;
		unordered_map<char, int> type_value_pairs;	
		bool locked_to_build;
		bool part_of_build;
		vector<Card*> build_buddies;
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
		bool get_locked_to_build();
		void set_locked_to_build(bool a_locked_to_build);
		bool get_part_of_build();
		void set_part_of_build(bool a_part_of_build);
		vector<Card*> get_build_buddies();
		void set_build_buddies(vector<Card*> a_build_buddies);
};

#endif
