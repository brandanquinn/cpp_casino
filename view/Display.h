#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>

#include "../model/Player.h"
#include "../model/Deck.h"
#include "../model/Table.h"

using namespace std;

class Display {
	private:
		void print_cards(vector<Player*> game_players, Table* game_table);
		void print_scores(vector<Player*> game_players);
	public:
		Display();
		void update_view(vector<Player*> game_players, Table* game_table);
		void print_welcome(int round_num);

};

#endif
