#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "Card.h"
#include "Build.h"

class Table {
	private:
		vector<vector<Card*>> total_table_cards;
		vector<Card*> table_cards;	
		vector<vector<Card*>> table_builds;			
		vector<Build*> current_builds;
		void remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove);
		bool does_build_exist(vector<Card*> build_buddies);
		void remove_from_table_builds(vector<Card*> cards_to_remove);
		bool is_card_in_vector(vector<vector<Card*>>, string my_card_string);
		bool is_card_in_single_vec(vector<Card*> card_list, string my_card_string);

	public:
		Table();
		Table(vector<Card*> a_table_cards, vector<Build*> a_current_builds);
		vector<Card*> get_table_cards();
		vector<vector<Card*>> get_total_table_cards();
		void add_to_table_cards(Card* new_card);
		void clear_table_cards();
		void remove_cards(vector<Card*> cards_to_remove);
		void remove_sets(vector<vector<Card*>> sets_to_remove);
		void remove_builds(vector<Build*> builds_to_remove);
		bool is_empty();
		void add_build(Build* new_build);
		vector<Build*> get_current_builds();
		vector<Card*> get_flattened_card_list();
		bool is_part_of_multi_build(Card* my_card);
		int get_size_of_multi_build(Card* my_card);
		int get_size_of_single_build(Card* my_card);
};

#endif
