#include <iostream>

#include "../../model/Tournament.h"
#include "../../model/Round.h"

using namespace std;

int main() {
	Tournament t1;
	for (int i = 0; i < 5; i++) {
		t1.start_round();
	}	
}
