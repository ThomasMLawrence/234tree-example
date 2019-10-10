//Michael Lawrence
//
//food declaration and derived classes.
//The food class has dynamically bound, input
//output and ralational/equality functions
//that work with the desert, main course, and
//drink classes.


#include "string.h"

enum nuts{none, peanuts, cashews, pecans};

class food
{
	public:
		food();

		//these do input and output of food. They are
		//wrappers for the vitual display function
		//and so work with upcasting.
		friend ostream& operator<<(ostream& out, const food & f1);
		friend istream& operator>>(istream& in, food & f1);

		//these compare food items based on their
		//name.
		bool operator>(const food & f2) const;
		bool operator>=(const food & f2) const;
		bool operator<(const food & f2) const;
		bool operator<=(const food & f2) const;
		bool operator==(const food & f2) const;
		bool operator!=(const food & f2) const;
		
		//a virtual check function to determine
		//whether or not a food item contains various
		//qualities. returns one if yes 0 if no.
		virtual int check(int type, int search) = 0;
		//returns 1 if the name matches, 0 if no.
		int check(const char * match);

	protected:
		//used by that relational and quality operators
		//1 is >, 2 is >=, 3 is <, 4 is <=, 5 is !=, 6 is ==
		bool compare(const food & f2, int type) const;
		//calls correct display and insert functions.
		virtual void display() const = 0;
		virtual void insert() = 0;
		
		String item;
		int calories;
		int gluten;
		int lactose;
};

class main_course: public food
{
	public:
		main_course();
		void display() const;
		void insert();	
		int check(int type, int search);

	protected:	
		nuts nut;
};


class desert: public food
{
	public:
		desert();
		void display() const;
		void insert();	
		int check(int type, int search);

	protected:	
		nuts nut;
		int sugar;
};


class drink: public food
{
	public:
		drink();
		void display() const;
		void insert();	
		int check(int type, int search);

	protected:	
		float alcohol;
		int sugar;
};
