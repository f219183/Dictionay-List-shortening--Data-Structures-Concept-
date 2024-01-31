#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<string>
using namespace std;

//struct node: simply an index having address and data
struct nodeLL
{
    string data;
	nodeLL* next = nullptr;
};
//class of linked list
class LL
{
public:

	nodeLL* head = nullptr; // to store address of first node
	nodeLL* curr = nullptr; //extrs pointer to traverse in loops

	LL();
	bool isempty();
	nodeLL* create_node(string);
	void insert_pos(string, string, int);
	string getLastNodeData();
};


#endif