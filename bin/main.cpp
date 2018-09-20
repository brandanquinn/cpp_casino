#include <iostream>
#include <vector>
#include <random>

#include "../model/Tournament.h"

using namespace std;

int main() {
	srand(time(NULL));
	Tournament t1;

	t1.start_round();
	t1.end_round();
}
