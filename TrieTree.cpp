#include<iostream>
#include<fstream>
#include"TrieTree.h"
#include"UsefulFunctions.h"
#include"LinkedList.h"
using namespace std;

TreeNode* TrieTree::getRoot()
{
	return rootNode;
}

TrieTree::TrieTree()
{
	rootNode = createNode();
}

TreeNode* TrieTree::createNode()
{
	TreeNode* node = new TreeNode;
	for (int i = 0; i < 26; ++i)
	{
		node->alphabets[i] = nullptr;
	}

	node->completeWord = false;
	node->assignedAlphabet = '*';
	node->isDiscovered = false;
	return node;
}

void TrieTree::loadTreeFromDictionary(ifstream& in)
{
	UsefulFunctions U;
	string currentWord;				//temp string to store each word temporarily
	size_t wordLength;
	TreeNode* currNodePtr;
	while (!in.eof())				//iterating through each word
	{
		in >> currentWord;
		currentWord = U.toLowerCase(currentWord);
		if (U.alphabetsCheck(currentWord) == true)
		{

			wordLength = currentWord.length();
			currNodePtr = rootNode;
			for (int j = 0; j < wordLength; j++)
			{
				if (currNodePtr->alphabets[static_cast<int>(currentWord[j]) - 97])
				{
					currNodePtr = currNodePtr->alphabets[static_cast<int>(currentWord[j]) - 97];
					if (j == wordLength - 1)
						currNodePtr->completeWord = true;
				}
				else
				{
					currNodePtr->alphabets[static_cast<int>(currentWord[j]) - 97] = createNode();
					currNodePtr = currNodePtr->alphabets[static_cast<int>(currentWord[j]) - 97];
					currNodePtr->assignedAlphabet = currentWord[j];
					if (j == wordLength - 1)
						currNodePtr->completeWord = true;
				}

			}
		}
	}
}

string cStrToStr(char* str, int n)
{
	string temp;
	for (int i = 0; i < n; i++)
	{
		temp += str[i];
	}
	return temp;
}

void TrieTree::suggestions(LL* list, TreeNode* root, char* word, string lastWord, int totalSuggestions)
{
	if (root == nullptr)
	{
		return;
	}
	if (root->completeWord)
	{
		
		string temp1 = lastWord + cStrToStr(word, totalSuggestions + lastWord.length());
		string temp2;
		for (int i = 0;i < temp1.length();i++)
		{
			if (temp1[i] >= 97 && temp1[i] <= 122)
			{
				temp2 += temp1[i];
			}
		}
   
		list->insert_pos(temp2, "beginning", 0);
	}
	for (int i = 0; i < 26; i++)
	{
		if (root->alphabets[i] != NULL)
		{
			
			word[totalSuggestions] = root->alphabets[i]->assignedAlphabet;
			suggestions(list, root->alphabets[i], word, lastWord, totalSuggestions + 1);
		}
	}
}