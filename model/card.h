#ifndef CARD_H
#define CARD_H

class Card {
	private:
		char suit;
		char type;
		int value;
	public:
		Card();
		char get_suit();
		void set_suit(char a_suit);
		char get_type();
		void set_type(char a_type);
		int get_value();
		void set_value(int a_value);
}

#endif
