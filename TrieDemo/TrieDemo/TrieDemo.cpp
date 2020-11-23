#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"
using namespace std;

int main()
{
    Trie<string> trie;
    fstream newfile;
    newfile.open("Dictionary.txt", fstream::in);
    if (newfile.is_open()) { 
        string tp;
        while (getline(newfile, tp)) {
            if (!trie.ContainsKey(tp)) {
                trie.Insert(tp, tp);
            }
        }
        newfile.close();
    }
    while (true)
    {
        cout << endl << "Input part of a word" << endl;
        string input;
        cin >> input;
        vector<string> cmpltedStrings = trie.GetValuesWithPrefix(input, 15);
        cout << "-------" << endl;
        for (int i = 0; i < cmpltedStrings.size(); i++) {
            cout << cmpltedStrings[i] << endl;
        }
    }
}

