#include <vector>
#include <iostream>
#include <utility>

#include "Computer.h"
#include "Card.h" 
#include "Move.h"

using namespace std;

Computer::Computer() {
	Player::set_score(0);
	Player::set_is_human(false);
}

Computer::Computer(int a_score) {
	Player::set_score(a_score);
	Player::set_is_human(false);
}

pair<Card*, char> Computer::play() {
	cout << "Computer is playing!" << endl;
}
