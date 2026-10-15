#include "Trie.cpp"

int main(){
    Trie trie;

    trie.insert("a");
    trie.insert("ab");
    trie.insert("abs");
    Trie assigned;
    assigned = trie;
}