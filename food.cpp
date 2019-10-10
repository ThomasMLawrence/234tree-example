//Michael Lawrence
//
//food functions and their derived counterparts
//These are stored in the menu for the client class
//so the user can add and see the food they want.

#include "food.h"

food::food()
{
	//zero value function	
	calories = 0;
	gluten = 0;
	lactose = 0;
}

//these are wrappers for dynamically bound insert and display
//functions so you can insert and display derived classes
//through upcasting.
ostream& operator<<(ostream& out, const food & f1)
{
	f1.display();
}

istream& operator>>(istream& in, food & f1)
{
	f1.insert();
}

//these are all wrappers for the compare function.
//the number passed in tells the compare function which
//compare to do.
bool food::operator>(const food & f2) const
{
	return compare(f2, 1);
}

bool food::operator>=(const food & f2) const
{
	return compare(f2, 2);
}
bool food::operator<(const food & f2) const
{
	return compare(f2, 3);
}
bool food::operator<=(const food & f2) const
{
	return compare(f2, 4);
}
bool food::operator==(const food & f2) const
{
	return compare(f2, 5);
}
bool food::operator!=(const food & f2) const
{
	return compare(f2, 6);
}


bool food::compare(const food & f2, int type) const
{
	//used by that relational and quality operators
	//1 is >, 2 is >=, 3 is <, 4 is <=, 5 is !=, 6 is ==
	//this function is a wrapper for the string
	//compare functions.
	if(type == 1)
		return item > f2.item;
	else if(type == 2)
		return item >= f2.item;
	else if(type == 3)
		return item < f2.item;
	else if(type == 4)
		return item <= f2.item;
	else if(type == 5)
		return item == f2.item;
	else if(type == 6)
		return item != f2.item;
}

int food::check(const char * match)
{
	//if the string compare function
	//is a match, returns 1
	if(match == item)
		return 1;
	else
		return 0;
}



main_course::main_course()
{
	nut = none;
}

void main_course::display() const
{
	//displays the main course data, the unique data
	//to this class is a nut stored as an enum
	cout << "The name of the dish is " << endl;
	cout << item << endl;
	cout << "The calories in the dish are " << calories << endl;
	if(gluten)
		cout << "The dish has gluten in it." << endl;
	else
		cout << "The dish is gluten free." << endl;
	if(lactose)
		cout << "The dish has lactose." << endl;
	else
		cout << "The dish is lactose free." << endl;
	if(nut == none)
		cout << "The dish has no nuts." << endl;
	else if(nut == peanuts)
		cout << "The dish has peanuts." << endl;
	else if(nut == cashews)
		cout << "The dish has cashews." << endl;
	else if(nut == pecans)
		cout << "The dish has pecans." << endl;
}

void main_course::insert()
{
	//insert for the main course.
	cout << "Please enter the name of the dish " << endl;
	cin >> item;
	cin.ignore(100 ,'\n');

	cout << "Please enter the calories " << endl;
	cin >> calories;
	cin.ignore(100, '\n');

	char temp[100];
	cout << "Does the dish have gluten." << endl;
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');
	if(temp[0] == 'Y' || temp[0] == 'y')
		gluten = 1;
	else
		gluten = 0;

	cout << "Does the dish have lactose." << endl;
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');
	if(temp[0] == 'Y' || temp[0] == 'y')
		lactose = 1;
	else
		lactose = 0;
	
	cout << "What type of nuts does the dish have." << endl;
	cout << "1 - no nuts" << endl;
	cout << "2 - peanuts" << endl;
	cout << "3 - cashews" << endl;
	cout << "4 - pecans" << endl;
	int user;
	cin >> user;
	if(user == 2)
		nut = peanuts;
	else if(user == 3)
		nut = cashews;
	else if(user == 4)
		nut = pecans;
	else
		nut = none;
}

int main_course::check(int type, int search)
{
	//checks for various main course elements
	if(type == 1)
	{
		//returns 1 if the callories are lower
		//than search
		if(calories <= search)
			return 1;	
		else
			return 0;
	}
	else if(type == 2)
	{
		if(search)
		{
			//if the user wants gluten
			if(gluten)
				return 1;
			else
				return 0;
		}
		else
		{
			//if the user doesn't want gluten
			if(!gluten)
				return 1;
			else
				return 0;
		}
	}
	else if(type == 3)
	{
		if(search)
		{
			//if the user wants lactose
			if(lactose)
				return 1;
			else
				return 0;
		}
		else
		{
			//if they don't want lactose
			if(!lactose)
				return 1;
			else
				return 0;
		}

	}
	else if(type == 4)
	{
		//nuts
		if(search == 1)
		{
			//wants all nuts
			return 1;
		}
		if(search == 2)
		{
			//!peanuts
			if(nut == peanuts)
				return 0;
			else
				return 1;
		}
		if(search == 3)
		{
			//!cashews
			if(nut == cashews)
				return 0;
			else
				return 1;
		}
		if(search == 4)
		{
			//!pecans
			if(nut == pecans)
				return 0;
			else
				return 1;
		}
	}
	else
	{
		//if a number was passed in that was
		//not 1-4 then the user is looking for
		//another meal type. This foregos RTTI.
		return 0;
	}
}


desert::desert()
{
	nut = none;
	sugar = 0;
}

void desert::display() const
{
	//displays desert
	//deserts have nuts and sugar as their unique data
	cout << "The name of the desert is " << endl;
	cout << item << endl;
	cout << "The calories in the desert are " << calories << endl;
	cout << "The sugar content is " << sugar << " grams." << endl;
	if(gluten)
		cout << "The desert has gluten in it." << endl;
	else
		cout << "The desert is gluten free." << endl;
	if(lactose)
		cout << "The desert has lactose." << endl;
	else
		cout << "The desert is lactose free." << endl;
	if(nut == none)
		cout << "The dish has no nuts." << endl;
	else if(nut == peanuts)
		cout << "The dish has peanuts." << endl;
	else if(nut == cashews)
		cout << "The dish has cashews." << endl;
	else if(nut == pecans)
		cout << "The dish has pecans." << endl;
}

void desert::insert()
{
	//reads in a desert
	cout << "Please enter the name of the desert " << endl;
	cin >> item;
	cin.ignore(100 ,'\n');

	cout << "Please enter the calories " << endl;
	cin >> calories;
	cin.ignore(100, '\n');

	cout << "Please enter the sugar content " << endl;
	cin >> sugar;
	cin.ignore(100, '\n');

	char temp[100];
	cout << "Does the desert have gluten." << endl;
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');
	if(temp[0] == 'Y' || temp[0] == 'y')
		gluten = 1;
	else
		gluten = 0;

	cout << "Does the desert have lactose." << endl;
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');
	if(temp[0] == 'Y' || temp[0] == 'y')
		lactose = 1;
	else
		lactose = 0;
	
	cout << "What type of nuts does the desert have." << endl;
	cout << "1 - no nuts" << endl;
	cout << "2 - peanuts" << endl;
	cout << "3 - cashews" << endl;
	cout << "4 - pecans" << endl;
	int user;
	cin >> user;
	if(user == 2)
		nut = peanuts;
	else if(user == 3)
		nut = cashews;
	else if(user == 4)
		nut = pecans;
	else
		nut = none;
}


int desert::check(int type, int search)
{
	if(type == 1)
	{
		//returns 1 if the calories are
		//lower than or equal to requested
		if(calories <= search)
			return 1;	
		else
			return 0;
	}
	else if(type == 2)
	{
		if(search)
		{
			//if wants gluten
			if(gluten)
				return 1;
			else
				return 0;
		}
		else
		{
			//if wants no gluten
			if(!gluten)
				return 1;
			else
				return 0;
		}
	}
	else if(type == 3)
	{
		if(search)
		{
			//if wants lactose
			if(lactose)
				return 1;
			else
				return 0;
		}
		else
		{
			//wants no lactose
			if(!lactose)
				return 1;
			else
				return 0;
		}

	}
	else if(type == 4)
	{
		//finds right nut type
		if(search == 1)
		{
			return 1;
		}
		if(search == 2)
		{
			if(nut == peanuts)
				return 0;
			else
				return 1;
		}
		if(search == 3)
		{
			if(nut == cashews)
				return 0;
			else
				return 1;
		}
		if(search == 4)
		{
			if(nut == pecans)
				return 0;
			else
				return 1;
		}
	}
	else if(type == 5)
	{
		//finds sugar that is less than
		//or equal to requested.
		if(sugar <= search)
			return 1;
		else 
			return 0;
	}
	else
	{
		//if a number was passed in that was
		//not 1-5 then the user is looking for
		//another meal type. This foregos RTTI.
		return 0;
	}
}




drink::drink()
{
	alcohol = 0.0;
}

void drink::display() const
{
	//displays drink
	cout << "The name of the drink is " << endl;
	cout << item << endl;
	cout << "The calories in the drink are " << calories << endl;
	cout << "The proof is " << alcohol << endl;
	cout << "The sugar content is " << sugar << " grams" << endl;
	if(gluten)
		cout << "The drink has gluten in it." << endl;
	else
		cout << "The drink is gluten free." << endl;
	if(lactose)
		cout << "The drink has lactose." << endl;
	else
		cout << "The drink is lactose free." << endl;
}

void drink::insert()
{
	//reads in drink
	cout << "Please enter the name of the drink " << endl;
	cin >> item;
	cin.ignore(100 ,'\n');

	cout << "Please enter the calories " << endl;
	cin >> calories;
	cin.ignore(100, '\n');

	cout << "Please enter the proof " << endl;
	cin >> alcohol;
	cin.ignore(100, '\n');
	
	cout << "Please enter the sugar content " << endl;
	cin >> sugar;
	cin.ignore(100, '\n');

	char temp[100];
	cout << "Does the drink have gluten." << endl;
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');
	if(temp[0] == 'Y' || temp[0] == 'y')
		gluten = 1;
	else
		gluten = 0;

	cout << "Does the drink have lactose." << endl;
	cin.get(temp, 100, '\n');
	if(temp[0] == 'Y' || temp[0] == 'y')
		lactose = 1;
	else
		lactose = 0;
	
}

int drink::check(int type, int search)
{
	if(type == 1)
	{
		//if calories are below or equal
		//what is wanted
		if(calories <= search)
			return 1;	
		else
			return 0;
	}
	else if(type == 2)
	{
		if(search)
		{
			//wants gluten
			if(gluten)
				return 1;
			else
				return 0;
		}
		else
		{
			//doesn't want gluten
			if(!gluten)
				return 1;
			else
				return 0;
		}
	}
	else if(type == 3)
	{
		if(search)
		{
			//wants lactose
			if(lactose)
				return 1;
			else
				return 0;
		}
		else
		{
			//doesn't want lactose
			if(!lactose)
				return 1;
			else
				return 0;
		}

	}
	else if(type == 5)
	{
		//less than or equal to sugar
		//wanted
		if(sugar <= search)
			return 1;
		else
			return 0;
	}
	else if(type == 6)
	{
		if(search)
		{
			//wants alcohol
			if(alcohol > 0.0)
				return 1;
			else
				return 0;
		}
		else
		{
			//doesn't want alcohol
			if(alcohol == 0.0)
				return 1;
			else
				return 0;
		}
	}
	else
	{
		//if 4 is passed in the user is looking
		//for a non drink dish.
		return 0;
	}
}
