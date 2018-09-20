#include <iostream>
#include <vector>

#include "Move.h"
#include "Card.h"

Move::Move(Card* a_card_played, char a_move_player, char a_move_type) {
	this->card_played = a_card_played;
	this->move_player = a_move_player;
	this->move_type = a_move_type;
}

Card* Move::get_card_played() {
	return this->card_played;
}

char Move::get_move_player() {
	return this->move_player;
}

char Move::get_move_type() {
	return this->move_type;
}
