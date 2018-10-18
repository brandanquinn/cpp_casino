#ifndef CARD_H
#define CARD_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Card {
	public:
		/*
 		* Function Name: Card
		* Purpose: Default constructor for Card class. 
 		* Params: None
 		* Returns: None
 		* Local Vars: None
 		* Algo: None
 		* Assistance: None
 		*/
		Card();
	
		/*
 		* Function Name: Card
		* Purpose: Overloaded constructor for Card class. 
 		* Params: char a_suit, char a_type
 		* Returns: None
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
 		*/
		Card(char a_suit, char a_type);
	
		/*
 		* Function Name: create_map
 		* Purpose: Generate map to pair card type to integer value.
 		* Params: None
 		* Return Value: None
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
 		*/
		void create_map();
	
		/*
 		* Function Name: get_suit
 		* Purpose: Get the card's suit.
 		* Params: None
 		* Return Value: char suit
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
		*/
		char get_suit();
	
		/*
 		* Function Name: set_suit
 		* Purpose: Set the card's suit.
 		* Params: 
			char a_suit, Suit to set member variable to.
 		* Return Value: None
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
 		*/
		void set_suit(char a_suit);
	
		/*
 		* Function Name: get_type
 		* Purpose: Get the card's type.
 		* Params: None
 		* Return Value: character value representing the value or rank of the playing card.
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
 		*/
		char get_type();
	
		/*
 		* Function Name: set_type
 		* Purpose: Set the card's type.
 		* Params: 
			char a_type, character value representing the value or rank of the playing card.
 		* Return Value: None
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
 		*/
		void set_type(char a_type);
		
		/*
 		* Function Name: get_value
 		* Purpose: Get the card's value.
 		* Params: None
 		* Return Value: Returns the card's value represented as an integer.
 		* Local Variables: None
 		* Algorithm: None
 		* Assistance: None
		*/
		int get_value();
	
		/*
 		* Function Name: set_value
 		* Purpose: Set the value of a card to based on its type / rank.
 		* Params: None
 		* Return Value: None
 		* Local Variables: None
 		* Algorithm: 
			1. Check type_value map to get corresponding value.
 			2. Assign proper value to member variable.
 		* Assistance: None
 		*/
		void set_value();
	
		/*
 		* Function Name: get_card_string
 		* Purpose: Generate string containing suit and type of a card.
 		* Params: None
 		* Return Value: string
 		* Local Variables: card_string, Used to concatenate suit and type of card.
 		* Algo: 
			1. Create string for concatenation
 		* 	2. To add the char member variables using '+' operator, use string() as the
 		* 	 first arg so that compiler knows you want a string not an integer.
 		* 	3. Return string. 
 		* Assistance: None
 		*/
		string get_card_string();
		
		/*
		Function Name: get_locked_to_build
		Purpose: Getter for locked_to_build private member variable.
		Parameters: None
		Return Value: Whether or not the current Card is locked to a build as a capture card, represented as a boolean
		Local Variables: None
		Algorithm: None
		Assistance: None
		*/
		bool get_locked_to_build();
	
		/*
		Function Name: set_locked_to_build
		Purpose: Setter for locked_to_build private member variable
		Parameters:
			bool a_locked_to_build, Whether or not the current Card is locked to a build as a capture card, represented as a boolean
		Return Value: None
		Algorithm: None
		Assistance: None
		*/
		void set_locked_to_build(bool a_locked_to_build);
		
		/*
		Function Name: get_part_of_build
		Purpose: Getter for part_of_build private member variable
		Parameters: None
		Return Value: Whether or not the current Card is part of a build, represented as a boolean.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		bool get_part_of_build();
		
		/*
		Function Name: set_part_of_build
		Purpose: Setter for part_of_build private member variable.
		Parameters:
			bool a_part_of_build, Whether or not the current Card is part of a build, represented as a boolean.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_part_of_build(bool a_part_of_build);
	
		/*
		Function Name: get_build_buddies
		Purpose: Getter for build_buddies private member variable
		Parameters: None
		Return Value: If card is part of a build, contains the cards that are in that build.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<Card*> get_build_buddies();
	
		/*
		Function Name: set_build_buddies
		Purpose: Setter for build_buddies private member variable
		Parameters: 
			vector<Card*> a_build_buddies, If card is part of a build, contains the cards that are in that build.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		void set_build_buddies(vector<Card*> a_build_buddies);
	
	private:
		char suit;
		char type;
		int value;
		unordered_map<char, int> type_value_pairs;	
		bool locked_to_build;
		bool part_of_build;
		vector<Card*> build_buddies;
};

#endif
