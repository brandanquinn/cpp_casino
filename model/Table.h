#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "Card.h"

class Table {
	private:
		vector<Card*> table_cards;				
	public:
		Table();
		vector<Card*> get_table_cards();
		void add_to_table_cards(Card* new_card);
		void clear_table_cards();
		void remove_cards(vector<Card*> cards_to_remove);
};

#endif
