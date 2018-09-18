#include <vector>
#include <iostream>

#include "Computer.h"
#include "Card.h" 
#include "Move.h"

using namespace std;

Computer::Computer() {
	Player::set_score(0);
}

Computer::Computer(int a_score) {
	Player::set_score(a_score);
}

Move* Computer::play() {
	cout << "Computer is playing!" << endl;
}
