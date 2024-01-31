#include<iostream>
#include<Windows.h>
#include"UsefulFunctions.h"
using namespace std;

//function to change the color of text (That is to be displayed next)
void UsefulFunctions::setTextColor(int colorCode)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

//reverses the string
string UsefulFunctions::reverseString(string text)
{
    int jPlus = text.length() - 1;
    char temp;
    for (int i = 0;i < text.length() / 2;i++)
    {
        temp = text[i];
        text[i] = text[jPlus];
        text[jPlus] = temp;
        jPlus--;
    }
    return text;
}

//checks if the string contains letters only
bool UsefulFunctions::alphabetsCheck(string word)
{
    for (int i = 0;i < word.length();i++)
    {
        if (word[i] < 97 || word[i] > 122)
        {
            return false;
        }
    }
    return true;
}

//converts string to lowercase letters
string UsefulFunctions::toLowerCase(string word)
{
    for (int i = 0;i < word.length();i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
        {
            word[i] += 32;
        }
    }
    return word;
}
