#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>
#include <utility>

#include "Card.h"
#include "Player.h"

using namespace std;

class Human: public Player {
	
	public:
		/*
		Function Name: Human
		Purpose: Default constructor for Human class
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Human();

		/*
		Function Name: Human
		Purpose: Overloaded constructor for Human class
		Parameters: 
			int a_score, score value to set private member variable.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Human(int a_score);

		/*
		Function Name: play
		Purpose: Get Human's input on what move to make and what card to play.
		Parameters: None
		Return Value: A pair object that contains a pointer to the card selected by player, and a char representing a move selection.
		Local Variables: 
			char move_option, move selected by player
			pair<Card*, char> move_pair, pair returned by function
			vector<Card*> player_hand, vector of cards in Human's hand.
			int card_num, keeps track of human input for card selection
		Algorithm:
			1. Initialize local variables
			2. While user hasn't input viable char for move:
				a. Print message to prompt user input.
				b. Read input to move_option
				c. If move_option does not match accepted inputs, print error message.
			3. Once move_option is set, get card selection input from user
			4. Set move_pair.first to card selected.
			5. Set move_pair.second to move_option char.
			6. Return move_pair
		Assistance Received: None
		*/
		pair<Card*, char> play();

	private:

		/*
		Function Name: get_card_index
		Purpose: Prompt user for index of card selected for play function
		Parameters: 
			char move_type, Used to print proper message for move type
		Return Value: Integer value input by user, validated within function
		Local Variables: 
			int card_num, Used to keep track of user input
		Algorithm:
			1. Initialize local variables
			2. While user hasn't input valid card index
				a. Print message based on move_type
				b. If user inputs invalid index, print error message.
			3. Return card_num - 1 to account for array indexing.
		Assistance Received: None
		*/
		int get_card_index(char move_type);
		
};

#endif
