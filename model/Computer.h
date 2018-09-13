#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>

#include "Card.h"
#include "Player.h"

using namespace std;

class Computer: public Player {
	private:
		
	public:
		Computer();
		Computer(int a_score);
		void play();	
};

#endif
