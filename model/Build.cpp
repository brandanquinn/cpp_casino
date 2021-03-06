#include <vector>
#include <algorithm>
#include <string>

#include "Build.h"
#include "Card.h"

using namespace std;

Build::Build(vector<Card*> a_build_cards, int a_sum, Card* a_sum_card, string a_build_owner) {
	this->total_build_cards.push_back(a_build_cards);	
	set_sum(a_sum);
	set_sum_card(a_sum_card);
	set_build_owner(a_build_owner);
	set_multi_build(false);
}

Build::Build(vector<vector<Card*>> a_multi_build_cards, int a_sum, Card* a_sum_card, string a_build_owner) {
	this->total_build_cards = a_multi_build_cards;	
	set_sum(a_sum);
	set_sum_card(a_sum_card);
	set_build_owner(a_build_owner);
	if (a_multi_build_cards.size() > 1)
		set_multi_build(true);
	else
		set_multi_build(false);
}

bool Build::get_multi_build() const {
	return this->multi_build;
}

void Build::set_multi_build(bool a_multi_build) {
	this->multi_build = a_multi_build;
}

int Build::get_sum() const {
	return this->sum;
}

void Build::set_sum(int a_sum) {
	this->sum = a_sum;
}

Card* Build::get_sum_card() const {
	return this->sum_card;
}

void Build::set_sum_card(Card* a_sum_card) {
	this->sum_card = a_sum_card;
}

vector<vector<Card*>> Build::get_total_build_cards() const {
	return this->total_build_cards;
}

void Build::extend_build(vector<Card*> build_cards) {
	total_build_cards.push_back(build_cards);
	set_multi_build(true);
}

void Build::set_build_owner(string a_build_owner) {
	this->build_owner = a_build_owner;
}

string Build::get_build_owner() const {
	return this->build_owner;
}

string Build::get_build_string() const {
	string build_str = "";

	if (this->multi_build) build_str += "[ ";
	for (int i = 0; i < this->total_build_cards.size(); i++) {
		for (int j = 0; j < this->total_build_cards[i].size(); j++) {
			if (j == 0) build_str += "[ ";
			build_str += this->total_build_cards[i][j]->get_card_string() + " ";
		}
		build_str += "] ";
	}
	if (this->multi_build) build_str += "]";

	return build_str + get_build_owner();
}

string Build::get_build_string_for_view() const {
	string build_str = "";

	if (this->multi_build) build_str += "[ ";
	for (int i = 0; i < this->total_build_cards.size(); i++) {
		for (int j = 0; j < this->total_build_cards[i].size(); j++) {
			if (j == 0) build_str += "[ ";
			build_str += this->total_build_cards[i][j]->get_card_string() + " ";
		}
		build_str += "] ";
	}
	if (this->multi_build) build_str += "]";

	return build_str;
}

void Build::add_to_build(Card* increasing_card) {
	this->total_build_cards[0].push_back(increasing_card);
	int sum = 0;

	for (int i = 0; i < total_build_cards[0].size(); i++)
		sum += total_build_cards[0][i]->get_value();
	set_sum(sum);
}



