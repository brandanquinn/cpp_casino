#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Card.h"
#include "Table.h"
#include "Build.h"

Table::Table() {

}


// Loose cards
vector<Card*> Table::get_table_cards() {
	return this->table_cards;
}

// All builds + loose cards.
vector<vector<Card*>> Table::get_total_table_cards() {
	vector<vector<Card*>> temp_vec = this->total_table_cards;
	temp_vec.push_back(this->table_cards);
	return temp_vec; 
}

void Table::add_to_table_cards(Card* new_card) {
	if (new_card->get_part_of_build()) {
		vector<Card*> build_buddies = new_card->get_build_buddies();
		// build_buddies.push_back(new_card);
		// Remove elements of build_buddies from table_cards
		for (int i = 0; i < build_buddies.size(); i++) {
			remove_card_from_vector(this->table_cards, build_buddies[i]);
		}
		this->total_table_cards.insert(total_table_cards.begin(), build_buddies);
		// Insert them in the front of the vector with new_card			
	} else {
		this->table_cards.push_back(new_card);
	}
}

void Table::remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove) {
	card_list.erase(remove(card_list.begin(), card_list.end(), card_to_remove), card_list.end());
}

void Table::clear_table_cards() {
	this->table_cards.clear();
}

void Table::remove_cards(vector<Card*> cards_to_remove) {
	for (int i = 0; i < cards_to_remove.size(); i++) {
		Card* removed_card = cards_to_remove[i];
		remove_card_from_vector(this->table_cards, removed_card);
	}
}

void Table::remove_sets(vector<vector<Card*>> sets_to_remove) {
	for (int i = 0; i < sets_to_remove.size(); i++) {
		remove_cards(sets_to_remove[i]);
	}	
}

bool Table::is_empty() {
	return this->table_cards.empty();
}

void Table::add_build(Build* new_build) {
	this->current_builds.push_back(new_build);
}

vector<Build*> Table::get_current_builds() {
	return this->current_builds;
}
