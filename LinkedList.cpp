#include<iostream>
#include"LinkedList.h"

//constructor
LL::LL()
{
	head = nullptr;
	curr = nullptr;
}
//function to check if linked list is empty
bool LL::isempty()
{
	//if head is empty the list is empty
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//function to create a new note and assign the data 
nodeLL* LL::create_node(string value)
{
	nodeLL* temp = new nodeLL;
	temp->data = value;
	return temp; // returns address of the new node
}
//function to insert values at beginning, last and middle
void LL::insert_pos(string x, string position, int index)
{

	//beginning

	if (position == "beginning")
	{
		if (isempty())
		{
			head = create_node(x);
		}
		else
		{
			nodeLL* temp = create_node(x); //assigning new node to a temporary pointer of type node
			temp->next = head;
			head = temp;

		}
	}
	//middle
	else if (position == "middle")
	{
		if (isempty())
		{
			if (index == 1)
			{
				insert_pos(x, "beginning", index); // calls the function again
			}
			else
			{
				cout << "Invalid Position";
			}
		}
		else
		{
			int count = 1;
			this->curr = this->head;
			while (curr->next != NULL) //iterrating  to count the number of nodes in linked list
			{
				count++;
				curr = curr->next;
			}
			if (index <= count)
			{

				nodeLL* temp = create_node(x);
				this->curr = this->head; //assigns head to current pointer
				for (int i = 1; i < index - 1; i++)
				{
					curr = curr->next;
				}
				temp->next = curr->next;
				curr->next = temp;

			}
			else if (index == (count + 1))
			{
				insert_pos(x, "last", index);
			}
			else
			{
				cout << "Invalid Position";
			}
		}


	}
	//end
	else if (position == "last")
	{
		if (isempty())
		{
			insert_pos(x, "beginning", index);
		}
		else
		{
			nodeLL* temp = create_node(x);
			this->curr = this->head;
			while (curr->next != NULL) //sets the current pointer to last node
			{
				curr = curr->next;
			}
			curr->next = temp;
		}
	}
}

string LL::getLastNodeData()
{
	if (head != NULL)
	{
		this->curr = this->head;
		while (curr->next != NULL)
		{
			//cout << curr->data << " " << endl;
			curr = curr->next;
		}
		return curr->data;
	}
}
