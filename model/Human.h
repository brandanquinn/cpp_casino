#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"
#include "Move.h"

using namespace std;

class Human: public Player {
	private:
		string name;
		int get_card_index(char move_type);
	public:
		Human();
		Human(string a_name, int a_score);
		string get_name();
		void set_name(string a_name);
		Move* play();
};

#endif
