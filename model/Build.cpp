#include <vector>
#include <algorithm>
#include <string>

#include "Build.h"
#include "Card.h"

using namespace std;

Build::Build(vector<Card*> a_build_cards, int a_sum, Card* a_sum_card, Player* a_build_owner) {
	this->total_build_cards.push_back(a_build_cards);	
	set_sum(a_sum);
	set_sum_card(a_sum_card);
	this->build_owner = a_build_owner;
}

Build::Build(vector<vector<Card*>> a_multi_build_cards, int a_sum, Card* a_sum_card, Player* a_build_owner) {
	this->total_build_cards = a_multi_build_cards;	
	set_sum(a_sum);
	set_sum_card(a_sum_card);
	this->build_owner = a_build_owner;
	set_multi_build(true);
}

bool Build::get_multi_build() {
	return this->multi_build;
}

void Build::set_multi_build(bool a_multi_build) {
	this->multi_build = a_multi_build;
}

int Build::get_sum() {
	return this->sum;
}

void Build::set_sum(int a_sum) {
	this->sum = a_sum;
}

Card* Build::get_sum_card() {
	return this->sum_card;
}

void Build::set_sum_card(Card* a_sum_card) {
	this->sum_card = a_sum_card;
}

vector<vector<Card*>> Build::get_total_build_cards() {
	return this->total_build_cards;
}

void Build::extend_build(vector<Card*> build_cards) {
	total_build_cards.push_back(build_cards);
}





