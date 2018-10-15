#include <vector>
#include <iostream>
#include <utility>

#include "Computer.h"
#include "Card.h" 
#include "Move.h"
#include "Table.h"

using namespace std;

Computer::Computer() {
	Player::set_score(0);
	Player::set_player_string("Computer");
}

Computer::Computer(int a_score) {
	Player::set_score(a_score);
	Player::set_player_string("Computer");
}

pair<Card*, char> Computer::play() {
	// AI Priority List
	// 1. Evaluate best possible capture set for each card in hand. Make the move that captures the most cards.
	// 2. If you control a build, try to extend it.
	// 3. Make the first build you can find, if possible. Check possibilities from highest value -> lowest.
	// 4. Trail the card with the lowest value.


	pair<Card*, char> move_pair = Player::get_help();
	
	if (move_pair.second == 'c') {
		cout << "AI decided it could capture the most cards with: " << move_pair.first->get_card_string() << endl;
	}

	return move_pair;
}
