#include <iostream>
#include <string>
#include <vector>

#include "Human.h"
#include "Card.h"

using namespace std;

Human::Human(string a_name) {
	set_name(a_name);
	set_score(0);
}

Human::Human(string a_name, int a_score) {
	set_name(a_name);
	set_score(a_score);
}

string Human::get_name() {
	return this->name;
}

void Human::set_name(string a_name) {
	this->name = a_name;
}

void Human::play() {
	cout << "Human playing!" << endl;
}
