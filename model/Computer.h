#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>

#include "Card.h"
#include "Player.h"
#include "Move.h"

using namespace std;

class Computer: public Player {
	private:
		
	public:
		Computer();
		Computer(int a_score);
		Move* play();	
};

#endif
