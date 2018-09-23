#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Card.h"
#include "Table.h"

Table::Table() {

}

vector<Card*> Table::get_table_cards() {
	return this->table_cards;
}

void Table::add_to_table_cards(Card* new_card) {
	this->table_cards.push_back(new_card);
}

void Table::clear_table_cards() {
	this->table_cards.clear();
}

void Table::remove_cards(vector<Card*> cards_to_remove) {
	for (int i = 0; i < cards_to_remove.size(); i++) {
		Card* removed_card = cards_to_remove[i];
		this->table_cards.erase(
			remove(
			table_cards.begin(), 
			table_cards.end(), 
			removed_card
			), 
			table_cards.end());
	}
}
