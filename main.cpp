#include<iostream>
#include<conio.h>
#include<string>
#include<cstring>
#include<fstream>
#include"UsefulFunctions.h"
#include"TrieTree.h"
#include"Huffman.h"
using namespace std;


int suggestionSelection = 0;
string displayedSuggestion[18];
int displayedSuggestionCount = 0;
int displayedPageNumber = 0;
bool encode = false;

string updateDisplay(string text, bool &nextLineSignal, int noSpaceCounter, string suggestionCursor)
{
	for (int i = 0;i < 18;i++)
	{
		displayedSuggestion[i] = "";
	}

	if (suggestionCursor == "down")
	{
		if (suggestionSelection < 18 && suggestionSelection < displayedSuggestionCount)
		{
			suggestionSelection++;
		}
	}
	if (suggestionCursor == "up")
	{
		if (suggestionSelection > 1)
		{
			suggestionSelection--;
		}
	}
	TrieTree Tree;
	ifstream in;
	LL* suggestionList = new LL;
	in.open("dictionary.txt");
	if (!in)
	{
		cout << "Dictionary couldn't be opened";
	}
	else
	{
		Tree.loadTreeFromDictionary(in);
	}
	UsefulFunctions U;
	int currentPage = displayedPageNumber + 1;
	int totalPages = (text.length() / 1098) + 1;
	int characters = text.length();
	int displayCount = (displayedPageNumber * 1098) + 1;
	int pageLines = text.length() / 61;
	if ((text.length() % 61) != 0)
	{
		pageLines++;
	}

	bool anySpaceFound = false;
	for (int i = 1;i < text.length();i++)
	{
		if (text[i] == ' ')
		{
			anySpaceFound = true;
		}
	}

	if (characters % 61 == 1 && nextLineSignal == false && characters > 61 && noSpaceCounter < 62 && anySpaceFound == true)
	{
	
		string tempText = "";
		for (int i = characters - 1;i>=0;i--)
		{
			if (text[i] == ' ')
			{
				break;
			}
			else
			{
				
				tempText += text[i];
				text[i] = ' ';
			}
		}
		tempText = U.reverseString(tempText);
		text.erase(text.length() - 1, 1);
		text += ' ';
		text += tempText;
		characters = text.length();
		nextLineSignal = false;
		anySpaceFound = false;
	}

	if (text[text.length() - 1] != ' ')
	{
		string lastWord;
		int i = characters;
		while (text[i] != ' ' && i > 0)
		{
			i--;
			lastWord += text[i];
		}

		if (lastWord[lastWord.length() - 1] == ' ')
		{
			lastWord.erase(lastWord.size() - 1, 1);
		}
			
		lastWord = U.reverseString(lastWord);
		lastWord = U.toLowerCase(lastWord);
		bool isWord = true;
		TreeNode* lastLetterNode = Tree.getRoot();

		for (int i = 0; i < lastWord.length(); ++i)			
		{
			lastLetterNode = lastLetterNode->alphabets[static_cast<int>(lastWord[i]) - 97];
			if (!lastLetterNode)
			{
				isWord = false;
				break;
			}
		}

		char suggestedWord[50];
		if (isWord)
		{
			Tree.suggestions(suggestionList, lastLetterNode, suggestedWord, lastWord, 0);
		}
	}

	system("CLS");
	nodeLL* tempLL = suggestionList->head;
	if (suggestionCursor == "none")
	{
		suggestionSelection = 0;
	}
	if (tempLL != NULL && suggestionCursor == "none")
	{
			suggestionSelection++;
	}
	displayedSuggestionCount = 0;

	if (encode == true)
	{
		suggestionSelection = 0;
	}
	cout << endl; 
	cout << "     ";
	U.setTextColor(2);
	cout << "[";
	U.setTextColor(7);
	cout << " encode";
	cout << "    ";
	U.setTextColor(2);
	cout << "]";
	U.setTextColor(7);
	cout << " decode";
	//cout << "                           ";
	cout << "    ";
	U.setTextColor(2);
	cout << ",";
	U.setTextColor(7);
	cout << " page (-)";
	cout << "    ";
	U.setTextColor(2);
	cout << ".";
	U.setTextColor(7);
	cout << " page (+)";
	cout << "    ";
	U.setTextColor(2);
	cout << ";";
	U.setTextColor(7);
	cout << " selection";
	cout << "    ";
	U.setTextColor(2);
	cout << "\\";
	U.setTextColor(7);
	cout << " up";
	cout << "    ";
	U.setTextColor(2);
	cout << "/";
	U.setTextColor(7);
	cout << " down";
	cout << "    ";
	U.setTextColor(2);
	cout << "=";
	U.setTextColor(7);
	cout << " save";
	cout << endl << endl;
	int greyLines = ((currentPage - 1) * 18) + 1;
	int greyNumbers;
	if (currentPage == totalPages)
	{
		greyNumbers = ((text.length() % 1098) / 61) + 1;
	}
	else
	{
		greyNumbers = 18;
	}
	cout << "     __________________________ <TEXT EDITOR> ___________________________" << " " << "____ <SUGGESTIONS> ____" << endl;
	for (int i = 0;i < 19;i++)
	{
		cout << "    |";
		if (i > 0)
		{
			if (i > greyNumbers)
			{
				U.setTextColor(8);
			}

			if (i < 10 && currentPage == 1)
			{
				cout << " <" << "0" << greyLines << "> ";
				greyLines++;
			}
			else
			{
				cout << " <" << greyLines << "> ";
				greyLines++;
			}
			U.setTextColor(7);
		}
		else
		{
			cout << "      ";
		}
		for (int j = 0;j < 61;j++)
		{
			if (displayCount < characters && i>0)
			{
				cout << text[displayCount];
				displayCount++;
			}
			else
			{
				cout << " ";
			}
		}
		cout << " |";


		if (i == 0)
		{

			for (int j = 0;j < 23;j++)
			{
				cout << " ";
			}
		}

			if (suggestionSelection == i && i>0)
			{
				string sugg = "";
				U.setTextColor(9);
				cout << " -> ";
				U.setTextColor(7);
				if (suggestionList->head != NULL)
				{
					
					if(tempLL != NULL)
					{
						sugg = tempLL->data;
						while (sugg.length() >= 18)
						{
							if (tempLL->next == NULL)
							{
								break;
							}
							tempLL = tempLL->next;
							sugg = tempLL->data;
						}
						if (sugg.length() < 18)
						{
							if (suggestionSelection == i)
							{
								U.setTextColor(9);
							}	
							displayedSuggestion[i-1] = sugg;
							displayedSuggestionCount++;
							cout << sugg;
							U.setTextColor(7);	
						}

							tempLL = tempLL->next;
				
					}
					
					if (sugg.length() < 18)
					{
						for (int j = 0;j < 19 - sugg.length();j++)
						{
							cout << " ";
						}
					}
					else
					{
						for (int j = 0;j < 19;j++)
						{
							cout << " ";
						}
					}
					
				}
				else
				{
					for (int j = 0;j < 19;j++)
					{
						cout << " ";
					}
				}
			}
			else if(i>0)
			{
				string sugg = "";
				cout << "    ";
				if (suggestionList->head != NULL)
				{
					if (tempLL != NULL)
					{
						sugg = tempLL->data;
						while (sugg.length() >= 18)
						{
							if (tempLL->next == NULL)
							{
								break;
							}
							tempLL = tempLL->next;
							sugg = tempLL->data;
						}
						if (sugg.length() < 18)
						{
							if (suggestionSelection == i)
							{
								U.setTextColor(9);
							}
							displayedSuggestion[i-1] = sugg;
							displayedSuggestionCount++;
							cout << sugg;
							U.setTextColor(7);
						}
					
							tempLL = tempLL->next;
					
					}


					if (sugg.length() < 18)
					{
						for (int j = 0;j < 19 - sugg.length();j++)
						{
							cout << " ";
						}
					}
					else
					{
						for (int j = 0;j < 19;j++)
						{
							cout << " ";
						}
					}
				}
				else
				{
					for (int j = 0;j < 19;j++)
					{
						cout << " ";
					}
				}
			}
		
		cout << "|";
		cout << endl;
	}
	cout << "     ____________________________________________________________________" << " " << "_______________________" << endl;
	cout << "     page " << currentPage << " of " << totalPages << "\t" << pageLines << " lines" << "\t" << characters << " characters" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t ";
	cout << "(";
	U.setTextColor(2);
	cout << "`";
	U.setTextColor(7);
	cout << ")";
	U.setTextColor(6);
	cout << " exit" << endl;
	U.setTextColor(7);
	displayCount = 0; 
	cout << endl << "            21F-9183               21F-9262               21F-9613" << endl;
	delete suggestionList;

	return text;
}

int main()
{
	UsefulFunctions U;
	Huffman H;
	char currentLetter = NULL;
	string text = " ";
	displayedPageNumber = text.length() / 1098;
	bool nextLine = false;
	int noSpaceCounter = 0;
	int characters = 0;
	updateDisplay(text, nextLine, noSpaceCounter, "none");
	//text.erase(text.size() - 1, 1);
	while (currentLetter != '`')
	{
		characters = text.length();
		if (text.length() % 61 == 60)
		{
			nextLine = false;
		}
		currentLetter = _getch();

		

		if (currentLetter != ' ')
		{
			noSpaceCounter++;
		}
		else
		{
			noSpaceCounter = 0;
		}

		if (currentLetter == '/')
		{
			if (characters > 0)
			{
				text = updateDisplay(text, nextLine, noSpaceCounter, "down");
			}			
			continue;
		}

		if (currentLetter == '\\')
		{
			if (characters > 0)
			{
				text = updateDisplay(text, nextLine, noSpaceCounter, "up");
			}
			continue;
		}

		if (currentLetter == '[' && encode == false)
		{
			if (characters > 0)
			{
				text = H.huffman(text);
				displayedPageNumber = text.length() / 1098;
				encode = true;
				text = updateDisplay(text, nextLine, noSpaceCounter, "none");
			}
			continue;
		}

		if (currentLetter == ']' && encode == true)
		{
			if (characters > 0)
			{
				text = H.decode(text,text.length());
				displayedPageNumber = text.length() / 1098;
				encode = false;
				text = updateDisplay(text, nextLine, noSpaceCounter, "none");
			}
			continue;
		}

		if (currentLetter == '=')
		{
				string fileName;
				string tempText = H.huffman(text);
				system("CLS");
				cout << endl;
				U.setTextColor(1);
				cout << "\t\t\tFile Name | ";
				U.setTextColor(7);
				cin >> fileName;
				fstream out;
				out.open(fileName + ".txt", ios::out);
				out << text;
				out.close();
				system("CLS");
				cout << endl;
				cout << "\t\t\tFile";
				U.setTextColor(2);
				cout << " Saved ";
				U.setTextColor(7);
				cout << "Successfully." << endl;
				displayedPageNumber = text.length() / 1098;
				nextLine = false;
				updateDisplay(text, nextLine, 0, "none");
				continue;
		}

		if (currentLetter == ';')
		{
			displayedPageNumber = text.length() / 1098;
			if (characters > 0 && suggestionSelection >= 1)
			{
				int tempCount = characters - 1;
				while (text[tempCount] != ' ' && characters > 0)
				{
					characters = text.length();
					text.erase(text.size() - 1, 1);
					tempCount--;
				}
				text += displayedSuggestion[suggestionSelection - 1];
				text += " ";
				text = updateDisplay(text, nextLine, noSpaceCounter, "none");
			}
			continue;
		}

		if (currentLetter == ',' && displayedPageNumber > 0)
		{
			displayedPageNumber--;
			text = updateDisplay(text, nextLine, noSpaceCounter, "none");
			continue;
		}

		if (currentLetter == '.' && displayedPageNumber < text.length()/1098)
		{
			displayedPageNumber++;
			text = updateDisplay(text, nextLine, noSpaceCounter, "none");
			continue;
		}

		if ((text.length() % 61) == 0 && (currentLetter == ' ') && nextLine == false)
		{
			nextLine = true;
		}
		else
		{
			nextLine = false;
			if ((currentLetter >= 97 && currentLetter <= 122) || (currentLetter >= 65 && currentLetter <= 90) || (currentLetter == ' '))
			{

				text += currentLetter;
			}
			
		}
		displayedPageNumber = text.length() / 1098;
		text = updateDisplay(text, nextLine, noSpaceCounter, "none");
	}

}