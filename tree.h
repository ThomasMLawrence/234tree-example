//Michael Lawrence

//this file contains the declarations for
//the data structure and the client program.
//Food is stored in a 234 tree contained within
//the client program under the name menu. The user
//can add new food to the menu or they can
//view existing food based on various types.

#include "food.h"



class node
{
	//this is a 234 node for a 234 tree.
	//the number 0 corresponds to the left
	//most data or next pointer in the node
	//and an increase in numerical value moves
	//to the right in the data or next pointers
	//of the node.
	public:
		node();
		//allocates the arrays in the node
		//and sets their values to NULL.
		node(const node & to_copy);
		//copy constructor
		~node();
		//destructor
		node& operator=(const node& to_set);
		//assignment operator copies the data
		//as expected.
		friend ostream& operator<<(ostream& out, const node * current);
		//insertion operator prints the nodes
		//data.
		void display(const int slot) const;
		//displays the chosen slot. diplays nothing
		//if it is empty.
		node* & go_next(const int slot) const;
		//pass in 0 - 3 to go the four different
		//children of the 234 node.
		int set_next(const int slot, node* to_set);
		//pass in 0 - 3 to manually set the next
		//pointer of the 234 node.
		
		//WARNING: when manaully setting data
		//you must start by setting the data
		//in slot 1 when you have just created
		//a node.
		int set_data(const int slot, food * to_set);
		//manually sets the data of the 234
		//tree. pass in 0 -2 to set the data
		//in the node. this works with a food
		//pointer. this is used when moving
		//one food that has already been allocated
		//to a new node. the food pointer is not
		//constant sice it is being moved in the
		//data structure. no copy is caused. just
		//pointer reassignment.
		void set_data(const int slot, const food & to_add);		
		//pass in a food reference to create a newly
		//allocated food item. this causes a copy
		//so it is not advised for shifting data.
		//instead use this function for adding
		//new data to the data structure.
		
		food *& get_data(const int slot);
		//returns the data pointer of a slot.
		//used for shifting data during node splits.
		
		//WARNING: these add functions only work
		//on a node that alreadys has data and is
		//not full. Use direct add for a newly
		//created node. Full nodes should be split.
		void add(food * to_add);
		//adds a pointer to data when you are not
		//sure where it needs to go. less efficient
		//than directly set_data with a pointer.
		//no copy is caused so this is useful
		//for shifting data during node splits.
		void add(const food & to_add);
		//adds a reference. used when you are not
		//sure where the reference needs to be added.
		//less efficient than set_data with a reference.
		//causes a copy so only used when adding
		//new data.
		//WARNING: becuase this causes a copy
		//it is assumed you will only use this version
		//with new data and so will only be adding 
		//at a leaf with data. This will not 
		//work when adding anywhere but a leaf.
		
		int where_to(const food & to_compare);
		//tells the tree, based on the data passed
		//which next pointer we will travel to
		//next. The int returned ranges from 0 - 3.
		//0 is the left most next and 3 is the
		//greatest.
		int size();
		//used by the tree to determine what
		//splitting algorithm we need to use.
		int leaf();
		//if leaf add data.
		bool full();	
		//checks if the node is full. used for splitting
		//nodes.
		int search(int type, int search);
		//key for looking for items
		//Calories:
		//type == 1, prints less than or equal
		//to search
		//Gluten:
		//type == 2, search is true wants gluten
		//search is false no gluten
		//Lactose:
		//type == 3, same as gluten
		//Nuts:
		//type == 4, search 1 is all nuts,
		//2 is no peantus, 3 is no cashews,
		//4 is no pecans
		//Sugar:
		//type == 5, prints less than or equal to
		//search
		//Alcohol:
		//type == 6, search == 1 is yes alcohol, 
		//0 is no
		int search(const char * match);
		//searches for matching name.
		//then displays
		int display_all_of_type(int type);
		//displays all dishes of a type
		//1 is main course, 2 is desert
		//3 is drink.

	private:
		//checks if a next pointer needs to be shifted, 
		//the first is a wrapper and the second does
		//the comparison, location 1 checks a shift
		//from left to right and location 2 is the
		//opposite.
		int check_shift(food & to_check, int location);
		int check_shift(food & to_check, int location, node * root);
		void set_null(node ** &current);
		//moves through the array and sets
		//the values to NULL recursively
		void set_null(food ** &current);
		//moves through the array and sets
		//the values to NULL recursively
		void copy(const node & to_copy);
		//called by the copy constructor
		//to begin the recursive copy
		void copy(node ** &current, node ** current1);
		//copies over the node pointers
		void copy(food ** &current, food ** current1);
		//copies over the food pointers
		void trash(food **& current);
		//recursively deletes food
		void trash();
		//calls the two above recursive functions
		//and then deletes the arrays
		node ** child;
		food ** data;
};



class tree
{
	public:
		tree();
		//copies a tree.
		tree(const tree & to_copy);
		//deletes tree
		~tree();
		//copies tree, use if the tree already
		//exists and you want to copy a new one
		//into it deleting the old tree.
		tree& operator=(const tree & to_copy);	

		//the +operator returns by reference since
		//it does not use a temporary. It looks like
		//tree + food or food + tree. Thus the tree,
		//which is not local to the operator function
		//can be returned by reference. On top of
		//that the = operators check for self assignment
		//if you write my_tree = my_tree + some_food will
		//prevent the tree from being copied at all.
		friend tree& operator+(tree & my_tree, const food & to_add);
		friend tree& operator+(const food & to_add, tree & my_tree);
		tree& operator+=(const food & to_add);
		
		//used for printing your data structure.
		friend ostream& operator<<(ostream& out, const tree & to_print);

		//used to search for a given type
		//key for looking for items
		//Calories:
		//type == 1, prints less than or equal
		//to search
		//Gluten:
		//type == 2, search is true wants gluten
		//search is false no gluten
		//Lactose:
		//type == 3, same as gluten
		//Nuts:
		//type == 4, search 1 is all nuts,
		//2 is no peantus, 3 is no cashews,
		//4 is no pecans
		//Sugar:
		//type == 5, prints less than or equal to
		//search
		//Alcohol:
		//type == 6, search == 1 is yes alcohol, 
		//0 is no
		int operator()(int type, int qualifier);
		//displays based on a name passed in
		int display(const char * match);	
		//displays all dishes of a given type
		//1 == main course, 2 == desert, 3 == drink
		int display_all_of_type(int type);





	private:
		//recursive function for display all of type
		int display_all_of_type(int type, node * root);
		//recursive function for display by name
		int display(const char * match, node * root);
		//recursive function for operator()
		int search(int type, int qualifier, node * root);
		//recursive function for operator<<
		void display(ostream& out, const node * root) const;
		//wrapper for recursive insert, called by
		//operators +, +=
		int insert(const food & to_add);
		//recursive insert
		int insert(node *& root, const food & to_add);
		//recursive copy
		void copy(node * root, const node * original);
		//recursive delete
		void trash(node *& root);
		node * root;
};


class client
{
	public:
		//runs the menu program, returns 0
		//when the user wants to quit.
		int run();

	private:
		tree menu;

};
