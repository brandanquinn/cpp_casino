#include <iostream>
#include <string>

#include "../../model/Deck.h"
#include "../../model/Card.h"

using namespace std;

int main() {
	Deck test = Deck();
	Card* temp_ptr = NULL;

	cout << "Deck created" << endl;
	for (int i = 0; i < 53; i++) {
		temp_ptr = test.draw_card();
		delete temp_ptr;		
	}
}
