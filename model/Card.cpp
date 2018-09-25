#include <iostream>
#include <unordered_map>

#include "Card.h"

using namespace std;

Card::Card() {
	set_suit('X');
	set_type('0');
}

/*
 * Function Name: Card()
 * Purpose: Default constructor for Card class. 
 * Params: char a_suit, char a_type
 * Returns: None
 * Local Vars:
 * Algo:
 * Assistance: None
 */
Card::Card(char a_suit, char a_type) {
	set_suit(a_suit);
	set_type(a_type);
	create_map();
	set_value();	
	set_locked_to_build(false);
	set_part_of_build(false);
}

/*
 * Function Name: create_map()
 * Purpose: Generate map to pair card type to integer value.
 * Params: None
 * Return Value: None
 * Local Variables: None
 * Algo: 1) Generate map
 * Assistance: None
 */
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

/*
 * Function Name: get_suit()
 * Purpose: Get the card's suit.
 * Params: None
 * Return Value: char suit
 * Local Variables: None
 * Algo: None
 * Assistance: None
 */
char Card::get_suit() {
	return this->suit;
}

/*
 * Function Name: set_suit()
 * Purpose: Set the card's suit.
 * Params: char a_suit, Suit to set member variable to.
 * Return Value: None
 * Local Variables: None
 * Algo: None
 * Assistance: None
 */
void Card::set_suit(char a_suit) {
	this->suit = a_suit;
}

/*
 * Function Name: get_type()
 * Purpose: Get the card's type.
 * Params: None
 * Return Value: char
 * Local Variables: None
 * Algo: None
 * Assistance: None
 */
char Card::get_type() {
	return this->type;
}

/*
 * Function Name: set_type() 
 * Purpose: Set the card's type.
 * Params: char a_type
 * Return Value: None
 * Local Variables: None
 * Algo: None
 * Assistance: None
 */
void Card::set_type(char a_type) {
	this->type = a_type;
}

/*
 * Function Name: get_value
 * Purpose: Get the card's value.
 * Params: None
 * Return Value: int
 * Local Variables: None
 * Algo: None
 * Assistance: None
 */
int Card::get_value() {
	return this->value;
}

/*
 * Function Name: set_value()
 * Purpose: Set the value of a card.
 * Params: None
 * Return Value: None
 * Local Variables: None
 * Algo: 1) Check type_value map to get corresponding value.
 * 	 2) Assign proper value to member variable.
 * Assistance: None
 */
void Card::set_value() {
	// Will need to build a map / algorithm to determine value based on type.	
	this->value = type_value_pairs[this->type];			
}

/*
 * Function Name: get_card_string()
 * Purpose: Generate string containing suit and type of a card.
 * Params: None
 * Return Value: string
 * Local Variables: card_string, Used to concatenate suit and type of card.
 * Algo: 1) Create string for concatenation
 * 	 2) To add the char member variables using '+' operator, use string() as the
 * 	 first arg so that compiler knows you want a string not an integer.
 * 	 3) Return string. 
 * Assistance: None
 */
string Card::get_card_string() {
	string card_string = string() + get_suit() + get_type();
	return card_string;
}

bool Card::get_locked_to_build() {
	return this->locked_to_build;
}

void Card::set_locked_to_build(bool a_locked_to_build) {
	this->locked_to_build = a_locked_to_build;
}

bool Card::get_part_of_build() {
	return this->part_of_build;
}

void Card::set_part_of_build(bool a_part_of_build) {
	this->part_of_build = a_part_of_build;
}

vector<Card*> Card::get_build_buddies() {
	return this->build_buddies;
}

void Card::set_build_buddies(vector<Card*> a_build_buddies) {
	this->build_buddies = a_build_buddies;
}
