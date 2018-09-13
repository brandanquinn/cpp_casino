#include <iostream>
#include <string>

#include "../../model/Deck.h"
#include "../../model/Card.h"

using namespace std;

int main() {
	Deck test = Deck();

	cout << "Deck created" << endl;
	for (int i = 0; i < 53; i++) {
		test.draw_card();
	}
}
