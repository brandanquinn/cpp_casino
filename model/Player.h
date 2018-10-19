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

		/*
		Function Name: set_pile
		Purpose: Setter for pile private member variable, used in serialization
		Parameters: 
			vector<Card*> a_pile, vector of cards to set pile to.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_pile(vector<Card*> a_pile);

		/*
		Function Name: get_hand_string
		Purpose: Generates a string representation of the player's hand for serialization.
		Parameters: None
		Return Value: Returns the player's hand as a string.
		Local Variables: 
			string hand_str, String to hold the card strings in player's hand.
		Algorithm: 
			1. Initialize hand_str to empty string.
			2. For each card in player's hand
				a. Add the card string and a space to hand_str
			3. Return hand_str
		Assistance Received: None
		*/
		string get_hand_string();

		/*
		Function Name: get_pile_string
		Purpose: Generates a string representation of the player's pile.
		Parameters: None
		Return Value: Returns the player's pile as a string.
		Local Variables:
			string pile_str, String to hold the card strings in player's pile.
		Algorithm: 
			1. Initialize pile_str to empty string.
			2. For each card in player's pile
				a. Add the card string and a space to pile_str
			3. Return pile_str
		Assistance Received: None
		*/
		string get_pile_string();

		/*
		Function Name: set_player_string
		Purpose: Setter for player_string private member variable
		Parameters: 
			string a_player_string, String to keep track of whether player is Human or Computer.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_player_string(string a_player_string);

		/*
		Function Name: get_player_string
		Purpose: Getter for player_string private member variable
		Parameters: None
		Return Value: Returns a string to keep track of whether player is Human or Computer.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		string get_player_string();

		/*
		Function Name: get_game_table
		Purpose: Getter for game_table private member variable.
		Parameters: None
		Return Value: Returns a pointer to the current game table.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Table* get_game_table();

		/*
		Function Name: set_game_table
		Purpose: Setter for game_table private member variable
		Parameters: 
			Table* a_game_table, Pointer to the current game table object.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None 
		*/
		void set_game_table(Table* a_game_table);

		/*
		Function Name: get_captured_last
		Purpose: Getter for captured_last private member variable
		Parameters: None
		Return Value: Boolean value to determine which player captured last.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		bool get_captured_last();

		/*
		Function Name: set_captured_last
		Purpose: Setter for captured_last private member variable
		Parameters: 
			bool a_captured_last, Boolean value to set captured_last to.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None 
		*/
		void set_captured_last(bool a_captured_last);

	private:
		int score;
		vector<Card*> hand;
		vector<Card*> pile;
		Table* game_table;
		bool is_playing;
		string player_string;
		bool captured_last;

		/*
		Function Name: assess_capture
		Purpose: Called by get_help to assess the viability / possibility of capture moves to be made.
		Parameters: 
			Card* card_played, pointer to the card selected by AI / Player.
		Return Value: An integer heuristic value based on what can be captured with card selected, 0 by default.
		Local Variables: 
			Move* game_move, Move object pointer that contains information regarding what can be captured.
			vector<Card*> capturable_cards, Vector of cards that can be captured with the card selected, pulled from the Move object.
			vector<Card*> pile_additions, Vector of cards that will contain cards captured that will be added to pile.
			vector<vector<Card*>> capturable_sets, 2d vector of card sets that can be captured with card selected.
			vector<Build*> capturable_builds, vector of build objects that can be captured with card selected.
			vector<vector<Card*>> selected_sets, 2d vector that will contain card sets selected for capture.
			int max_set_size, best_set_index, set_selection, Used to find the best capturable sets.
		Algorithm:
			1. Initialize local variables
			2. If there are no capturable cards, sets or builds. Return 0.
			3. While there are capturable sets:
				a. For each set
					i. If the size of that set > max_set_size:
						- Set it as the max set size
						- Update best_set_index
				b. Add best set to selected_sets vector.
				c. Remove selected set and any set containing cards captured from capturable sets vector
			4. Add card played to pile_additions vector
			5. Add capturable cards to pile_additions vector
			6. Add selected sets to pile_additions vector
			7. Add capturable build cards to pile_additions vector.
			8. Return size of the pile_additions vector as the heuristic value.
		Assistance Received: None
		*/
		int assess_capture(Card* card_played);

		/*
		Function Name: get_set_value
		Purpose: Sums the value of each card in the set to get its total value.
		Parameters: 
			vector<Card*> card_set, Vector of cards representing a set.
		Return Value: Returns the sum value of each card in the set. 
		Local Variables: 
			int value_sum, integer variable to keep track of the sum value
		Algorithm:
			1. Initialize value_sum to 0
			2. For each card in the set
				a. Add its value to value_sum
			3. Return value_sum
		Assistance Received: None
		*/
		int get_set_value(vector<Card*> card_set);

		/*
		Function Name: generate_capture_move
		Purpose: Generates a move object that contains capturable cards, sets, and builds for the card selected.
		Parameters: 
			Card* card_played, card selected by AI / player to be evaluated.
		Return Value: A move object containing everything that can be captured.
		Local Variables: 
			vector<Build*> capturable_builds, Vector that will contain builds that can be captured
			vector<Build*> current_builds, Vector containing all builds on the table.
			int played_value, value of card played - used for set capturing info
			vector<Card*> avail_cards, Vector containing loose cards on the table.
			vector<Card*> capturable_cards, vector that will contain cards that can be captured.
			vector<vector<Card*>> avail_sets, 2d vector that will contain all sets on the table.
			vector<Card*> empty, Vector representing the empty set for the power set algorithm.
			vector<vector<Card*>> temp_sets, Temporary 2d vector used in algorithm
			vector<vector<Card*>> capturable_sets, 2d vector that will contain sets that total to played_value
		Algorithm:
			(General Algorithm)
			1. Initialize local variables
			2. For each build in current_builds:
				a. If the card selected is the capture card for that build
				or
				Player does not own the build and they have a viabe capture card.
					i. Add the build to capturable_builds vector.
			3. For each loose card on the table:
				a. If the card has the same value as card selected for play
					i. Add the card to capturable_cards vector.
			4. Generate capturable sets using (Set Capture Algorithm)
			5. Return move object containing card played, as well as everything that can be 
			
			(Set Capture Algorithm)
			1. Initialize local variables
			2. Add the empty set to avail_sets
			3. For each loose card on the table:
				a. Create a temp 2d vector copied from avail_sets
				b. For each set in temp_sets:
					i. Add card from table to set
				c. For each set in temp_sets:
					i. Add set to avail_sets.
			4. For each set in avail_sets:
				a. If set value == played_value and set size > 1
					i. Add set to capturable_sets
		Assistance Received: 
		*/
		Move* generate_capture_move(Card* card_played);

		/*
		Function Name: remove_selected_set
		Purpose: Remove a set from vector of sets
		Parameters: 
			vector<vector<Card*>> &total_sets, 2d vector of sets
			vector<Card*> selected_set, set of cards to be removed
		Return Value: None
		Local Variables: None
		Algorithm: 
			1. For each card in selected_set:
				a. For each set in total_sets:
					i. If the card exists in the set, remove the set from total_sets
		Assistance Received: None
		*/
		void remove_selected_set(vector<vector<Card*>> &total_sets, vector<Card*> selected_set);

		/*
		Function Name: assess_builds
		Purpose: Evaluating the heuristic value of possible builds and returning it to the AI
		Parameters:
			Card* card_selected, Pointer to the card selected as the capture card for the build.
		Return Value: Returns the heuristic value evaluated.
		Local Variables: 
			int selected_value, value of the card selected
			vector<int> possible_build_vals, vector to keep track of heuristic values for each build option.
		Algorithm: 
			1. Initialize local variables
			2. If card_selected is currently locked to a build
				a. For each card in your hand:
					i. Evaluate build heuristics of extending build.
			3. Else
				a. For each card in your hand:
					i. Evaluate build heuristics of creating new build.
			4. Return maximum heuristic value in possible_build_vals
		Assistance Received: None
		*/
		int assess_builds(Card* card_selected);

		/*
		Function Name: create_builds
		Purpose: Called by assess_builds() to create the possible builds and evaluate heuristics
		Parameters: 
			Card* card_selected, Pointer to card selected by AI
			Card* card_played, Pointer to card played into build from hand
			bool extending_build, Boolean to track whether or not AI is extending build.
		Return Value: Integer heuristic value based on build size / value.
		Local Variables: 
			int selected_value, value of card selected by AI
			vector<Card*> table_cards, vector of loose table cards
			vector<Card*> filtered_cards, filtered vector to keep track of cards that can be built with
			int played_value, value of card played from hand
			bool build_created, Boolean value to keep track of whether or not build was created
			vector<Card*> build_cards, vector of cards included in build
			int best_card_selection, min_value, used to select the best cards to evaluate for build options
			Build* b1, Build object pointer used for extending a current build
			vector<vector<Card*>> temp_build_cards, used to evauate heuristic value or multi-build
		Algorithm: 
			1. Initialize local variables
			2. If card selected to play has value >= selected_value, return 0
			3. Add card played to build_cards vector
			4. While build is not created:
				a. Filter out table cards that cannot be used in the build.
				b. If no cards exist after filtering, return 0
				c. For each card in filtered_cards:
					i. If card can be used to create a build, save the index and break
					i. If card's value < min value
						- Save index
						- Set min value to card's value.
				d. Add selected card to build_cards vector
				e. Remove selected card from filtered_cards vector.
				f. If build_cards sum value == selected_value and !extending_build
					i. Return size of build_cards as heuristic value
				g. Else if build_cards sum value == selected_value and extending_build
					i. Return size of multi_build as heuristic value
		Assistance Received: None
		*/
		int create_builds(Card* card_selected, Card* card_played, bool extending_build);
		
		/*
		Function Name: filter_build_options
		Purpose: Filter cards out of a vector that cannot be used in build
		Parameters: 
			vector<Card*> available_cards, Vector of total cards on the table.
			int played_value, Value of card played into build
			int build_sum, Value of card selected as capture card.
		Return Value: Returns filtered vector of cards
		Local Variables: 
			vector<Card*> filtered_options, Vector to track filtered cards
		Algorithm: 
			1. Initialize filtered_options
			2. For each card in available card vector:
				a. If card value + played_value <= build_sum:
					i. Add card to filtered_options
			3. Return filtered_options
		Assistance Received: None
		*/
		vector<Card*> filter_build_options(vector<Card*> available_cards, int played_value, int build_sum);
		
		/*
		Function Name: get_correct_build
		Purpose: Find a Build object that a certain card is locked to.
		Parameters: 
			Card* my_card, Pointer to card being searched for.
		Return Value: Build object containing my_card, NULL if build not found.
		Local Variables: 
			vector<Build*> total_builds, Vector of all current builds
		Algorithm: 
			1. Initialize total_builds
			2. For each build in total builds:
				a. If Build's capture card_string == query card_string
					i. Return Build
			3. Return NULL
		Assistance Received: None
		*/
		Build* get_correct_build(Card* my_card);

		/*
		Function Name: get_max_score
		Purpose: Find index of maximum heuristic value
		Parameters: 
			vector<int> scores, Vector of heuristic values
		Return Value: Index of max value as an integer
		Local Variables: 
			int max_val, max_index, to keep track of maximums
		Algorithm: 
			1. Initialize local variables
			2. For each value in scores:
				a. If value > max_val
					i. Set max_val to value
					ii. Set max_index to current index
			3. Return max_index
		Assistance Received: None
		*/
		int get_max_score(vector<int> scores);

		/*
		Function Name: remove_card_from_vector
		Purpose: Remove a specific card from a given vector of cards
		Parameters: 
			vector<Card*> &card_list, Vector of cards
			Card* card_to_remove, Card to be removed from vector
		Return Value: None
		Local Variables: None
		Algorithm: 
			1. Call remove() to get index of card_to_remove in vector
			2. Erase() index from vector.
		Assistance Received: None
		*/
		void remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove);		
};

#endif

