#ifndef DECK_H
#define DECK_H

#include <string>
#include <queue>
#include <vector>

#include "Card.h"

using namespace std;

class Deck {

	public:	
		/*
		* Function Name: Deck()
		* Purpose: Default constructor for Deck class; used to randomly generate a deck of cards. 
		* Will be called at the beginning of every Round.
		* Params: None
		* Local variables: char suits[4] - Array of suits, char types[13] - Array of card types. 
		* Algo: Instead of hard coding the entire 52 card deck, I decided to use a simple for loop
		* that works on the premise that the deck is split evenly into 4 suits and 13 types. To
		* make sure the suits were applied correctly, I found that you could use the division
		* operator to apply suit[0] ('S' or spades) to the first 14 cards because x/13=0 if
		* x < 13. That same logic can be applied to the other suits. I use similar logic for the
		* types array but instead use the modulus operator to incrementally apply types to each
		* card in the deck. 
		* Return: None
		* Assistance: Neel helped me figure out an issue with pointer handling semantics during Card creation. 
		*/
		Deck();

		/*
		* Function Name: Deck(vector<Card*> pre_loaded_deck)
		* Purpose: Overloaded constructor for Deck class; will be used to generate a serialized deck.
		* Params: string pre_loaded_deck
		* Return: None
		*/
		Deck(vector<Card*> pre_loaded_deck);

		/*
 		* Function Name: ~Deck
		* Purpose: Destructor for Deck class. 
 		* Params: None
 		* Returns: None
 		* Local Vars: None
 		* Algo: None
 		* Assistance: None
 		*/
	 	~Deck();

		/*
		* Function Name: draw_card()
		* Purpose: Will draw a card off the top of the deck and return that card to be handled by player.
		* Params: None
		* Local Variables: Card* card_drawn, a pointer to keep track of the card drawn off the top of the deck.
		* Algo: 
			1. If deck is empty: Let user know and return default card.
		* 	2. Create a pointer and pass the address of the top card of the deck.
		* 	3. Print the card drawn to console.
		* 	4. Remove the top card from the deck.
		* 	5. Set the top_of_deck pointer to current top card. 
		* Return: Card * card_drawn - pointer to the Card drawn.
		*/
		Card* draw_card();

		/*
		* Function Name: shuffle_deck()
		* Purpose: Shuffles the deck of cards.
		* Params: None
		* Local Variables:
		* Algo: 
		* 	1. Seed random generator based on time.
		* 	2. Shuffle deck.
		* Return: None
		*/
		void shuffle_deck();

		/*
		Function Name: is_empty
		Purpose: Determines if deck is empty.
		Parameters: None
		Local Variables: None
		Return Value: A boolean value that represents whether or not the game deck is empty.
		Algorithm: None
		*/
		bool is_empty();

		/*
		Function Name: get_num_cards_left
		Purpose: Computes the number of cards left in the deck.
		Parameters: None
		Local Variables: None
		Return Value: The size of the current game deck.
		Algorithm: None
		*/
		int get_num_cards_left() const;

		/*
		Function Name: get_deck_string
		Purpose: Generates a string representation of the game deck.
		Parameters: None
		Local Variables: 
			queue<Card*> game_deck_copy, used to copy the game_deck for manipulation
			string deck_str, string variable used to concatenate the deck string
		Return Value: The string representation of the game deck.
		Algorithm:
			1. Copy the game_deck queue to another variable.
			2. Initialize an empty string variable, deck_str for concatenation.
			3. For each card in the deck:
				a. Add the card string to deck_str.
				b. Pop the card off the game_deck copy.
			4. Return the deck_str
		*/
		string get_deck_string() const;

	private:
		// Array of Card pointers to represent deck.
		queue <Card*> game_deck;
		Card* top_of_deck;	
};

#endif
