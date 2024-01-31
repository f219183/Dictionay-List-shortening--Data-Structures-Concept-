#ifndef TRIETREE_H
#define TRIETREE_H

#include<iostream>
#include<fstream>
#include"LinkedList.h"
using namespace std;

class TreeNode {
public:
	char assignedAlphabet;
	TreeNode* alphabets[26];	
	bool completeWord;
	bool isDiscovered;
};

class TrieTree {
private:
	TreeNode* rootNode;
	int count1 = 0;
public:
	TrieTree();
	TreeNode* createNode();
	TreeNode* getRoot();
	void loadTreeFromDictionary(ifstream& in);
	void suggestions(LL*, TreeNode*, char*, string tempWord, int);
};
#endif