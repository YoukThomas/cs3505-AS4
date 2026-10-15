#include "./include/Trie.h"
#include <vector>
#include <string>
#include <iostream>
using std::swap;

const int maxArraySize = 26;

Trie::Trie() : children(){
    endOfWord = false;
}

Trie::Trie(const Trie &oldTrie) : endOfWord(oldTrie.endOfWord){
    deepCopy(children, oldTrie.children);
}

void Trie::deepCopy(Trie* children[], Trie* const oldChildren[]){
    for (int i = 0; i < maxArraySize; i++){
        if (oldChildren[i]){
            children[i] = new Trie(*oldChildren[i]);
        }
        else{
            children[i] = nullptr;
        }
    }
}


Trie::~Trie(){
    for (int i = 0; i < maxArraySize; i++){
        if (children[i]){
            delete children[i];
        }
    }
}

Trie& Trie::operator=(Trie other){
    for (int i = 0; i < maxArraySize; i++){
        swap(children[i], other.children[i]);
    }
    swap(endOfWord, other.endOfWord);
    return *this;
}

void Trie::insert(std::string word){
    int index = word[0] - 'a';
    Trie* trie = new Trie();
    if (word.length() > 1){
        if (!children[index]){
            children[index] = trie;
        }
            children[index]->insert(word.substr(1));
    }
    else {
        children[index] = trie;
        children[index]->endOfWord = true;
    }
    
}

bool Trie::contains(std::string word) const{
    if (word.length() < 1){
        return false;
    }
    else{
        for (int i = 0; i < word.length() - 1; i++){
            if (word[i] - 'a' < 0 || word[i] - 'a' > maxArraySize){
                return false;
            }
            
        }
        return containsRecursion(word);
    }
}

bool Trie::containsRecursion(std::string word) const{
    int index = word[0] - 'a';
    if (!children[index]){
        return false;
    }
    else{
        if (word.length() > 1){
            return children[index]->containsRecursion(word.substr(1));
        }
        else{
            return children[index]->endOfWord;
        }
    }
}

std::vector<std::string> Trie::wordsWithPrefix(std::string prefix) const{
    std::vector<std::string> sVec;
    std::string str;
    return wordsWithPrefixRecursion(prefix, sVec, str);
}

std::vector<std::string> Trie::wordsWithPrefixRecursion(const std::string& prefix, std::vector<std::string>& stringVector, std::string string) const{
    //traverse the trie until you've passed the prefix or you find the prefix is not in the trie
    //enter each child
    //check if endOfWord, if so add to string vector
    //search child's children, repeat until no children left
    //return the completed string vector
    
    if (prefix.length() > 0){    
        int index = prefix[0] - 'a';
        string += prefix[0];
        if (!children[index]){
            return stringVector;
        }
        children[index]->wordsWithPrefixRecursion(prefix.substr(1), stringVector, string);
    }
    else{
        if (endOfWord){
            stringVector.push_back(string);

        }
        for (int i = 0; i < maxArraySize; i++){
            if (children[i]){
            std::string tempString = string;
                tempString += 'a' + i;
                children[i]->wordsWithPrefixRecursion(prefix, stringVector, tempString);
            }
        }
    }
    return stringVector;
}