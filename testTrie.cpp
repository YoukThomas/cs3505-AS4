// testTrie.cpp
// Demonstrates and checks the public behavior required for Trie.
// Compile with the student's Trie.cpp, for example:
// g++ -std=c++17 -Wall -Wextra -pedantic Trie.cpp testTrie.cpp -o testTrie

#include "Trie.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {

int failures = 0;

void check(bool condition, const std::string& description) {
    std::cout << "- " << description << ": ";
    if (condition) {
        std::cout << "PASS\n";
    } else {
        std::cout << "FAIL\n";
        ++failures;
    }
}

bool sameWords(std::vector<std::string> actual,
               std::vector<std::string> expected) {
    // The specification requires the matching words, but does not explicitly
    // require a particular order.  Sorting compares the contents only.
    std::sort(actual.begin(), actual.end());
    std::sort(expected.begin(), expected.end());
    return actual == expected;
}

}  // namespace

int main() {
    std::cout << "Trie behavior tests\n";

    Trie trie;
    check(!trie.contains("cat"),
          "an empty trie does not contain a word");
    check(trie.wordsWithPrefix("").empty(),
          "an empty trie returns no words for the empty prefix");

    trie.insert("cat");
    check(trie.contains("cat"), "an inserted word can be found");
    check(!trie.contains("ca"),
          "a path prefix is not a complete word unless inserted");
    check(!trie.contains("cats"),
          "a longer word is not found when only its prefix was inserted");

    trie.insert("car");
    trie.insert("cart");
    trie.insert("dog");
    trie.insert("door");
    trie.insert("a");
    trie.insert("z");
    trie.insert("cat");  // Duplicate insertion should not duplicate a word.

    check(trie.contains("car") && trie.contains("cart") &&
              trie.contains("dog") && trie.contains("door"),
          "words on shared and separate branches can all be found");
    check(trie.contains("a") && trie.contains("z"),
          "one-letter lowercase words can be stored");
    check(!trie.contains("do"),
          "a shared prefix is not automatically a complete word");
    check(sameWords(trie.wordsWithPrefix("ca"), {"car", "cart", "cat"}),
          "a prefix returns every matching word across branches");
    check(sameWords(trie.wordsWithPrefix("car"), {"car", "cart"}),
          "a complete word can also be a prefix of another word");
    check(sameWords(trie.wordsWithPrefix("do"), {"dog", "door"}),
          "a different branch has its own prefix matches");
    check(trie.wordsWithPrefix("zoo").empty(),
          "a missing prefix returns no words");
    check(sameWords(trie.wordsWithPrefix(""),
                    {"a", "car", "cart", "cat", "dog", "door", "z"}),
          "the empty prefix returns all stored words without duplicates");

    std::cout << "\nCopy-constructor tests\n";
    Trie copied(trie);
    check(sameWords(copied.wordsWithPrefix(""), trie.wordsWithPrefix("")),
          "a copy contains the same words as the original");
    copied.insert("cow");
    trie.insert("dove");
    check(copied.contains("cow") && !trie.contains("cow"),
          "adding to a copy does not change the original");
    check(trie.contains("dove") && !copied.contains("dove"),
          "adding to the original does not change the copy");

    std::cout << "\nAssignment-operator tests\n";
    Trie assigned;
    assigned.insert("old");
    assigned = trie;
    check(sameWords(assigned.wordsWithPrefix(""), trie.wordsWithPrefix("")),
          "assignment replaces previous contents with the source contents");
    check(!assigned.contains("old"),
          "assignment removes words that belonged only to the destination");
    assigned.insert("ant");
    check(assigned.contains("ant") && !trie.contains("ant"),
          "an assigned trie is independent of its source");

    std::cout << "\nDestruction and dynamic-memory exercise\n";
    {
        Trie temporary;
        temporary.insert("ant");
        temporary.insert("anteater");
        temporary.insert("antelope");
        temporary.insert("bat");
        Trie temporaryCopy(temporary);
        Trie temporaryAssigned;
        temporaryAssigned = temporaryCopy;
        check(temporaryAssigned.contains("anteater") &&
                  temporaryAssigned.contains("bat"),
              "copied and assigned dynamically-built tries remain usable");
    }
    if (failures == 0) {
        std::cout << "\nAll Trie demonstrations passed.\n";
        return 0;
    }

}