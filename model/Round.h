#ifndef ROUND_H
#define ROUND_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include "Table.h"
#include "Move.h"
#include "../view/Display.h"

class Round {
	private:	
		void deal_hands(vector<Player*> game_players);
		int round_num;
		Deck* game_deck;
		Table* game_table;
		vector<Player*> game_players;
		Display* game_view;
	public:
		Round(int a_round_num, vector<Player*> a_game_players);
		int get_round_num();
		void start_game();
		void deal_to_table(Table* game_table);
		Table* get_game_table();
		void trail(Card* card_played, Player* game_player);
		bool capture(Card* card_played, Player* game_player);
		Move* generate_capture_move(Card* card_played, Player* game_player);
};	

#endif
