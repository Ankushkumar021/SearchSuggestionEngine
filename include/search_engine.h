#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "trie.h"
#include <vector>
#include <string>

class SearchEngine {
public:
    SearchEngine(const std::string& filename);
    ~SearchEngine();

    void loadFromFile();
    void saveToFile();

    void addKeyword(const std::string& word, int freq = 1);
    void searchKeyword(const std::string& word);
    std::vector<std::pair<std::string, int>> suggest(const std::string& prefix, int k = 5);

    void printStats();
private:
    std::string filename;
    Trie trie;
};

#endif // SEARCH_ENGINE_H
