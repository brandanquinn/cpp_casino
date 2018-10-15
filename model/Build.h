#ifndef BUILD_H
#define BUILD_H

#include <string>
#include <vector>

#include "Card.h"

using namespace std;

class Build {
	private:
		bool multi_build;
		int sum;
		Card* sum_card;
		vector<vector<Card*>> total_build_cards;
		string build_owner;
		
	
	public:
		Build(vector<Card*> a_build_cards, int a_sum, Card* a_sum_card, string a_build_owner);
		Build(vector<vector<Card*>> a_multi_build_cards, int a_sum, Card* a_sum_card, string a_build_owner);
		bool get_multi_build();
		void set_multi_build(bool a_multi_build);
		int get_sum();
		void set_sum(int a_sum);
		Card* get_sum_card();
		void set_sum_card(Card* a_sum_card);
		vector<vector<Card*>> get_total_build_cards();	
		void extend_build(vector<Card*> build_cards);
		string get_build_string();
		void set_build_owner(string a_build_owner);
		string get_build_owner();
};

#endif
