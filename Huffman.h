#ifndef HUFFMAN_H
#define HUFFMAN_H

#include<iostream>
using namespace std;
struct LinkedListNode {
	int LinkedListData = 0;
	char cypher = '0';
	char LinkedListLetter = {};
	LinkedListNode* next = NULL;
	LinkedListNode* firstChild = NULL;
	LinkedListNode* secondChild = NULL;
};

class Huffman {
public:
	string finalString = "";
	LinkedListNode* LinkedListHead = NULL;
	LinkedListNode* LinkedListTail = NULL;
	bool check = false;
	LinkedListNode* saveLeftNode;
	LinkedListNode* nodeCreat(int val, char input_letter);
	void LinkedListLinkedListInsertAtFirst(int val, char leter);
	void LinkedListInsert(int val, char leter);
	void LinkedListsort(LinkedListNode* temp, LinkedListNode* temp1);
	void uniqueChar();
	void encode(string str, LinkedListNode* rootNode, char requiredLetter, string var);
	string decode(string code, int codeLength);
	void Sorting(char* char_ptr, int* int_ptr, int store_count);
	string huffman(string text);
};

#endif