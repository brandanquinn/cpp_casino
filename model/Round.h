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

	public:
		/*
		Function Name: Round
		Purpose: Constructor for Round class
		Parameters: 
			int a_round_num, current round number
			vector<Player*> a_game_players, vector containing the two pre-intialized game players
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance: None
		*/
		Round(int a_round_num, vector<Player*> a_game_players);

		/*
		Function Name: Round
		Purpose: Constructor for Round class; used in deserialization
		Parameters: 
			int a_round_num, current round number
			vector<Player*> a_game_players, vector containing the two pre-intialized game players
			vector<Card*> a_deck_list, pre-built deck to create Deck object
			vector<Card*> a_table_cards, pre-loaded vector of loose table cards
			vector<Build*> a_current_builds, vector of builds on the table
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance: None
		*/
		Round(int a_round_num, vector<Player*> a_game_players, vector<Card*> a_deck_list, vector<Card*> a_table_cards, vector<Build*> a_current_builds);
		
		/*
		Function Name: ~Round
		Purpose: Destructor for Round class
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		~Round();

		/*
		Function Name: get_round_num
		Purpose: Getter for round_num private member variable
		Parameters: 
			int a_round_num, current round number
			vector<Player*> a_game_players, vector containing the two pre-intialized game players
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance: None
		*/
		int get_round_num() const;

		/*
		Function Name: start_game
		Purpose: Starts game play
		Parameters: 
			bool human_is_first, boolean value representing whether or not human is playing first
			bool loaded_game, boolean value representing whether or not game is loading from file
			vector<Card*> deck_list, if player selects to load in seeded deck - round will create and use a new deck with this vector of cards
		Return Value: None
		Local Variables: 
			bool possible_move_selected, keep track of whether or not to possible move has been selected by player
			Player* player_one, player_two, pointers to easily keep track of game players
		Algorithm: 
			1. If player chose to start new game
				a. Deal cards to hands and table
			2. Initialize local variables
			3. If human is going first:
				a. Set player_one to human, player_two to computer
			4. Else:
				a. Set player_two to human, player_one to computer
			5. Update view
			6. While deck isn't empty and hands aren't empty:
				a. If players hand are empty and deck is empty:
					i. Deal cards to players
					ii. Update view
				b. While possible move has not been selected and player_one has cards in hand:
					i. Get move_pair from player_one's play function
						- If player_one is a Computer: 
					 		- Make move based on AI move selection
						- Else
							- Make move based on Player's input
				c. Set player is playing accordingly.
				d. Update view
				e. While possible move has not been selected and player_two has cards in hand:
					i. Get move_pair from player_two's play function
						- If player_two is a Computer: 
					 		- Make move based on AI move selection
						- Else
							- Make move based on Player's input
				f. Set player is playing accordingly.
				g. Update view
			7. If player_one captured last
				a. Add loose cards on table to player_one's pile
			8. Else if player_two captured last
				a. Add loose cards on table to player_two's pile
		Assistance: None
		*/
		void start_game(bool human_is_first, bool loaded_game, vector<Card*> deck_list);

		/*
		Function Name: deal_to_table
		Purpose: Draw cards from deck and add them to the table.
		Parameters: 
			Table* game_table, Table object pointer to be dealt to.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance: None
		*/		
		void deal_to_table(Table* game_table);

		/*
		Function Name: get_game_table
		Purpose: Getter for game_table private member function
		Parameters: None
		Return Value: Table object pointer
		Local Variables: None
		Algorithm: None
		Assistance: None
		*/	
		Table* get_game_table() const;

		/*
		Function Name: trail
		Purpose: Properly make a trail move
		Parameters: 
			Card* card_played, Card selected to trail
			Player* game_player, Player making the trail move.
		Return Value: Returns true if move is successfully made, false otherwise
		Local Variables: None
		Algorithm: 
			1. If card_played is locked to a build
				a. Print error message, return false.
			2. For each card in player's hand:
				a. If a capture or build can be made with card
					i. Return false
			3. Discard card played from player's hand
			4. Add card played to table cards
			5. Set player is_playing to false
			6. Return true
		Assistance: None
		*/	
		bool trail(Card* card_played, Player* game_player);

		/*
		Function Name: capture
		Purpose: Properly make capture move
		Parameters: 
			Card* card_played, Card selected to capture with
			Player* game_Player, Player making the trail move
		Return Value: Returns true is move is successfully made, false otherwise
		Local Variables:
			Move* game_move, Move object pointer that contains information regarding what can be captured.
			vector<Card*> capturable_cards, Vector of cards that can be captured with the card selected, pulled from the Move object.
			vector<Card*> pile_additions, Vector of cards that will contain cards captured that will be added to pile.
			vector<vector<Card*>> capturable_sets, 2d vector of card sets that can be captured with card selected.
			vector<Build*> capturable_builds, vector of build objects that can be captured with card selected.
			vector<vector<Card*>> selected_sets, 2d vector that will contain card sets selected for capture.
		Algorithm: 
			1. Initialize game_move to get capturable_cards, sets and builds
			2. If there is nothing to capture:
				a. Print error message, return false.
			3. If there are capturable builds:
				a. Print builds that can be captured.
				b. Let player choose if they want to capture builds.
					i. If not, return false.
			4. If there are capturable cards:
				a. Print cards that can be captured.
				b. Let player choose if they want to capture cards.
					i. If not, return false.
			5. If there are capturable sets:
				a. Initialize set_selection to -1
				b. While set_selection != 0:
					i. Print sets that can be captured.
					ii. Let player choose which sets they want to capture.
					iii. If set selection is valid
						- add selected set to selected_sets
						- remove selected set from capturable sets
			6. Discard card played from player's hand.
			7. Remove capturable cards from table
			8. Remove selected sets from table
			9. Remove capturable builds from table
			10. Add all captured cards to player's pile
			11. Return true
		Assistance: None
		*/	
		bool capture(Card* card_played, Player* game_player);

		/*
		Function Name: build
		Purpose: Properly make build move
		Parameters: 
			Card* card_selected, Card selected to be played into the build
			Player* game_player, Player currently making move
		Return Value: Returns true if move can be made, false otherwise
		Local Variables: 
			int selected_value, keeps track of value of card_selected
			vector<Card*> player_hand, vector of cards from player hand
			int card_num, value to keep track of card selection input from player
			bool extending_build, Keeps track whether or not player is extending build to multi-build
			Card* card_played, card selected by player to play into a build.
			vector<Card*> table_cards, vector of loose cards on the table
			vector<Card*> filtered_cards, vector to filter out table cards that cannot be used in build
			int played_value, value of card played
			bool build_created, Keeps track of whether or not build has been created
			vector<Card*> build_cards, Vector of cards involved in build
		Algorithm: 
			1. Initialize local variables
			2. If card selected is a capture card
				a. Set extending_build to true
				b. Get input from player as to which card they want to play
			3. Assign that card to card_played pointer
			4. If value of card_played >= selected_value, return false
			5. Get loose table cards and store them into table_cards
				a. Copy table cards vector into filtered_cards
			6. Add card_played to build_cards vector
			7. While build has not been created:
				a. Filter out cards that cannot be used in build
				b. If no cards exist: return false
				c. Have user input card to build with.
				d. Point build_card pointer to selected card
				d. Add build_card to build_cards
				e. Remove selected card from filtered cards
				f. if played_value + build_card value == selected_value and not extending build
					i. Ask user if they want to create build
						- If yes, create build and set necessary things up
							- return true
						- If no, return false
				g. if played_value + build_card value == selected_value and extending build
					i. Ask user if they want to extend build
						- If yes, extend build and set things up
							- return true
						- If no, return false
				h. Recalculate played_value by summing up value of build_cards
		Assistance: None
		*/			
		bool build(Card* card_selected, Player* game_player);

		/*
		Function Name: make_increase
		Purpose: Make the increase build move that AI selected, if player is human - asks them if they want to make move.
		Parameters:
			Card* card_selected, pointer to card selected to increase build with.
			Player* game_player, player making move
		Return Value: Boolean value determining whether or not move can be made.
		Local variables:
			vector<Build*> current_builds, vector of build objects currently on the table
			vector<Card*> player_hand, vector of cards in player's hand
		Algorithm:
			1. Get list of current builds on the table
			2. For each build in filtered list:
				a. If build belongs to opponent:
					i. For each card in player's hand:
						- If Build sum + card_selected value == value of card in your hand:
							- Ask user if they want to make move
								- If yes, update model and return true
			3. Return false
		Assistance Received: None
		*/
		bool make_increase(Card* card_selected, Player* game_player);

		/*
		Function Name: increase_build
		Purpose: Allow user to increase an opponent's build and claim it.
		Parameters:
			Card* card_selected, Pointer to card selected to increase build with.
			Player* game_player, Player making move
		Return Value: Boolean value determining whether or not move can be made.
		Local Variables:
		Algorithm:
			1. Get list of current builds on the table
			2. For each build in filtered list:
				a. If build belongs to opponent:
					i. For each card in player's hand:
						- If Build sum + card_selected value == value of card in your hand:
							- Ask user if they want to make move
								- If yes, update model and return true
			3. Return false
		Assistance Received: None
		*/
		bool increase_build(Card* card_selected, Player* game_player);

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
		Move* generate_capture_move(Card* card_played, Player* game_player);
		
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

	private:

		/*
		Function Name: deal_hands
		Purpose: Draw cards from deck and deal them to players properly.
		Parameters: 
			vector<Player*> game_players, Players of the game
		Return Value: If cards are dealt properly, return true. Returns false otherwise.
		Local Variables: None
		Algorithm: 
			1. Deal 4 cards to Human
				a. If card dealt is not a real card, return false.
			2. Deal 4 cards to Computer
				a. If card dealt is not a real card return false.
			3. Return true
		Assistance: None
		*/
		bool deal_hands(vector<Player*> game_players);

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
		int get_set_value(vector<Card*> card_set) const;

		/*
		Function Name: print_vector_cards
		Purpose: Print out a vector of card strings
		Parameters: 
			vector<Card*> card_list, Vector of cards
		Return Value: None
		Local Variables: None
		Algorithm: 
			1. For each card in the card_list:
				a. Print the card string
		Assistance Received:
		*/
		void print_vector_cards(vector<Card*> card_list);

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
		Build* get_correct_build(Card* my_card) const;
		int round_num;
		Deck* game_deck;
		Table* game_table;
		vector<Player*> game_players;
		Display* game_view;
		/*
		Function Name: save_game
		Purpose: Save the current game state to a text file.
		Parameters: None
		Return Value: Boolean value determining whether or not the save completed
		Local Variables:
			const char *file_name, Exact file path that the game will be saved to
			ofstream save_file, Output stream to save file
			string next_player, Used to write who is playing next to save file
		Algorithm:
			1. Initialize local variables
			2. If save file is open:
				a. Write stringified game info to save file
			3. Return true
		Assistance Received: None
		*/
		bool save_game();

		/*
		Function Name: get_build_strings
		Purpose: Get a concatenated string of individual build strings to write to save file.
		Parameters: None
		Return Value: String containing all builds on the table with their respective owners.
		Local Variables: 
			string build_strings, String to concatentate - returned by function
			vector<Build*> current_builds, temp vector to hold current build objects
		Algorithm:
			1. Initialize local variables
			2. For each build in current_builds
				a. Add stringified build to build_strings
			3. Return build_strings
		Assistance Received: None
		*/
		string get_build_strings() const;

		/*
		Function Name: make_move
		Purpose: Handles Making the move the AI decided upon and updates the model accordingly.
		Parameters: 
			char move_type, Character value representing which move will be made
			Card* card_selected, card selected for play by AI
			Player* game_player, player currently making the move
		Return Value: Boolean value determing whether move was made successfully or not.
		Local Variables: None
		Algorithm: 
			1. Explain which move was made by AI, and why.
			2. Call function corresponding to move_type and return its boolean value
			3. Return false
		Assistance Received: None
		*/
		bool make_move(char move_type, Card* card_selected, Player* game_player);
		
		/*
		Function Name: create_build
		Purpose: Generate build move decided upon by AI and update model accordingly
		Parameters: 
			Card* card_selected, capture card determined by AI
			Card* card_played, card to be played into build
			bool extending_build, whether or not player is extending a current build
		Return Value: Boolean value determing whether move was made successfully or not.
		Local Variables:
			vector<Card*> table_cards, Vector of loose table cards
			vector<Card*> filtered_cards, Filtered table cards
			int selected_value, played_value, integer values of cards involved in build
			vector<Card*> build_cards, Vector of cards contained in the build
			Card* build_card, Pointer to keep track of cards added to build
		Algorithm:
			1. Initialize local variables
			2. If card selected to play has value >= selected_value, return 0
			3. Add card played to build_cards vector
			4. While true:
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
					i. Create build object, update model accordingly
					ii. Return true
				g. Else if build_cards sum value == selected_value and extending_build
					i. Extend build object, update model accordingly
					ii. Return true
		Assistance Received: None
		*/
		bool create_build(Card* card_selected, Card* card_played, bool extending_build, Player* game_player, bool making_changes);
		
		/*
		Function Name: make_capture
		Purpose: Make the capture move decided on by the AI and update the model accordingly
		Parameters:
			Card* card_selected, Card selected by AI to capture with
			Player* game_player, Player making move
			bool making_changes, Indicates whether or not model should be updated
			- Used to check if move can be made other than trail.
		Return Value: Boolean value determing whether move was made successfully or not.
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
			2. If there are no capturable cards, sets or builds. Return false.
			3. While there are capturable sets:
				a. For each set
					i. If the size of that set > max_set_size:
						- Set it as the max set size
						- Update best_set_index
				b. Add best set to selected_sets vector.
				c. Remove selected set and any set containing cards captured from capturable sets vector
			4. If making_changes to model:
				a. Update model accordingly
				b. Add card played to pile_additions vector
				c. Add capturable cards to pile_additions vector
				d. Add selected sets to pile_additions vector
				e. Add capturable build cards to pile_additions vector.
				e. Add pile to player making move
			5. Return true
				
		Assistance Received: None
		*/
		bool make_capture(Card* card_selected, Player* game_player, bool making_changes);
		
		/*
		Function Name: make_build
		Purpose: Test build viability for each card that can be played from player's hand
		Parameters:
			Card* card_selected, Pointer to capture card selected
			Player* game_player, Player making move
			bool making_changes, bool making_changes, Indicates whether or not model should be updated
			- Used to check if move can be made other than trail.
		Return Value: Boolean value determing whether move was made successfully or not.
		Local Variables:
			int selected_value, value of card selected
			vector<Card*> player_hand, vector of cards in player's hand
		Algorithm:
			1. Initialize local variables
			2. If card_selected is a capture card already:
				a. For each card in player's hand:
					i. Check if card can be used in a build extension
						- If it can, return true
			3. Else if looking to start a new build with card selected:
				a. For each card in player's hand:
					i. Check if card can be used to play into a build
						- If it can, return true
			4. Return false
		Assistance Received: None
		*/
		bool make_build(Card* card_selected, Player* game_player, bool making_changes);

};	

#endif
