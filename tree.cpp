//Michael Lawrence


//these are the functions that build and manage
//the data structure and the client program that
//utilizes them. A 234 tree is built out of the node
//class. The user can insert new data into the tree
//or view existing data based on various parameters.

#include "tree.h"


node::node()
{
	//the default constructor allocates
	//the arrays and sets all their cells
	//to NULL through pointer arithmetic.
	child = new node* [4];
	node ** current1 = child;
	set_null(current1);
	data = new food* [3];
	food ** current2 = data;
	set_null(current2);
}

void node::set_null(node ** &current)
{
	//this function moves through the
	//child array with pointer arithmetic
	//and sets all the values to NULL.
	if(current > child + 3)
	{
		return;
	}
	*current = NULL;
	set_null(++current);
}

void node::set_null(food ** &current)
{
	//sets the food values to NULL in the same
	//manner as the above function
	if(current > data + 2)
	{
		return;
	}	
	*current = NULL;
	set_null(++current);
}

node::node(const node & to_copy)
{
	//the copy constructor is a wrapper
	//to a recursive copy
	copy(to_copy);
}

void node::copy(const node & to_copy)
{
	//a wrapper for the recursive copy
	//functions. this function also 
	//handles the allocation of the
	//arrays.
	child = new node* [4];
	node ** current = child;
	set_null(current);
	
	data = new food* [3];
	food ** current3 = data;
	food ** current4 = to_copy.data;
	copy(current3, current4);
}

void node::copy(node ** &current, node ** current1)
{
	//recursively copies the pointers
	if(current > child + 3)
		return;
	*current = *current1;
	copy(++current, ++current1);
}

void node::copy(food ** &current, food ** current1)
{
	
	//uses RTTI to copy over the food.
	if(current > data + 2)
		return;

	//RTTI for copying the food.
	if(*current1)
	{
		if(main_course* ptr1 = dynamic_cast<main_course*>(*current1))
		{
			*current = new main_course(*ptr1);
		}
		else if(desert* ptr2 = dynamic_cast<desert*>(*current1))
		{
			*current = new desert(*ptr2);
		}
		else if(drink* ptr3 = dynamic_cast<drink*>(*current1))
		{
			*current = new drink(*ptr3);
		}
	}
	else
	{
		*current = NULL;
	}
	copy(++current, ++current1);
}

node::~node()
{
	//wrapper for destructor
	trash();
}

void node::trash()
{
	//first this function calles
	//the recursive delete to delete
	//the pointers and then it
	//deletes the array
	delete [] child;
	if(data)
	{
		food ** current1 = data;
		trash(current1);	
		delete [] data;
	}
}


void node::trash(food **& current)
{
	//recursively deletes the food.
	if(current > data + 2)
		return;
	if(*current)
		delete *current;
	trash(++current);
}

node& node::operator=(const node& to_set)
{
	//checks for self assignment
	if(this == &to_set)
		return *this;
	//checks if it needs to deallocate.
	trash();
	//copies
	copy(to_set);
	//return current object
	return *this;
}

ostream& operator<<(ostream& out, const node * current)
{
	//prints data
	for(int i = 0; i < 3; ++i)
	{
		if(current->data[i])
		{
			//calls the operator << for the
			//food objects in order to display
			//them
			
			out << *current->data[i] << endl; 
		}
	}
	return out;
}

void node::display(const int slot) const
{
	//prints only one data item.
	if(data[slot])
	{
		cout << *data[slot] << endl;
	}
}


node* & node::go_next(const int slot) const
{
	//goes to the next node. Pass in 0 through 3
	//to travel to any of the four children of a
	//234 node.
	return child[slot];
}

int node::set_next(const int slot, node* to_set)
{
	//manually sets the next pointer of the 234
	//node.
	child[slot] = to_set;
	return 1;
}

int node::set_data(const int slot, food * to_set)
{
	//sets the data through pointer reassignment
	data[slot] = to_set;
}


void node::set_data(const int slot, const food & to_add)
{
	//allocates a new food item by copying the reference.
	//used for instantiating new food items from NULL pointers
	//uses RTTI to determine what food item to allocate.
	const food * fptr = &to_add;
	if(const main_course* ptr1 = dynamic_cast<const main_course*>(fptr))
	{
		data[slot] = new main_course(*ptr1);
	}
	else if(const desert* ptr2 = dynamic_cast<const desert*>(fptr))
	{
		data[slot] = new desert(*ptr2);
	}
	else if(const drink* ptr3 = dynamic_cast<const drink*>(fptr))
	{
		data[slot] = new drink(*ptr3);
	}
}


food *& node::get_data(const int slot)
{
	//returns a pointer to the slot it
	//is pointing to.
	return data[slot];
}



void node::add(const food & to_add)
{
	//this add function is used when you are adding
	//a new item to the list but are not sure where
	//you want to add it because you do not know
	//the layout of the data in the node.
	//
	//it is assumed this function is only used at
	//a leaf. No need to check next pointers since
	//they are all NULL.
	if(data[0])
	{
		//first checks if there is data in
		//the left most slot. Then it checks
		//left to right to see where the data goes.
		//If it goes in that slot the data gets
		//moved down and the new data is added.
		if(*data[0] < to_add)
		{
			data[2] = data[1];
			data[1] = data[0];
			set_data(0, to_add);	
		}
		else if(*data[1] < to_add)
		{
			data[2] = data[1];
			set_data(1, to_add);

		}
		else
		{
			set_data(2, to_add);
		}
	}
	else if(data[2])
	{
		//if there is data in the second slot
		//we need to check right to left.
		if(*data[2] > to_add)
		{
			data[0] = data[1];
			data[1] = data[2];
			set_data(2, to_add);
		}
		else if(*data[1] > to_add)
		{
			data[0] = data[1];
			set_data(1, to_add);
			
		}
		else
		{
			set_data(0, to_add);
		}
	}
	else
	{
		//otherwise add check against the middle.
		//makes sure the node is not empty.
		if(*data[1] > to_add)
		{
			set_data(2, to_add);
		}
		else
		{
			set_data(0, to_add);
		}
	}
}

void node::add(food * to_add)
{
	//adds a pointer to data. Used when splitting
	//nodes, specifically where you are not sure
	//where the data will be placed.
	//
	//Once major difference in this function
	//as opposed to the reference function.
	//checks if the next pointer of the middle
	//left or middle right needs to be moved.
	if(data[0])
	{
		//if data is in the left most slot
		//check left to right.
		if(*data[0] < *to_add)
		{
			data[2] = data[1];
			data[1] = data[0];
			data[0] = to_add;
			
			child[2] = child [1];	
			child[1] = NULL;
		}
		else if(*data[1] < *to_add)
		{
			data[2] = data[1];
			data[1] = to_add;
			//we may need to shift the next
			//pointer down.
			if(check_shift(*to_add, 1))
			{
				child[2] = child[1];
				child[1] = NULL;
			}

		}
		else
		{
			data[2] = to_add;
		}
	}
	else if(data[2])
	{
		//if data is in right most slot checks
		//right to left.
		if(*data[2] > *to_add)
		{
			data[0] = data[1];
			data[1] = data[2];
			data[0] = to_add;
			child[1] = child[2];
			child[2] = NULL;
		}
		else if(*data[1] > *to_add)
		{
			data[0] = data[1];
			data[1] = to_add;
			//check for a next pointer shift	
			if(check_shift(*to_add, 2))
			{
				child[1] = child[2];
				child[2] = NULL;
			}
		}
		else
		{
			data[0] = to_add;
		}
	}
	else
	{
		//otherwise check against the middle
		if(*data[1] > *to_add)
		{
			data[2] = to_add;
		}
		else
		{
			data[0] = to_add;
		}
	}
}

int node::check_shift(food & to_check, int location)
{
	//wrapper to check if the node needs
	//to be shifted due to new data being
	//added. If location is 1, check the middle
	//left child, if location is 2, check the middle
	//right child.
	//
	//a shift could occur when splitting
	//the middle right or left node in the tree and
	//this is because the data in the parent node
	//will change when the middle is poped up
	//and this could result in the next pointer
	//needing to be moved.
	if(location == 1)
	{
		if(child[1])
		{
			return check_shift(to_check, location, child[1]);
		}
		else
			return 0;
	}
	else if(location == 2)
	{
		if(child[2])
		{
			return check_shift(to_check, location, child[2]);
		}
		else
			return 0;
	}
}

int node::check_shift(food & to_check, int location, node * root)
{
	if(!root)
		return 0;
	//checks if the node needs to be shifted
	//one over.
	if(location == 1)
	{
		//if the left most item in the node is
		//alphabetically lower than the data
		//being added then the node needs to be
		//shifted one over.
		if(root->data[0])
		{
			//if the left most item is the left
			//data it needs to be checked.
			if(*root->data[0] < to_check)
			{
				return 1;
			}
			else
			{
				return 0;	
			}
		}
		else if(root->data[1])
		{
			//if the left most item is
			//the middle item it needs to be
			//checked.
			if(*root->data[1] < to_check)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

	}
	else if(location == 2)
	{
		//if the right most item in the node
		//is alphabetically higher than to_check,
		//this node needs to be shifted from
		//the middle right position to
		//the middle left.
		if(root->data[2])
		{
			//if the right most item is the
			//right data it needs to be checked
			if(*root->data[2] > to_check)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(root->data[1])
		{
			//if the right most item is
			//the middle data it needs to be
			//checked.
			if(*root->data[1] > to_check)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}


int node::where_to(const food & to_compare)
{
	//figures out based on the data where to
	//go next.
	for(int i = 0; i < 3; ++i)
	{
		//if the data is a copy, no copies allowed in
		//the tree.
		if(data[i])
		{
			if(*data[i] == to_compare)
			{
				return -1;
			}
		}
	}
	//make sure the node has data.
	if(data[1])
	{
		//check based on the middle item.
		if(*data[1] < to_compare)
		{
			//check left.
			//check if the left slot has data.
			if(data[0])
			{
				//check against the left data.
				if(*data[0] < to_compare)
				{
					//far left
					return 0;
				}
				else
				{
					//in between left and
					//middle,
					return 1;
				}
			}
			else
			{
				//otherwise, far left.
				return 0;
			}
		}
		else
		{
			//otherwise check right data
			if(data[2])
			{
				if(*data[2] < to_compare)
				{
					//in between middle and
					//right
					return 2;
				}
				else
				{
					//otherise far right.
					return 3;
				}
			}
			else
			{
				//if no right data go left.
				return 3;
			}
		}
	}
}

bool node::full()
{
	//if the node is full it needs to be split.
	if(data[0] && data[1] && data[2])
		return true;
	else
		return false;
}


int node::size()
{
	//gets the size of node. Used by the tree
	//to determine how to split the node after
	//the middle has been poped up. After the data
	//has been poped up the node will either have
	//three data items or two.
	if(data[0] && data[2])
	{
		return 3;
	}
	else
	{
		return 2;
	}

}

int node::leaf()
{
	//if a leaf we can add data.
	for(int i = 0; i < 4; ++i)
	{
		if(child[i])
			return 0;	
	}
	return 1;

}

int node::search(int type, int search)
{
	//checks if the data contains the items
	//the user is looing for.
	int success = 0;
	for(int i = 0; i < 3; ++i)
	{
		if(data[i])
		{
			if(data[i]->check(type, search))
			{
				cout << *data[i] << endl;
				success = 1;
			}
		}	
	}	
	return success;
}

int node::search(const char * match)
{
	//searches for a matching name
	int success = 0;
	for(int i = 0; i < 3; ++i)
	{
		if(data[i])
		{
			if(data[i]->check(match))
			{
				cout << *data[i] << endl;
				success = 1;
			}
		}
	}
	return success;
}

int node::display_all_of_type(int type)
{
	//display all data of a given type
	int success = 0;
	for(int i = 0; i < 3; ++i)
	{
		if(data[i])
		{
			if(main_course * ptr1 = dynamic_cast<main_course*>(data[i]))
			{
				if(type == 1)
				{
					cout << *ptr1 << endl;
					success = 1;
				}
			}
			else if(desert * ptr2 = dynamic_cast<desert*>(data[i]))
			{
				if(type == 2)
				{
					cout << *ptr2 << endl;
					success = 1;
				}
			}
			else if(drink * ptr3 = dynamic_cast<drink*>(data[i]))
			{
				if(type == 3)
				{
					cout << *ptr3 << endl;
					success = 1;
				}
			}


		}
	}
	return success;
}




tree::tree()
{
	root = NULL;
}

tree::tree(const tree & to_copy)
{
	//wrapper for copy
	copy(root, to_copy.root);
}

void tree::copy(node * root, const node * original)
{
	//recursive copy
	if(!original)
		return;

	//calls node copy constructor.
	root = new node(*original);
	for(int i = 0; i < 4; ++i)
	{
		//traverses all directions of the tree.
		copy(root->go_next(i), original->go_next(i));
	}
}

tree::~tree()
{
	//wrapper for delete
	trash(root);
}


void tree::trash(node *& root)
{
	//recursive delete
	if(!root)
		return;

	for(int i = 0; i < 4; ++i)
	{
		//goes all directions
		trash(root->go_next(i));
	}
	delete root;
	root = NULL;
}

tree& tree::operator=(const tree & to_copy)
{
	//checks for self assignment
	if(this == &to_copy)
		return *this;
	//checks if already exists
	
	trash(root);
	//copies
	copy(root, to_copy.root);
	return *this;
}

tree& operator+(tree & my_tree, const food & to_add)
{
	//wrapper for insert
	my_tree.insert(to_add);
	return my_tree;	


}

tree& operator+(const food & to_add, tree & my_tree)
{
	//wrapper for insert
	my_tree.insert(to_add);
	return my_tree;	


}

tree& tree::operator+=(const food & to_add)
{
	//wrapper for insert
	//this function is the most efficient due
	//to being able to return an l value.
	insert(to_add);
	return *this;
}

ostream& operator<<(ostream& out, const tree & to_print)
{
	//wrapper for display
	to_print.display(out, to_print.root);	
	return out;
}

void tree::display(ostream& out, const node * root) const
{
	//recursive display
	if(!root)
		return;
	
	//we must display this nodes data in between
	//its children so as to display in the correct
	//order.
	display(out, root->go_next(0));
	root->display(0);
	display(out, root->go_next(1));
	root->display(1);
	display(out, root->go_next(2));
	root->display(2);
	display(out, root->go_next(3));
}

int tree::operator()(int type, int qualifier)
{
	//wrapper to search by category
	return search(type, qualifier, root);
}

int tree::search(int type, int qualifier, node * root)
{
	//recursively checks each node if it contains
	//the right data. the node displays its data.
	int success = 0;
	if(!root)
		return success;

	root->search(type, qualifier);
	
	for(int i = 0; i < 4; ++i)
	{
		success = search(type, qualifier, root->go_next(i));
	}
	return success;
}

int tree::display(const char * match)
{
	//recursive display for a passed in name
	return display(match, root);
}

int tree::display(const char * match, node * root)
{
	//finds the object of a given name.
	int success = 0;
	if(!root)
		return success;	

	if(root->search(match))
		success = 1;			

	for(int i = 0; i < 4; ++i)
	{
		success = display(match, root->go_next(i)); 
	}
	return success;

}

int tree::display_all_of_type(int type)
{
	//wrapper for display by type
	return display_all_of_type(type, root);
}

int tree::display_all_of_type(int type, node * root)
{
	//recursively displays all the data of a given type.
	//the node displays the data that is a match
	int success = 0;
	if(!root)
		return success;

	if(root->display_all_of_type(type))
		success = 1;

	for(int i = 0; i < 4; ++i)
	{
		success = display_all_of_type(type, root->go_next(i));
	}
	return success;
}



int tree::insert(const food & to_add)
{
	//adds a new data item to the tree. This is where
	//we check for splitting nodes.
	if(!root)
	{
		//if the tree is empty we can create a new
		//node and add the data here and return.
		root = new node;
		for(int i = 0; i < 4; ++i)
		{
			root->set_next(i, NULL);
		}
		root->set_data(1, to_add);
		return 1;
		
	}
	else if(root && root->full())
	{
		//if root is full we need to split root.
		//we create a new node and point its left
		//to root.
		node * temp = new node;
		temp->set_next(0, root);
		temp->set_next(1, NULL);
		temp->set_next(2, NULL);
		//then point its right to another node.
		node * temp2 = new node;
		temp->set_next(3, temp2);

		//temp2's left and right need to point to
		//the old roots middle right and right.
		temp2->set_next(0, root->go_next(2));
		temp2->set_next(1, NULL);
		temp2->set_next(2, NULL);
		temp2->set_next(3, root->go_next(3));

		//pop roots middle data up.
		temp->set_data(1, root->get_data(1));
		//temp2s middle is old roots right.
		temp2->set_data(1, root->get_data(2));
		//move old roots left over to middle.
		root->set_data(1, root->get_data(0));
		//set the now moved data to NULL.
		root->set_data(0, NULL);
		root->set_data(2, NULL);
		
		//set roots far right to its middle left.	
		root->set_next(3, root->go_next(1));
		root->set_next(1, NULL);
		root->set_next(2, NULL);
		
		//move the root of the tree.
		root = temp;
		
	}
	return insert(root, to_add);		
}

int tree::insert(node *& root, const food & to_add)
{

	//recursively splits nodes and then adds at a leaf.
	if(!root)
		return 0;
	if(root->leaf())
	{
		//if we are at a leaf we need to add the 
		//data and return.
		root->add(to_add);
		return 1;	
	}

	//figures out which node to travel to next
	int next = root->where_to(to_add);

	//a pointer to that node	
	node * temp = root->go_next(next);
	if(temp->full())
	{
		//if the node we are going to travel to
		//next is full we need to split it.
		//first we move the middle data item up
		//to where we are currently located.
		root->add(temp->get_data(1));
		temp->set_data(1, NULL);		
		int size = root->size();
		//we will need the size of our current
		//node since the splits are different.
		//This node, since it just got data and
		//it already had data either has two items
		//or three.
		if(size == 2)
		{
			//in this case the root node has a far
			//left child and a far right child and
			//we will split either to a middle left
			//or middle right child.
			if(next < 2)
			{
				//splits to a middle left.
				//first we need a new
				//node connected to the middle
				//left.
				node * temp2 = new node;
				root->go_next(next + 1) = temp2;
				//then we need the new nodes
				//far left and right to point
				//to the old nodes middle right
				//and far right. The old node was
				//full so it is guaranteed to
				//have 4 children. middle children
				//are NULL.
				
				temp2->set_next(0, temp->go_next(2));
				temp2->set_next(3, temp->go_next(3));
				temp2->set_next(1, NULL);
				temp2->set_next(2, NULL);

				//then we need to set the old
				//nodes far right to its middle
				//left and set the middle children
				//to NULL

				temp->set_next(3, temp->go_next(1));
				temp->set_next(1, NULL);
				temp->set_next(2, NULL);
				//then we need to move
				//the data. the old node
				//and new node will both
				//have a middle data
				//item and one data only

				temp2->set_data(1, temp->get_data(2));
				temp->set_data(1, temp->get_data(0));
				temp->set_data(0, NULL);
				temp->set_data(2, NULL);
					
			}		
			else if(next >= 2)
			{
				//first we will need a new
				//node at roots middle right.
				node * temp2 = new node;
				root->go_next(next - 1) = temp2;
				
				//then we need the new nodes
				//far left and right to point
				//to the old nodes middle left
				//and far left. The old node was
				//full so it is guaranteed to
				//have 4 children. middle children
				//are NULL.
				temp2->set_next(0, temp->go_next(0));
				temp2->set_next(3, temp->go_next(1));
				temp2->set_next(1, NULL);
				temp2->set_next(2, NULL);

				//then we need to set the old
				//nodes far left to its middle
				//right and set the middle children
				//to NULL
				temp->set_next(0, temp->go_next(2));
				temp->set_next(1, NULL);
				temp->set_next(2, NULL);

				//then we need to move
				//the data. the old node
				//and new node will both
				//have a middle data
				//item and one data only

				temp2->set_data(1, temp->get_data(0));
				temp->set_data(1, temp->get_data(2));
				temp->set_data(0, NULL);
				temp->set_data(2, NULL);
			}
		}
		if(size == 3)
		{
			//in this situation root has three
			//children and the split will create a
			//fourth in either the middle left or
			//right node

			if(!root->go_next(1))
			{
				//first make a new node.
				node * temp2 = new node;
				root->go_next(1) = temp2;
				//the split is different if we
				//are splitting the far left into
				//the middle left or either right
				//into the middle left.
				if(next == 0)
				{
					//first set the new nodes far left and right
					//to the old nodes middle right and far
					//right
					temp2->set_next(0, temp->go_next(2));
					temp2->set_next(1, NULL);
					temp2->set_next(2, NULL);
					temp2->set_next(3, temp->go_next(3));

					//then set the old nodes far right
					//to its middle left
					temp->set_next(3, temp->go_next(1));
					temp->set_next(1, NULL);
					temp->set_next(2, NULL);

					//the shift the daata.
					temp2->set_data(1, temp->get_data(2));
					temp->set_data(2, NULL);
					temp->set_data(1, temp->get_data(0));
					temp->set_data(0, NULL);

				}
				else
				{
					//this is a shift from right to left
					//first set the new nodes left and right
					//to the old nodes far left and middle left
					temp2->set_next(0, temp->go_next(0));
					temp2->set_next(1, NULL);
					temp2->set_next(2, NULL);
					temp2->set_next(3, temp->go_next(1));

					//the set the old nodes far left to its middle
					//right
					temp->set_next(0, temp->go_next(2));
					temp->set_next(1, NULL);
					temp->set_next(2, NULL);

					//then shift data
					temp2->set_data(1, temp->get_data(0));
					temp->set_data(0, NULL);
					temp->set_data(1, temp->get_data(2));
					temp->set_data(2, NULL);
						
				}
			}
			else if(!root->go_next(2))
			{
				node * temp2 = new node;
				root->go_next(2) = temp2;
				if(next == 3)
				{
					//this is a shift from right to left
					//first set the new nodes left and right
					//to the old nodes far left and middle left
					temp2->set_next(0, temp->go_next(0));
					temp2->set_next(1, NULL);
					temp2->set_next(2, NULL);
					temp2->set_next(3, temp->go_next(1));

					//the set the old nodes far left to its middle
					//right
					temp->set_next(0, temp->go_next(2));
					temp->set_next(1, NULL);
					temp->set_next(2, NULL);

					//then shift data
					temp2->set_data(1, temp->get_data(0));
					temp->set_data(0, NULL);
					temp->set_data(1, temp->get_data(2));
					temp->set_data(2, NULL);


				}
				else
				{
					//first set the new nodes far left and right
					//to the old nodes middle right and far
					//right
					temp2->set_next(0, temp->go_next(2));
					temp2->set_next(1, NULL);
					temp2->set_next(2, NULL);
					temp2->set_next(3, temp->go_next(3));

					//then set the old nodes far right
					//to its middle left
					temp->set_next(3, temp->go_next(1));
					temp->set_next(1, NULL);
					temp->set_next(2, NULL);

					//then shift data
					temp2->set_data(1, temp->get_data(2));
					temp->set_data(2, NULL);
					temp->set_data(1, temp->get_data(0));
					temp->set_data(0, NULL);
						
				}

			}
		}
	}
	//next may have moved.
	next = root->where_to(to_add);
	
	//move to next and repeat until you come to a leaf.	
	return insert(root->go_next(next), to_add);
}



int client::run()
{
	cout << "1 - add food" << endl;
	cout << "2 - view food" << endl;
	cout << "3 - view by contents" << endl;
	cout << "4 - view by type" << endl;
	cout << "5 - search by name" << endl;
	cout << "6 - quit" << endl;
	int user;
	cin >> user;
	cin.ignore(100, '\n');

	if(user == 1)
	{
		cout << "1 - main course" << endl;
		cout << "2 - desert" << endl;
	       	cout << "3 - drink" << endl;
		cin >> user;
		cin.ignore(100, '\n');	

		if(user == 1)
		{
			main_course temp;
			cin >> temp;
			cin.ignore(100, '\n');
			menu += temp;
		}
		else if(user == 2)
		{
			desert temp;
			cin >> temp;
			cin.ignore(100, '\n');
			menu += temp;
		}
		else if(user == 3)
		{
			drink temp;
			cin >> temp;
			cin.ignore(100, '\n');
			menu += temp;
		}

	}	
	else if(user == 2)
	{
		cout << menu << endl;
	}
	else if(user == 3)
	{
		cout << "What content would you like to" << endl;
		cout << "search for." << endl;
		cout << "1 - calories" << endl;
		cout << "2 - gluten" << endl;
		cout << "3 - lactose" << endl;
		cout << "4 - nut contents" << endl;
		cout << "5 - sugar" << endl;
		cout << "6 - alcohol" << endl;
		cin >> user;
		cin.ignore(100, '\n');
		int user2;
		if(user == 1)
		{
			cout << "What is the maximum calorie count you want." << endl;
		}
		else if(user == 2)
		{
			cout << "0 - I want gluten free" << endl;
			cout << "1 - I want gluten" << endl;
		}
		else if(user == 3)
		{
			cout << "0 - I want lactose free" << endl;
			cout << "1 - I want lactose" << endl;
		}
		else if(user == 4)
		{
			cout << "1 - I am okay with any nut" << endl;
			cout << "2 - I don't want peanuts" << endl;
			cout << "3 - I don't want cashews" << endl;
		      	cout << "4 - I don't want pecans" << endl;	
		}
		else if(user == 5)
		{
			cout << "What is the maximum sugar you want" << endl;
		}
		else if(user == 6)
		{
			cout << "0 - I want no alcohol" << endl;
			cout << "1 - I want alcohol" << endl;
		}

		cin >> user2;
		cin.ignore(100, '\n');
		if(!menu(user, user2))
		{
			cout << "No dishes that meet those requirments are on the menu." << endl;
		}
	}
	else if(user == 4)
	{
		cout << "What type of food do you want?" << endl;
		cout << "1 - main course" << endl;
		cout << "2 - desert" << endl;
		cout << "3 - drink" << endl;
		cin >> user;
		cin.ignore(100, '\n');
		if(!menu.display_all_of_type(user))
		{
			cout << "No dishes of that type are on the menu." << endl;
		}
	}
	else if(user == 5)
	{
		cout << "Please enter the name of the item you wish to search for." << endl;
		char * temp = new char [1000];
		cin.get(temp, 1000, '\n');
		cin.ignore(100, '\n');
		if(!menu.display(temp))
		{
			cout << "No dish by that name exists" << endl;
		}
	}
	else
	{
		return 0;
	}
	return 1;



}	

