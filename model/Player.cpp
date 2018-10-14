#include <iostream>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player() {
	set_score(0);	
	set_is_playing(false);
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

bool Player::hand_is_empty() {
	return this->hand.empty();
}
	
void Player::set_is_playing(bool a_is_playing) {
	this->is_playing = a_is_playing;
}

bool Player::get_is_playing() {
	return this->is_playing;
}

void Player::set_hand(vector<Card*> a_hand) {
	this->hand = a_hand;
}
		
		
void Player::set_pile(vector<Card*> a_pile) {
	this->pile = a_pile;
}

string Player::get_hand_string() {
	string hand_str = "";
	for (int i = 0; i < hand.size(); i++) {
		hand_str += hand[i]->get_card_string() + " ";
	}

	return hand_str;
}

string Player::get_pile_string() {
	string pile_str = "";
	for (int i = 0; i < pile.size(); i++) {
		pile_str += pile[i]->get_card_string() + " ";
	}

	return pile_str;
}

void Player::set_is_human(bool a_is_human) {
	this->is_human = a_is_human;
}
		
bool Player::get_is_human() {
	return this->is_human;
}