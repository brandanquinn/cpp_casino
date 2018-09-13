#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include "Deck.h"
#include "Card.h"

using namespace std;

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
 */
Deck::Deck() {
	// Iterate through deck and initialize cards.
	// Deck made up of 4 suits: 'S' (spades), 'C' (clubs), 'H' (hearts), 'D' (diamonds)
	// Each suit has types '2-9', 'X for 10', 'J, Q, K, A'
	char suits[4] = {'S', 'C', 'H', 'D'};
	char types[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
	Card card_list[52];


	for (int i = 0; i < 52; i++) {
		card_list[i] = Card(suits[i/13], types[i%13]);
		game_deck[i] = &card_list[i];
	}

	shuffle_deck();
	print_deck();
	this->top_of_deck = this->game_deck[0];
}

/*
 * Function Name: Deck(string pre_loaded_deck)
 * Purpose: Overloaded constructor for Deck class; will be used to generate a serialized deck.
 * Params: string pre_loaded_deck
 * Return: None
 */
/*Deck::Deck(string pre_loaded_deck) {

}*/

/*
 * Function Name: draw_card()
 * Purpose: Will draw a card off the top of the deck.
 * Params: None
 * Return: None
 */
void Deck::draw_card() {
	cout << "Card drawn: " << this->top_of_deck->get_card_string() << endl;
	this->top_of_deck++;		
}

/*
 * Function Name: shuffle_deck()
 * Purpose: Shuffles the deck of cards.
 * Params: None
 * Local Variables:
 * Algo:
 * Return: None
 */
void Deck::shuffle_deck() {
	srand(time(NULL));
	random_shuffle(&this->game_deck[0], &this->game_deck[51]);		
}

// Iterate through deck and print each card using get_card_string()
void Deck::print_deck() {
	for (int i = 0; i < 52; i++) {
		cout << i << ": " <<  this->game_deck[i]->get_card_string() << endl;
	}
}
