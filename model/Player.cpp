#include <iostream>
#include <vector>

#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player() {
	set_score(0);	
}

int Player::get_score() {
	return this->score;
}

void Player::set_score(int a_score) {
	this->score = a_score;
}

void Player::add_to_hand(Card* new_card) {
	hand.push_back(new_card);
}

vector<Card*> Player::get_hand() {
	return this->hand;
}

void Player::clear_hand() {
	this->hand.clear();
}
