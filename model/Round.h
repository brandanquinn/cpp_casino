#ifndef ROUND_H
#define ROUND_H

#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"

class Round {
	private:	
		void start_game();
		void deal_hands(Player* game_players[2]);
		int round_num;
		Deck* game_deck;
	public:
		Round(int a_round_num);
		int get_round_num();

};	

#endif
