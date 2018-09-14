#include <iostream>
#include <string>

#include "Round.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include "Card.h"

using namespace std;

Round::Round(int a_round_num) {
	this->round_num = a_round_num;
	game_deck = new Deck;
	start_game();
}

int Round::get_round_num() {
	return this->round_num;
}

void Round::start_game() {
	Player* game_players[2];
	game_players[0] = new Human("Brandan");
	game_players[1] = new Computer;
	Deck* game_deck = new Deck;
	deal_hands(game_players);

	game_players[0]->play();
	game_players[1]->play();		
}

void Round::deal_hands(Player* game_players[2]) {
	for (int i = 0; i < 4; i++) {
		game_players[0]->add_to_hand(game_deck->draw_card());
		game_players[1]->add_to_hand(game_deck->draw_card());
	} 
}
