#include "build.h"

using namespace std;

Build::Build(a_multi_build, a_sum, a_sum_card) {
	set_multi_build(a_multi_build);
	set_sum(a_sum);
	set_sum_card(a_sum_card);
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

string Build::get_sum_card() {
	return this->sum_card;
}

void Build::set_sum_card(string a_sum_card) {
	this->sum_card = a_sum_card;
}




