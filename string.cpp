//Michael Lawrence


//String class functions
//used to store and compare an array of
//characters

#include "string.h"

String::String()
{
	//zero value set
	data = NULL;
	len = 0;

}

String::String(const String & to_copy)
{
	//copy constructor.
	copy(to_copy.data);
}

void String::copy(const char * to_copy)
{
	//this is a copy function used by the copy
	//constructor and assignment operators.
	data = new char [strlen(to_copy) + 1];
	strcpy(data, to_copy);		
	len = strlen(to_copy);	
}

String::~String()
{
	//if the data has been set it needs to be
	//deleted.
	if(data)
	{
		delete [] data;
		data = NULL;
	}
}

String & String::operator=(const String & to_set)
{
	//assignment that takes a string
	if(this == &to_set)
		//self assignment;
		return *this;
	if(data)
	{
		delete [] data;
	}
	copy(to_set.data);
	return *this;
}

String & String::operator=(const char * to_set)
{
	//assignment that takes a string
	if(data)
	{
		delete [] data;
	}
	copy(to_set);
	return *this;
}

char & String::operator[](int location)
{
	return data[location];
}


ostream& operator<<(ostream & out, const String & s1)
{
	//prints the string.
	out << s1.data;
	return out;
}

istream& operator>>(istream & in, String & s1)
{
	//reads in a string and sets
	//the length of the string.
	char temp[1000];
	cin.get(temp, 1000, '\n');
	if(s1.data)
		delete [] s1.data;
	s1.len = strlen(temp);
	s1.data = new char[s1.len + 1];
	strcpy(s1.data, temp);
	return in;
}

String & String::operator+=(const String & s2)
{
	//concatanates two strings.
	len += s2.len;	
	char * temp = new char[len + 1];
	strcpy(temp, data);
	strcat(temp, s2.data);
	char * hold = data;
	data = temp;
	delete [] hold;
	return *this;
}

String & String::operator+=(const char * s2)
{
	//concatanates a string and char *
	len += strlen(s2);	
	char * temp = new char[len + 1];
	strcpy(temp, data);
	strcat(temp, s2);
	char * hold = data;
	data = temp;
	delete [] hold;
	return *this;
}


String operator+(const String & s1, const String & s2)
{
	//concatanates two strings. 
	String temp;
	temp.len = s1.len + s2.len;
	temp.data = new char[temp.len + 1];
	strcpy(temp.data, s1.data);
	strcat(temp.data, s2.data);
	return temp;
}

String operator+(const char * s1, const String & s2)
{
	//concatanates a string and char *
	String temp;
	temp.len = strlen(s1) + s2.len;
	temp.data = new char[temp.len + 1];
	strcpy(temp.data, s1);
	strcat(temp.data, s2.data);
	return temp;
}

String operator+(const String & s1, const char * s2)
{
	//concatanates a string and char *
	String temp;
	temp.len = s1.len + strlen(s2);
	temp.data = new char[temp.len + 1];
	strcpy(temp.data, s1.data);
	strcat(temp.data, s2);
	return temp;
}



bool compare(const char * s1, const char * s2, int type)
{
	//does the right comparison so I only
	//have to write the code once.
	
	//if s1 > s2 then that means that s1 is
	//closer to the letter A than s2.
	//
	//0 is >
	//1 is <
	//2 is >=
	//3 is <=
	//4 is ==
	//5 is !=
	
	int cmpr = strcmp(s1, s2);
	bool success;
	if(type == 0)
	{
		if(cmpr < 0)
			success = true;
		else
			success = false;
	}
	else if(type == 1)
	{
		if(cmpr > 0)
			success = true;
		else
			success = false;
	}
	else if(type == 2)
	{
		if(cmpr <= 0)
			success = true;
		else
			success = false;
	}
	else if(type == 3)
	{
		if(cmpr >= 0)
			success = true;
		else
			success = false;
	}
	else if(type == 4)
	{
		if(cmpr == 0)
			success = true;
		else
			success = false;
	}
	else if(type == 5)
	{
		if(cmpr != 0)
			success = true;
		else
			success = false;
	}
	return success;
}

//all the comparison functions are merely wrappers that
//call compare. The int argument determines what
//compare to do.

//greater than operators.
bool operator>(const String & s1, const String & s2)
{
	return compare(s1.data, s2.data, 0);
}

bool operator>(const char * s1, const String & s2)
{
	return compare(s1, s2.data, 0);
}

bool operator>(const String & s1, const char * s2)
{
	return compare(s1.data, s2, 0);
}

//less than functions
bool operator<(const String & s1, const String & s2)
{
	return compare(s1.data, s2.data, 1);
}

bool operator<(const char * s1, const String & s2)
{
	return compare(s1, s2.data, 1);
}

bool operator<(const String & s1, const char * s2)
{
	return compare(s1.data, s2, 1);
}

//greater than or equal
bool operator>=(const String & s1, const String & s2)
{
	return compare(s1.data, s2.data, 2);
}

bool operator>=(const char * s1, const String & s2)
{
	return compare(s1, s2.data, 2);
}

bool operator>=(const String & s1, const char * s2)
{
	return compare(s1.data, s2, 2);
}

//less than or equal
bool operator<=(const String & s1, const String & s2)
{
	return compare(s1.data, s2.data, 3);
}

bool operator<=(const char * s1, const String & s2)
{
	return compare(s1, s2.data, 3);
}

bool operator<=(const String & s1, const char * s2)
{
	return compare(s1.data, s2, 3);
}

//equal
bool operator==(const String & s1, const String & s2)
{
	return compare(s1.data, s2.data, 4);
}

bool operator==(const char * s1, const String & s2)
{
	return compare(s1, s2.data, 4);
}

bool operator==(const String & s1, const char * s2)
{
	return compare(s1.data, s2, 4);
}

//not equal
bool operator!=(const String & s1, const String & s2)
{
	return compare(s1.data, s2.data, 5);
}

bool operator!=(const char * s1, const String & s2)
{
	return compare(s1, s2.data, 5);
}

bool operator!=(const String & s1, const char * s2)
{
	return compare(s1.data, s2, 5);
}


int String::get_length()
{
	return len;
}
