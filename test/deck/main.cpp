#include <iostream>
#include <string>

#include "../../model/Deck.h"
#include "../../model/Card.h"

using namespace std;

int main() {
	Deck game_deck;

	cout << "Deck created" << endl;
	game_deck.draw_card();	
}
