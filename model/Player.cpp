#include <iostream>
#include <vector>
#include <algorithm>

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

void Player::add_to_pile(vector<Card*> captured_cards) {
	for (int i = 0; i < captured_cards.size(); i++) {
		this->pile.push_back(captured_cards[i]);
	}	
}

vector<Card*> Player::get_pile() {
	return this->pile;
}

void Player::discard(Card* removed_card) {
	this->hand.erase(remove(hand.begin(), hand.end(), removed_card), hand.end());
}

vector<Card*> Player::get_hand() {
	return this->hand;
}

void Player::clear_hand() {
	this->hand.clear();
}


