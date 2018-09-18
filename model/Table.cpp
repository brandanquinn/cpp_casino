#include <iostream>
#include <vector>

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
