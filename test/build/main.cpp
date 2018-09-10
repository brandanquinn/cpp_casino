#include <iostream>
#include <string>
#include "../model/Build.h"

using namespace std;

int main() {
	string my_card = "S4";
	cout << "hello world we've compiled" << endl;
	Build b1(false, 4, my_card);

	if (b1.get_multi_build()) {
		cout << "b1 is a multi-build!" << endl;	
	} else {
		cout << "b1 is not a multi-build!" << endl;
	}
	cout << "What is the current sum of b1: " << b1.get_sum() << endl;
	cout << "What is the current sum card of b1: " << b1.get_sum_card() << endl;
}
