#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"

using namespace std;

class Human: public Player {
	private:
		string name;
	public:
		Human(string a_name);
		Human(string a_name, int a_score);
		string get_name();
		void set_name(string a_name);
		void play();
};

#endif
