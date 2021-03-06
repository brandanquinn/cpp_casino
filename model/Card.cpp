#include <iostream>
#include <unordered_map>

#include "Card.h"

using namespace std;

Card::Card() {
	set_suit('X');
	set_type('0');
	this->is_real_card = false;
}

Card::Card(char a_suit, char a_type) {
	set_suit(a_suit);
	set_type(a_type);
	create_map();
	set_value();	
	set_locked_to_build(false);
	set_part_of_build(false);
	this->is_real_card = true;
}

void Card::create_map() {
	this->type_value_pairs = {
		{'2', 2},
		{'3', 3},
		{'4', 4},
		{'5', 5},
		{'6', 6},
		{'7', 7},
		{'8', 8},
		{'9', 9},
		{'X', 10},
		{'J', 11},
		{'Q', 12},
		{'K', 13},
		{'A', 14}
	};
}

char Card::get_suit() const {
	return this->suit;
}

void Card::set_suit(char a_suit) {
	this->suit = a_suit;
}

char Card::get_type() const {
	return this->type;
}

void Card::set_type(char a_type) {
	this->type = a_type;
}

int Card::get_value() const {
	return this->value;
}

void Card::set_value() {
	// Will need to build a map / algorithm to determine value based on type.	
	this->value = type_value_pairs[this->type];			
}


string Card::get_card_string() const {
	string card_string = string() + get_suit() + get_type();
	return card_string;
}

bool Card::get_locked_to_build() const {
	return this->locked_to_build;
}

void Card::set_locked_to_build(bool a_locked_to_build) {
	this->locked_to_build = a_locked_to_build;
}

bool Card::get_part_of_build() const {
	return this->part_of_build;
}

void Card::set_part_of_build(bool a_part_of_build) {
	this->part_of_build = a_part_of_build;
}

vector<Card*> Card::get_build_buddies() const {
	return this->build_buddies;
}

void Card::set_build_buddies(vector<Card*> a_build_buddies) {
	this->build_buddies = a_build_buddies;
}

bool Card::get_is_real_card() const {
	return this->is_real_card;
}
