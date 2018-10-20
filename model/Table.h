#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "Card.h"
#include "Build.h"

class Table {

	public:
		/*
		Function Name: Table
		Purpose: Default constructor for Table class
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Table();

		/*
		Function Name: Table
		Purpose: Overloaded constructor for Table class; used in deserialization
		Parameters: 
			vector<Card*> a_table_cards, vector of cards to add to the table
			vector<Build*> a_current_builds, vector of builds on the table
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Table(vector<Card*> a_table_cards, vector<Build*> a_current_builds);

		/*
		Function Name: get_table_cards
		Purpose: Getter for table_cards private member variables
		Parameters: None
		Return Value: Vector of loose table cards
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<Card*> get_table_cards() const;

		/*
		Function Name: get_total_table_cards
		Purpose: Gets a 2d vector of loose table cards and cards from builds
		Parameters: None
		Return Value: 2d vector of ALL table cards
		Local Variables: 
			vector<vector<Card*>> temp_vec, vector to hold all table cards
		Algorithm:
			1. Initialize temp_vec to hold table_build member variable
			2. Add loose table cards to temp_vec
			3. Return temp_vec
		Assistance Received: None
		*/
		vector<vector<Card*>> get_total_table_cards() const;

		/*
		Function Name: add_to_table_cards
		Purpose: Checks whether card is part of a build or not and adds it to proper container
		Parameters:
			Card* new_card, card to be added to table
		Return Value: None
		Local Variables:
			vector<Card*> build_buddies, Vector of cards in a build
		Algorithm: 
			1. If new_card is part of a build:
				a. Get its build_buddies
				b. For each card in build_buddies
					i. Remove it from loose table cards vector
				c. If build_buddies aren't part of a build on the table
					a. Add them to known table builds
			2. Else
				a. Add new_card to loose table cards.
		Assistance Received: None
		*/
		void add_to_table_cards(Card* new_card);

		/*
		Function Name: clear_table_cards
		Purpose: Remove loose cards from table
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: Clear table cards vector
		Assistance Received: None
		*/
		void clear_table_cards();

		/*
		Function Name: remove_cards
		Purpose: Remove cards from loose table cards vector
		Parameters:
			vector<Card*> cards_to_remove, Card to remove from table
		Return Value: None
		Local Variables: None
		Algorithm: 
			1. For each card in cards_to_remove:
				a. Remove card from loose table cards vector
		Assistance Received: None
		*/
		void remove_cards(vector<Card*> cards_to_remove);

		/*
		Function Name: remove_sets
		Purpose: Remove sets of cards from loose table cards vector
		Parameters: 
			vector<vector<Card*>> sets_to_remove, sets to remove from table
		Return Value: None
		Local Variables: None
		Algorithm: 
			1. For each set to remove:
				a. Call remove_cards(set)
		Assistance Received: None
		*/
		void remove_sets(vector<vector<Card*>> sets_to_remove);

		/*
		Function Name: remove_builds
		Purpose: Remove captured builds from table
		Parameters: 
			vector<Build*> builds_to_remove, builds from remove from table
		Return Value: None
		Local Variables: 
			vector<vector<Card*> temp_build_cards, temp 2d vec to hold build cards
		Algorithm: 
			1. For each build to remove:
				a. Get total build cards
				b. For each vector of cards in total build cards:
					i. Remove card from table_builds
			2. For each build to remove:
				a. Delete build object from current_builds vector
		Assistance Received: None
		*/
		void remove_builds(vector<Build*> builds_to_remove);

		/*
		Function Name: is_empty
		Purpose: Check if there are no loose table cards
		Parameters: None
		Return Value: Boolean value that represents whether or not there are loose table cards.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		bool is_empty();

		/*
		Function Name: add_build
		Purpose: Add new build to current_builds vector
		Parameters: 
			Build* new_build, pointer to new build object
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void add_build(Build* new_build);

		/*
		Function Name: get_current_builds
		Purpose: Getter for current_builds private member variable
		Parameters: None
		Return Value: Vector of current builds on table
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<Build*> get_current_builds() const;

		/*
		Function Name: get_flattened_card_list
		Purpose: Generates a single vector of all cards on the table
		Parameters: None
		Return Value: Vector of ALL table cards
		Local Variables: 
			vector<Card*> flat_list, Vector of all table cards to be returned
		Algorithm:
			1. Initialize flat_list
			2. For each set of cards in table_builds:
				a. For each card in the set:
					i. Add card to flat_list
			3. For each loose card on the table
				a. Add card to flat_list
			4. Return flat_list
		Assistance Received: None
		*/
		vector<Card*> get_flattened_card_list();

		/*
		Function Name: is_part_of_multi_build
		Purpose: To get whether a card is currently part of a multi-build on the table
		Parameters: 
			Card* my_card, card in question
		Return Value: Boolean value determining whether or not my_card is part of a multi-build
		Local Variables:
			vector<vector<Card*>> temp_build_cards, 2d vector to hold ALL build cards
		Algorithm:
			1. For each build in current_builds:
				a. Get total build cards
				b. If my_card is in total build cards:
					i. If temp_build_cards size > 1
						- Return true
					ii. Else:
						- Return false
			2. Return false
		Assistance Received: None
		*/
		bool is_part_of_multi_build(Card* my_card);

		/*
		Function Name: get_size_of_multi_build
		Purpose: Given a card, if that card is in a multi-build return size of that build
		Parameters: 
			Card* my_card, card in question
		Return Value: Size of multi-build, 0 if not in multi-build
		Local Variables:
			int count, variable to keep count of size of multi-build 
			vector<vector<Card*>> temp_build_cards, 2d vector to hold ALL build cards
		Algorithm:
			1. Initialize count to 0
			2. For each build in current_builds vector
				a. Get total build cards
				b. If my_card is in total build cards
					i. Get total # of cards in total build cards
			3. Return count
		Assistance Received:
		*/
		int get_size_of_multi_build(Card* my_card);

		/*
		Function Name: get_size_of_single_build
		Purpose: Given a card, if that card is in a build return size of build
		Parameters:
			Card* my_card, card in question
		Return Value: Size of single build that card is in, 0 if not in build
		Local Variables: 
			vector<vector<Card*>> temp_build_cards, 2d vector to hold ALL build cards
		Algorithm:
			1. For each build in current_builds vector
				a. Get total build cards
				b. For each set of cards in total build cards
					i. If my_card is in that set:
						- Return size of set
			2. Return 0
		Assistance Received: None
		*/
		int get_size_of_single_build(Card* my_card);

		/*
		Function Name: get_table_string
		Purpose: Generate a stringified table
		Parameters: None
		Return Value: String containing cards and builds on table
		Local Variables: 
			vector<Card*> table_card_list, vector of ALL cards on table
			int mb_size, build_size, used to keep track of build sizes to display brackets properly
			bool in_mb, in_build, used to create stringified builds properly
			string table_str, string to generate and return stringified table
		Algorithm:
			1. Initialize local variables
			2. For each card in table_card_list:
				a. If index == mb_size and in_mb is true:
					i. Add closing bracket to table_str
					ii. Set in_mb to false
				b. If index == build_size and in_build is true:
					i. Add closing bracket to table_str
					ii. Set in_build to false
				c. If card is part of a multi-build and in_mb is false:
					i. Set in_mb to true
					ii. Compute mb_size
					iii. Add open bracket to table_str
				d. If card is part of build and in_build is false:
					i. Set in_build tot rue
					ii. Compute build_size
					iii. Add open bracket to table_str
				e. Add card string to table_str
			3. Return table_str
		Assistance Received: None
		*/
		string get_table_string();

	private:
		vector<vector<Card*>> total_table_cards;
		vector<Card*> table_cards;	
		vector<vector<Card*>> table_builds;			
		vector<Build*> current_builds;

		/*
		Function Name: remove_card_from_vector
		Purpose: Remove a single card from a vector
		Parameters: 
			vector<Card*> &card_list, vector to remove card from
			Card* card_to_remove, card to remove from card_list
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void remove_card_from_vector(vector<Card*> &card_list, Card* card_to_remove);
		
		/*
		Function Name: does_build_exist
		Purpose: Check if build cards already exist on the table
		Parameters: 
			vector<Card*> build_buddies, Cards in build
		Return Value: Boolean value representing whether or not the build exists ont able
		Local Variables: None
		Algorithm:
			1. For each set of cards in table_builds:
				a. For each card in the set:
					i. For each card in build_buddies:
						- if set card == build_buddies card: return true
			2. Return false
		Assistance Received: None
		*/
		bool does_build_exist(vector<Card*> build_buddies);

		/*
		Function Name: remove_from_table_builds
		Purpose: Remove cards from table builds
		Parameters: 
			vector<Card*> cards_to_remove, Cards to remove from table builds
		Return Value: None
		Local Variables:
			vector<vector<Card*>> builds_to_erase, 2d vector to keep track of sets of cards to be erased
			bool build_erased, keeps track of whether or not the build has been erased
		Algorithm:
			1. Initialize local variables
			2. For each set of cards in table_builds:
				a. For each card in the set:
					i. For each card to remove:
						- If set card == card to remove and !build_erased:
							- Add set to build_to_erase
							- Set build_erased to true
			3. For each build to erase:
				a. Remove build from table_builds
		Assistance Received: None
		*/
		void remove_from_table_builds(vector<Card*> cards_to_remove);

		/*
		Function Name: is_card_in_vector
		Purpose: Check if card is in 2d vector
		Parameters: 
			vector<vector<Card*>> card_lists, 2d vector to check through
			string my_card_string, stringified card to check equality
		Return Value: Boolean value determining whether or not card is in 2d vector
		Local Variables: None
		Algorithm:
			1. For each vector of cards in card_lists
				a. For each card in that vector:
					i. If card string == my_card_string:
					 	- Return true
			2. Return false
		Assistance Received: None
		*/
		bool is_card_in_vector(vector<vector<Card*>>, string my_card_string);

		/*
		Function Name: is_card_in_single_vec
		Purpose: Check if card is in vector
		Parameters:
			vector<Card*> card_list, vector to check through
			string my_card_string, stringified card to check equality
		Return Value: Boolean value determining whether or not card is in vector
		Local Variables: None
		Algorithm: 
			1. For each card in card_list:
				a. If card string == my_card_string:
					i. Return true
			2. Return false
		Assistance Received: None
		*/
		bool is_card_in_single_vec(vector<Card*> card_list, string my_card_string);
};

#endif
