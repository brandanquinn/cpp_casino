#include <iostream>
#include <string>

#include "../../model/Deck.h"
#include "../../model/Card.h"

using namespace std;

int main() {
	Deck test = Deck();

	cout << "Deck created" << endl;
	test.draw_card();
	test.print_deck();
}
