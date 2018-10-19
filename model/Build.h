#ifndef BUILD_H
#define BUILD_H

#include <string>
#include <vector>

#include "Card.h"

using namespace std;

class Build {
		
	public:
		/*
		Function Name: Build
		Purpose: Constructor for Build class.
		Parameters: 
			vector<Card*> a_build_cards, A vector of cards included in the build.
			int a_sum, The value that the cards in the build sum to.
			Card* a_sum_card, The card that the build is locked to; capture card.
			string a_build_owner, String indicating which player owns the build.
		Return Value: None
		Local variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Build(vector<Card*> a_build_cards, int a_sum, Card* a_sum_card, string a_build_owner);
		
		/*
		Function Name: Build
		Purpose: Constructor for Build class; used in deserialization to load in preset multi-builds.
		Parameters: 
			vector<vector<Card*>> a_multi_build_cards, 2d vector of cards included in multi-build.
			int a_sum, The value that the cards in the build sum to.
			Card* a_sum_card, The card that the build is locked to; capture card.
			string a_build_owner, String indicating which player owns the build.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Build(vector<vector<Card*>> a_multi_build_cards, int a_sum, Card* a_sum_card, string a_build_owner);
	
		/*
		Function Name: get_multi_build
		Purpose: Getter for multi_build private member variable
		Parameters: None
		Return Value: Whether or not the Build object is a multi-build, as a boolean.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		bool get_multi_build();
	
		/*
		Function Name: set_multi_build
		Purpose: Setter for multi_build private member variable
		Parameters: 
			bool a_multi_build, Boolean variable representing whether or not the Build object is a multi-build
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_multi_build(bool a_multi_build);
		
		/*
		Function Name: get_sum
		Purpose: Getter for sum private member variable
		Parameters: None
		Return Value: The integer value that the build sums to.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		int get_sum();
	
		/*
		Function Name: set_sum
		Purpose: Setter for sum private member variable
		Parameters: 
			int a_sum, Value representing the integer value that the build sums to.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_sum(int a_sum);
	
		/*
		Function Name: get_sum_card
		Purpose: Getter for the private member variable
		Parameters: None
		Return Value: The card that the build is locked to; capture card represented by a Card obj pointer.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Card* get_sum_card();
	
		/*
		Function Name: set_sum_card
		Purpose: Setter for the sum_card private member variable
		Parameters: 
			Card* a_sum_card, The card that the build is locked to; capture card.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_sum_card(Card* a_sum_card);
	
		/*
		Function Name: get_total_build_cards
		Purpose: Getter for total_build_cards private member variable.
		Parameters: None
		Return Value: The total 2d vector of cards included in the build.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<vector<Card*>> get_total_build_cards();
	
		/*
		Function Name: extend_build
		Purpose: Used to extend a single build object to a multi-build.
		Parameters: 
			vector<Card*> build_cards, A vector of new cards to extend the build with.
		Return Value: None
		Local Variables: None
		Algorithm: 
			1. Add new build cards to 2d vector of total build cards.
			2. Set multi build member variable to true.
		Assistance Received: None
		*/
		void extend_build(vector<Card*> build_cards);
	
		/*
		Function Name: get_build_owner
		Purpose: Getter for build_owner private member variable
		Parameters: None
		Return Value: The build objects owner represented as a string (Human / Computer)
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		string get_build_owner();
	
		/*
		Function Name: set_build_owner
		Purpose: Setter for build_owner private member variable
		Parameters: The build objects owner represented as a string
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_build_owner(string a_build_owner);
	
		/*
		Function Name: get_build_string
		Purpose: Provide a representation of the build object as a string for Serialization.
		Parameters: None
		Return Value: The build object as a string value concatenated with its owner.
		Local Variables: 
			string build_str, string used to concatenate build properties to string format.
		Algorithm:
			1. Initialize build string as empty string.
			2. Iterate through total build cards (2d vector)
				a. If Build object is a multi build, add an open bracket to build string.
			3. Iterate through single vector of build cards
				a. If you are at the beginning of the vector, add an open bracket to build string.
				b. Add each card represented as a string to build string.
			4. Add a closed bracket to build string.
			5. If Build object is a multi build, add a closed bracket to build string.
			6. Return build string concatenated with Build Owner.
		Assistance Received: None
		*/
		string get_build_string();

		/*
		Function Name: get_build_string_for_view
		Purpose: Provide a representation of the build object as a string for Display.
		Parameters: None
		Return Value: The build object as a string value.
		Local Variables: 
			string build_str, string used to concatenate build properties to string format.
		Algorithm:
			1. Initialize build string as empty string.
			2. Iterate through total build cards (2d vector)
				a. If Build object is a multi build, add an open bracket to build string.
			3. Iterate through single vector of build cards
				a. If you are at the beginning of the vector, add an open bracket to build string.
				b. Add each card represented as a string to build string.
			4. Add a closed bracket to build string.
			5. If Build object is a multi build, add a closed bracket to build string.
			6. Return build string
		Assistance Received: None
		*/
		string get_build_string_for_view();

	private:
		bool multi_build;
		int sum;
		Card* sum_card;
		vector<vector<Card*>> total_build_cards;
		string build_owner;
};

#endif
