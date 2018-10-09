#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Card.h"
#include "Table.h"
#include "Build.h"

Table::Table() {

}

Table::Table(vector<Card*> a_table_cards, vector<Build*> a_current_builds) {
	for (int i = 0; i < a_table_cards.size(); i++) {
		// cout << "adding " << a_table_cards[i]->get_card_string() << " to table cards list." << endl;
		add_to_table_cards(a_table_cards[i]);
	}
	this->current_builds = a_current_builds;
}

vector<Card*> Table::get_flattened_card_list() {
	vector<Card*> flat_list;
	for (int i = 0; i < table_builds.size(); i++) {
		for (int j = 0; j < table_builds[i].size(); j++) {
			// cout << "While flattening: " << table_builds[i][j]->get_part_of_build() << endl; 
			flat_list.push_back(table_builds[i][j]);
		}
	}

	for (int i = 0; i < this->table_cards.size(); i++)
		flat_list.push_back(this->table_cards[i]);
	
	return flat_list;
}


// Loose cards
vector<Card*> Table::get_table_cards() {
	return this->table_cards;
}

// All builds + loose cards.
vector<vector<Card*>> Table::get_total_table_cards() {
	vector<vector<Card*>> temp_vec = this->table_builds;
	temp_vec.push_back(this->table_cards);
	// for (int i = 0; i < temp_vec.size(); i++) {
	// 	for (int j = 0; j < temp_vec[i].size(); j++) {
	// 		if (temp_vec[i][j]->get_part_of_build()) { cout << temp_vec[i][j]->get_card_string() << " is part of build." << endl; }
	// 	}
	// }
	return temp_vec; 
}

void Table::add_to_table_cards(Card* new_card) {
	if (new_card->get_part_of_build()) {
		// cout << new_card->get_card_string() << " is part of a build. And has buddies: ";
		vector<Card*> build_buddies = new_card->get_build_buddies();
		// for (int i = 0; i < build_buddies.size(); i++) {
		// 	cout << build_buddies[i]->get_card_string() << " ";
		// }
		// cout << endl;
		
		// build_buddies.push_back(new_card);
		// Remove elements of build_buddies from table_cards
		for (int i = 0; i < build_buddies.size(); i++) {
			remove_card_from_vector(this->table_cards, build_buddies[i]);
		}

		if (!does_build_exist(build_buddies)) {
			for (int i = 0; i < build_buddies.size(); i++)
				build_buddies[i]->set_part_of_build(true); 
			this->table_builds.insert(table_builds.begin(), build_buddies);
		}
		// Insert them in the front of the vector with new_card			
	} else {
		// cout << new_card->get_card_string() << " is not part of a build." << endl;
		this->table_cards.push_back(new_card);
	}
}

bool Table::does_build_exist(vector<Card*> build_buddies) {
	// If build_buddies vector already exists in table_builds; return true.
	// else return false
	for (int i = 0; i < table_builds.size(); i++) {
		for (int j = 0; j < table_builds[i].size(); j++) {
			for (int k = 0; k < build_buddies.size(); k++)
				if (table_builds[i][j]->get_card_string() == build_buddies[i]->get_card_string()) return true;
		}
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
