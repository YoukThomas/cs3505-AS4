#include "Trie.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

int main(int argc, char** argv){
    std::vector<std::string> resultString;

    if (argc > 3 || argc < 3){
        cout << "Incorrect number of arguments. Please ensure only two arguments are given." << endl;
        return 0;
    }

    Trie trie;
    std::ifstream dictionary(argv[1]);
    std::ifstream query(argv[2]);
    std::string output;
    std::vector<std::string> matchedStrings;

    if (!dictionary.is_open() || !query.is_open()){
        cout << "File error! Check that the files are valid!" << endl;
        return 0;
    }

    while (getline(dictionary, output)){
        trie.insert(output);
    }

    dictionary.close();

    while (getline(query, output)){
        cout << "Checking for " << output << endl;
        if (trie.contains(output) == 1){
            cout << "True" << endl;
            matchedStrings = trie.wordsWithPrefix(output);
            resultString.push_back(matchedStrings[0]);
        }
        else {
            cout << "False" << endl;
        }
        
        
    }
    cout << "Matched strings: " << endl;
    for (int i = 0; i < resultString.size(); i++){
        cout << resultString[i] << endl;
    }

    cout << endl;
    query.close();
}