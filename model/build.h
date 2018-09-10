#ifndef BUILD_H
#define BUILD_H

#include <string>

using namespace std;

class Build {
	private:
		bool multi_build;
		int sum;
		string sum_card;
		
	public:
		Build();
		bool get_multi_build();
		void set_multi_build(bool a_multi_build);
		int get_sum();
		void set_sum(int a_sum);
		string get_sum_card();
		void set_sum_card(string a_sum_card);
};

#endif
