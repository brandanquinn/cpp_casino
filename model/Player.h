#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <utility>

#include "Card.h"
#include "Move.h"
#include "Table.h"

class Player {
	private:
		int score;
		vector<Card*> hand;
		vector<Card*> pile;
		Table* game_table;
		bool is_playing;
		string player_string;
		int assess_capture(Card* card_played);
		int get_set_value(vector<Card*> card_set);
		Move* generate_capture_move(Card* card_played);
		void remove_selected_set(vector<vector<Card*>> &total_sets, vector<Card*> selected_set);
		int assess_builds(Card* card_selected);
		int create_builds(Card* card_selected, Card* card_played, bool extending_build);
		vector<Card*> filter_build_options(vector<Card*> available_cards, int played_value, int build_sum);
		Build* get_correct_build(Card* my_card);
		int get_max_score(vector<int> scores);
		void remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove);
		// Card* selected_for_build;

	public:
		Player();
		virtual pair<Card*, char> play() = 0;
		pair<Card*, char> get_help();
		int get_score();
		void set_score(int a_score);
		void add_to_hand(Card* new_card);
		void add_to_pile(vector<Card*> captured_cards);
		vector<Card*> get_pile();
		void discard(Card* removed_card);
		vector<Card*> get_hand();
		void clear_hand();
		bool hand_is_empty();
		void set_is_playing(bool a_is_playing);
		bool get_is_playing();
		void set_hand(vector<Card*> a_hand);
		void set_pile(vector<Card*> a_pile);
		string get_hand_string();
		string get_pile_string();
		void set_player_string(string a_player_string);
		string get_player_string();
		Table* get_game_table();
		void set_game_table(Table* a_game_table);
		// Card* get_selected_for_build();
		// void set_selected_for_build(Card* card);
		
};

#endif

