#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <utility>

#include "Card.h"
#include "Player.h"
#include "Move.h"

using namespace std;

class Computer: public Player {

	public:
		/*
		Function Name: Computer
		Purpose: Default constructor for Computer class.
		Parameters: None
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Computer();

		/*
		Function Name: Computer
		Purpose: Overloaded constructor for Computer class; used for deserialization
		Parameters: 
			int a_score, value used to set player's score.
		Return Value: None
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		Computer(int a_score);

		/*
		Function Name: play
		Purpose: Calls the AI function from the Player parent class
		Parameters: None
		Return Value: A pair object containing the Card selected to play by the AI, as well as the best move to make with that card.
		Local Variables: None
		Algorithm: None
		Assistance Received: None
		*/
		pair<Card*, char> play();	
};

#endif
