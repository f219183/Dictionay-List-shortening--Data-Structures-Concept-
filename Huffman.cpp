#include<iostream>
#include<string>
#include"Huffman.h"
using namespace std;

LinkedListNode* Huffman::nodeCreat(int val, char input_letter) {
	LinkedListNode* current = new LinkedListNode;
	current->LinkedListData = val;
	current->LinkedListLetter = input_letter;
	current->next = NULL;
	current->firstChild = NULL;
	current->secondChild = NULL;
	return current;
}

void Huffman::LinkedListLinkedListInsertAtFirst(int val, char leter)
{
	LinkedListNode* current = nodeCreat(val, leter);
	if (LinkedListHead == NULL)
	{
		LinkedListHead = current;
		LinkedListTail = current;
	}
	else
	{
		current->next = LinkedListHead;
		LinkedListHead = current;
	}
}

void Huffman::LinkedListInsert(int val, char leter) {
	LinkedListNode* current = new LinkedListNode;
	current->LinkedListLetter = leter;
	current->LinkedListData = val;
	current->next = NULL;
	LinkedListTail->next = current;
	LinkedListTail = current;
}

void Huffman::LinkedListsort(LinkedListNode* temp, LinkedListNode* temp1)
{
	//Now to do ascending sort
	while (temp1 != NULL)
	{
		while (temp != NULL)
		{
			if (temp->LinkedListData > temp1->LinkedListData && temp != temp1)
			{
				swap(temp->LinkedListData, temp1->LinkedListData);
				swap(temp->LinkedListLetter, temp1->LinkedListLetter);
				swap(temp->firstChild, temp1->firstChild);
				swap(temp->secondChild, temp1->secondChild);

			}
			temp = temp->next;
		}
		temp1 = temp1->next;
		temp = LinkedListHead;
	}

}

void Huffman::uniqueChar()
{
	if (LinkedListHead->next != NULL)
	{
		LinkedListNode* current = new LinkedListNode;
		current->LinkedListData = LinkedListHead->LinkedListData + LinkedListHead->next->LinkedListData;
		current->LinkedListLetter = '$';
		current->firstChild = LinkedListHead;
		LinkedListHead = LinkedListHead->next;
		current->firstChild->next = NULL;
		current->secondChild = LinkedListHead;
		LinkedListHead = LinkedListHead->next;
		current->secondChild->next = NULL;

		current->next = LinkedListHead;
		LinkedListHead = current;

		LinkedListsort(LinkedListHead, LinkedListHead);
		uniqueChar();
	}
	if (LinkedListHead->next == NULL && check == false)
	{
		saveLeftNode = LinkedListHead;
		check = true;
	}
	return;
}


void Huffman::encode(string str, LinkedListNode* rootNode, char requiredLetter, string var)
{
	str += var;
	if (rootNode == NULL)
	{
		return;
	}
	encode(str, rootNode->firstChild, requiredLetter, "0");
	if (rootNode->LinkedListLetter == requiredLetter)
	{
		finalString += str;
		return;
	}
	else
		encode(str, rootNode->secondChild, requiredLetter, "1");
}



string Huffman::decode(string code, int codeLength)
{
	finalString = "";
	LinkedListNode* temp = saveLeftNode;
	// char array,,,,, temp to get root again ,,, 
	for (int i = 0; i < codeLength; i++)
	{
		if (code[i] == '0')
		{
			temp = temp->firstChild;
		}
		else
		{
			temp = temp->secondChild;
		}
		if (temp->firstChild == NULL && temp->secondChild == NULL)
		{
			finalString += temp->LinkedListLetter;
			temp = saveLeftNode;
		}
	}
	return finalString;

}

void Huffman::Sorting(char* char_ptr, int* int_ptr, int store_count)
{
	bool isSwapped;
	for (int i = 0; i < store_count; i++)
	{
		isSwapped = false;
		for (int j = 1; j < store_count - i; j++)
		{
			if (int_ptr[j] < int_ptr[j - 1])
			{
				swap(int_ptr[j], int_ptr[j - 1]);
				swap(char_ptr[j], char_ptr[j - 1]);
				isSwapped = true;
			}
		}
		if (!isSwapped)
		{
			break;
		}
	}
}

string Huffman::huffman(string text)
{
	finalString = "";
	////////////////////Pass string here in str
	string str = text;
	int size = str.length();
	int count = 0;
	bool repeat = 0;
	char* char_ptr = new char[size];
	int* int_ptr = new int[size];
	int store_count = 0;
	int rept = 0;

	for (int i = 0; i < size; i++)
	{
		count = 0;
		repeat = 0;
		for (int j = 0; j < size; j++)
		{
			if (str[i] == str[j])
			{
				count++;
			}
		}
		for (int k = 0; k < i; k++)
		{
			if (str[i] == str[k])
			{
				repeat = 1;
			}
		}
		if (!repeat)
		{
			char_ptr[store_count] = str[i];
			int_ptr[store_count] = count;
			store_count++;
		}
	}
	Sorting(char_ptr, int_ptr, store_count);
	for (int i = 0; i < store_count; i++)
	{
		if (i == 0)
			LinkedListLinkedListInsertAtFirst(int_ptr[i], char_ptr[i]);
		else
			LinkedListInsert(int_ptr[i], char_ptr[i]);
	}
	uniqueChar();
	LinkedListNode* rootnode = saveLeftNode;

	for (int i = 0; i < size; i++)
	{
		string strng = {};
		encode(strng, rootnode, str[i], "");
	}

	return finalString;
	////////////////////////////////////////////////////////////////////////////
	// Enter encoded from file in code variable

	//string code = "0000000110010001000111110010011111011001011110111111011001101011";
	//int codeLength = code.length();
	//decode(code, codeLength, rootnode);


}