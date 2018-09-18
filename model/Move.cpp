#include <iostream>
#include <vector>

#include "Move.h"
#include "Card.h"

Move::Move(Card* a_card_played, vector<Card*> a_cards_built, vector<Card*> a_cards_captured) {
	this->card_played = a_card_played;
	this->cards_built = a_cards_built;
	this->cards_captured = a_cards_captured;
}

Card* Move::get_card_played() {
	return this->card_played;
}

vector<Card*> Move::get_cards_built() {
	return this->cards_built;
}

vector<Card*> Move::get_cards_captured() {
	return this->cards_captured;
}
