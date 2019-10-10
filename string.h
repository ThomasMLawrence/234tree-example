//Michael Lawrence


//the declaration of the string class
//used to store an array of characters
//contains length and comparison as well

#include <iostream>
#include <cstring>

using namespace std;


class String
{
	public:
		String();
		String(const String & to_copy);
		~String();
		//assignment passing in a String object
		String& operator=(const String & to_set);
		//assignment with a const char *
		String& operator=(const char * to_set);
	
		
		char & operator[](int location);

		//input and output	
		friend ostream& operator<<(ostream & out, const String & s1);
		friend istream& operator>>(istream & in, String & s1);

		//these are the most efficient way
		//of concatanating strings due to
		//the language.
		String& operator+=(const String & s2);
		String& operator+=(const char * s2);

		//these addition operators are significantly
		//less efficient than the += operator due
		//to the language. Try to use the  += 
		//wherever.
		friend String operator+(const String & s1, const String & s2);
		friend String operator+(const char * s1, const String & s2);
		friend String operator+(const String & s1, const char * s2);

		//comparison operators. You can compare
		//two Strings and a String and const
		//char *. If a > b then that means that
		//string a is alphabetically closer to
		//the letter A then string b is.
		
		friend bool operator>(const String & s1, const String & s2);
		friend bool operator>(const char * s1, const String & s2);
		friend bool operator>(const String & s1, const char * s2);

		
		friend bool operator<(const String & s1, const String & s2);
		friend bool operator<(const char * s1, const String & s2);
		friend bool operator<(const String & s1, const char * s2);


		
		friend bool operator>=(const String & s1, const String & s2);
		friend bool operator>=(const char * s1, const String & s2);
		friend bool operator>=(const String & s1, const char * s2);

		
		friend bool operator<=(const String & s1, const String & s2);
		friend bool operator<=(const char * s1, const String & s2);
		friend bool operator<=(const String & s1, const char * s2);


		
		friend bool operator==(const String & s1, const String & s2);
		friend bool operator==(const char * s1, const String & s2);
		friend bool operator==(const String & s1, const char * s2);

		
		friend bool operator!=(const String & s1, const String & s2);
		friend bool operator!=(const char * s1, const String & s2);
		friend bool operator!=(const String & s1, const char * s2);
		
		//returns length
		int get_length();
	private:
		//this is used by the comparison operators
		friend bool compare(const char * s2, int type);
		//this is used by the copy constructor.
		void copy(const char * to_copy);
		char * data;
		int len;


};
