#include <iostream>
#include <vector>

#include "Move.h"
#include "Card.h"

Move::Move(Card* a_card_played, vector<Card*> a_cards_built, vector<Card*> a_cards_captured, char a_move_player, char a_move_type) {
	this->card_played = a_card_played;
	this->cards_built = a_cards_built;
	this->move_player = a_move_player;
	this->move_type = a_move_type;
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

char Move::get_move_player() {
	return this->move_player;
}

char Move::get_move_type() {
	return this->move_type;
}
