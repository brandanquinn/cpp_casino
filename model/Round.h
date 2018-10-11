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
#include "Build.h"
#include "../view/Display.h"

class Round {
	private:	
		void deal_hands(vector<Player*> game_players);
		int get_set_value(vector<Card*> card_set);
		void print_vector_cards(vector<Card*> card_list);
		void remove_selected_set(vector<vector<Card*>> &total_sets, vector<Card*> selected_set);
		Build* get_correct_build(Card* my_card);
		int round_num;
		Deck* game_deck;
		Table* game_table;
		vector<Player*> game_players;
		Display* game_view;
	public:
		Round(int a_round_num, vector<Player*> a_game_players);
		Round(int a_round_num, vector<Player*> a_game_players, vector<Card*> a_deck_list, vector<Card*> a_table_cards, vector<Build*> a_current_builds);
		int get_round_num();
		void start_game(bool human_is_first, bool loaded_game);
		void deal_to_table(Table* game_table);
		Table* get_game_table();
		void trail(Card* card_played, Player* game_player);
		bool capture(Card* card_played, Player* game_player);
		bool build(Card* card_selected, Player* game_player);
		vector<Card*> filter_build_options(vector<Card*> available_cards, int played_value, int build_sum); 
		Move* generate_capture_move(Card* card_played, Player* game_player);
		void remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove); 
};	

#endif
