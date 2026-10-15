#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <vector>
/// @brief A class representing a Trie. Uses an array of Trie pointers to track its children.
class Trie{
    Trie* children[26];
    bool endOfWord;

public:
    /// @brief A simple constructor for the Trie class. Populates the children array with nullptr and sets the current endOfWord flag to false.
    Trie();

    /// @brief A copy constructor. Returns a Trie object with the same values as the given Trie.
    /// @param oldTrie The Trie object to copy from.
    Trie(const Trie &oldTrie);

    /// @brief A destructor for the Trie class. iterates through each of the children and calls delete.
    ~Trie();

    /// @brief An overload of the "=" operator. Calls "swap()" on this object's children array and a given Trie's children array.
    /// @param other The Trie to copy data from.
    /// @return This Trie, with data from the given Trie;
    Trie& operator=(Trie other);
    
    /// @brief Inserts a word into the Trie.
    /// @param word The word to insert.
    void insert(std::string word);

    /// @brief Checks the Trie to see if a given word has been entered. Does not alter the Trie.
    /// @param word The word to check for.
    /// @return True if the word is in the Trie, false if not.
    bool contains(std::string word) const;

    /// @brief Checks how many words are present in the Trie that include the given prefix. If the prefix is an empty string, returns all words in the current Trie.
    /// @param prefix The prefix to check for.
    /// @return A vector of strings containing each matched word with the given prefix.
    std::vector<std::string> wordsWithPrefix(std::string prefix) const;

private:
    /// @brief A helper method to conduct a deep copy of a Trie.
    /// @param children The next child nodes to iterate through and copy.
    void deepCopy(Trie* children[], Trie* const oldChildren[]);

    /// @brief A helper method that recursively searches the Trie to find a given word.
    /// @param word The word to search for.
    /// @return True if found, False if not. Passed to the main contains() method.
    bool containsRecursion(std::string word) const;

    /// @brief A helper method that recursively traverses the Trie to find words matching the given prefix. Passes a string vector down each recursion to add to and eventually return.
    /// @param prefix The prefix to start from in the Trie.
    /// @param stringVector Used to store and return any completed words found in the Trie.
    /// @param string A string passed down each recursion to keep track of the letters so far. Does not carry back upwards.
    /// @return A vector containing the complete words found.
    std::vector<std::string> wordsWithPrefixRecursion(const std::string& prefix, std::vector<std::string>& stringVector, std::string string) const;

};
#endif