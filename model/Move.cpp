#include <iostream>
#include <vector>

#include "Move.h"
#include "Card.h"

Move::Move(Card* a_card_played, vector<Card*> a_capturable_cards, vector<vector<Card*>> a_capturable_sets) {
	this->card_played = a_card_played;
	this->capturable_cards = a_capturable_cards;
	this->capturable_sets = a_capturable_sets;
}

Card* Move::get_card_played() {
	return this->card_played;
}

vector<Card*> Move::get_capturable_cards() {
	return this->capturable_cards;
}

vector<vector<Card*>> Move::get_capturable_sets() {
	return this->capturable_sets;
}
