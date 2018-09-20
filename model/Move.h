#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Card.h"

using namespace std;

class Move {
	private:
		Card* card_played;
		char move_player;
		char move_type;	
	public:
		Move(Card* a_card_played, char a_move_player, char a_move_type);
		Card* get_card_played();
		char get_move_player();
		char get_move_type();
};

#endif

