#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <utility>

#include "Card.h"
#include "Move.h"
#include "Table.h"

class Player {

	public:
		/*
		Function Name: Player
		Purpose: Default constructor for Player class
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Player();

		/*
		Function Name: play
		Purpose: Virtual function defined in Human / Computer classes.
		Parameters: None
		Return Value: Returns a pair object containing card selected by Player and char move type.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		virtual pair<Card*, char> play() = 0;

		/*
		Function Name: get_help
		Purpose: AI function called by both Human / Computer to get optimal moves.
		Parameters: None
		Return Value: Returns a pair object containing card selected by AI and move selected as a char
		Local Variables: 
			pair<Card*, char> move_pair, Keep track of card / move selected - returned by function
			int max_build_index, max_capture_index, Variables that keep track of indices of maximum values in move option vectors
			vector<int> build_values, capture_values, Vectors that keep track of possible moves and what heuristic values can be attained with each move
			int min_val, min_index, Variables to keep track of minimum card index in hand for trailing
		Algorithm:
			1. Initialize local variables
			2. For each card in player hand:
				a. Compute heuristic values for possible builds and add them to build_values vector
			3. Find index of max value in build_values
			4. If the max value of build is 0
				a. For each card in player hand:
					i. Compute heuristic values for possible captures and add them to capture_values vector
				b. Find index of max value in capture_values
				c. If max value of capture is 0
					i. Create move_pair with minimum value card and trail char
				d. If max value of capture > 0
					i. Create move_pair with max heuristic card and capture char
			5. If max value of build > 0
				a. Create move_pair with max heuristic card and build char
			6. Return move_pair
		Assistance Received: None
		*/
		pair<Card*, char> get_help();

		/*
		Function Name: get_score
		Purpose: Getter for score private member variable
		Parameters: None
		Return Value: Integer value representing player score
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		int get_score();

		/*
		Function Name: set_score
		Purpose: Setter for score private member variable
		Parameters: 
			int a_score, Variable to set score to
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_score(int a_score);

		/*
		Function Name: add_to_hand
		Purpose: Adds a new card to player's hand
		Parameters: 
			Card* new_card, card obj pointer to add to hand private member variable.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void add_to_hand(Card* new_card);

		/*
		Function Name: add_to_pile
		Purpose: Adds captured cards to player pile
		Parameters: 
			vector<Card*> captured_cards, Cards captured by player to be added to their pile
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void add_to_pile(vector<Card*> captured_cards);

		/*
		Function Name: get_pile
		Purpose: Getter for pile private member variable
		Parameters: None
		Return Value: vector of cards in the player's current pile
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<Card*> get_pile();

		/*
		Function Name: discard
		Purpose: Discard selected card from player's hand
		Parameters:
			Card* removed_card, Card played in move to be removed from hand in model.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void discard(Card* removed_card);

		/*
		Function Name: get_hand
		Purpose: Getter for hand private member variable
		Parameters: None
		Return Value: vector of cards in player's hand 
		Local Variables: None
		Algorithm: 
			1. Use the remove() function to get the index of the card to remove
			2. Use erase() to remove card at said index from the vector
		Assistance Received: None
		*/
		vector<Card*> get_hand();

		/*
		Function Name: clear_hand
		Purpose: Clears all cards from player's hand.
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void clear_hand();

		/*
		Function Name: clear_pile
		Purpose: Clears all cards from player's pile
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void clear_pile();

		/*
		Function Name: hand_is_empty
		Purpose: Used to check if player's hand is currently empty for round ending state / drawing purposes
		Parameters: None
		Return Value: Whether or not the players hand is empty represented as a boolean value.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		bool hand_is_empty();

		/*
		Function Name: set_is_playing
		Purpose: Setter for is_playing private member variable
		Parameters: 
			bool a_is_playing, Boolean value representing whether player is currently playing or not.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_is_playing(bool a_is_playing);

		/*
		Function Name: get_is_playing
		Purpose: Getter for is_playing private member variable
		Parameters: None
		Return Value: Boolean value representing whether player is currently playing or not.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		bool get_is_playing();

		/*
		Function Name: set_hand
		Purpose: Setter for hand private member variable, used in serialization
		Parameters: 
			vector<Card*> a_hand, vector of cards to set hand to.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
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
		
};

#endif

