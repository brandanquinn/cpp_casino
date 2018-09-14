#include <vector>
#include <iostream>

#include "Computer.h"
#include "Card.h" 

using namespace std;

Computer::Computer() {
	Player::set_score(0);
}

Computer::Computer(int a_score) {
	Player::set_score(a_score);
}

void Computer::play() {
	cout << "Computer is playing!" << endl;
}
