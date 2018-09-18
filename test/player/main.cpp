#include <iostream>
#include <vector>
#include <random>

#include "../../model/Human.h"
#include "../../model/Computer.h"
#include "../../model/Card.h"
#include "../../model/Deck.h"
#include "../../model/Tournament.h"
#include "../../model/Round.h"

using namespace std;

int main() {
	srand(time(NULL));
	Tournament t1;

	t1.start_round();
	t1.end_round();

}
