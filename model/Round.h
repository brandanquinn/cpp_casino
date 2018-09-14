#ifndef ROUND_H
#define ROUND_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"

class Round {
	private:	
		void deal_hands(vector<Player*> game_players);
		int round_num;
		Deck* game_deck;
		vector<Player*> game_players;
	public:
		Round(int a_round_num, vector<Player*> a_game_players);
		int get_round_num();
		void start_game();


};	

#endif
