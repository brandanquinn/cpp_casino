#include <iostream>
#include <vector>

#include "Move.h"
#include "Card.h"
#include "Build.h"

Move::Move(Card* a_card_played, vector<Card*> a_capturable_cards, vector<vector<Card*>> a_capturable_sets, vector<Build*> a_capturable_builds) {
	this->card_played = a_card_played;
	this->capturable_cards = a_capturable_cards;
	this->capturable_sets = a_capturable_sets;
	this->capturable_builds = a_capturable_builds;
}

Move::~Move() {
	delete this->card_played;
}

Card* Move::get_card_played() const{
	return this->card_played;
}

vector<Card*> Move::get_capturable_cards() const {
	return this->capturable_cards;
}

vector<vector<Card*>> Move::get_capturable_sets() const {
	return this->capturable_sets;
}

vector<Build*> Move::get_capturable_builds() const {
	return this->capturable_builds;
}
