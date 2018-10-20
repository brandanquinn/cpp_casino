#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Card.h"
#include "Build.h"

using namespace std;

class Move {

	public:
		/*
		Function Name: Move
		Purpose: Constructor for Move class
		Parameters: 
			Card* a_card_played, pointer for card played by user
			vector<Card*> a_capturable_cards, vector of cards that can be captured by the user
			vector<vector<Card*>> a_capturable_sets, 2d vector containing sets that can be captured by the user
			vector<Build*> a_capturable_builds, vector of builds that can be captured by the user
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Move(Card* a_card_played, vector<Card*> a_capturable_cards, vector<vector<Card*>> a_capturable_sets, vector<Build*> a_capturable_builds);

		/*
 		* Function Name: ~Move
		* Purpose: Destructor for Move class. 
 		* Params: None
 		* Returns: None
 		* Local Vars: None
 		* Algo: None
 		* Assistance: None
 		*/
	 	~Move()

		/*
		Function Name: get_card_played
		Purpose: Getter for card_played private member variable
		Parameters: None
		Return Value: Pointer for card played by user.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Card* get_card_played() const;

		/*
		Function Name: get_capturable_cards
		Purpose: Getter for capturable_cards
		Parameters: None
		Return Value: Vector of capturable cards
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<Card*> get_capturable_cards() const;

		/*
		Function Name: get_capturable_sets
		Purpose: Getter for capturable_sets
		Parameters: None
		Return Value: 2d vector of all capturable sets
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<vector<Card*>> get_capturable_sets() const;

		/*
		Function Name: get_capturable_builds
		Purpose: Getter for capturable_builds
		Parameters: None
		Return Value: Vector of capturable builds
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		vector<Build*> get_capturable_builds() const;
	
	private:
		Card* card_played;
		vector<Card*> capturable_cards;
		vector<vector<Card*>> capturable_sets;
		vector<Build*> capturable_builds;
};

#endif

