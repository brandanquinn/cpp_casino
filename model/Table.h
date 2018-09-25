#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "Card.h"
#include "Build.h"

class Table {
	private:
		vector<Card*> table_cards;				
		vector<Build*> current_builds;
	public:
		Table();
		vector<Card*> get_table_cards();
		void add_to_table_cards(Card* new_card);
		void clear_table_cards();
		void remove_cards(vector<Card*> cards_to_remove);
		void remove_sets(vector<vector<Card*>> sets_to_remove);
		bool is_empty();
		void add_build(Build* new_build);
		vector<Build*> get_current_builds();
};

#endif
