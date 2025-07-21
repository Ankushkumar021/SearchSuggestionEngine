#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    int frequency; // Frequency for ranking
    TrieNode() : isEndOfWord(false), frequency(0) {}
};

class Trie {
public:
    Trie();
    ~Trie();

    void insert(const std::string& word, int freq = 1);
    bool search(const std::string& word);
    void increaseFrequency(const std::string& word);
    void getAllWordsWithPrefix(const std::string& prefix,
                               std::vector<std::pair<std::string, int>>& result);

    void clear();

private:
    TrieNode* root;

    void deleteTrie(TrieNode* node);
    void dfs(TrieNode* node, std::string& current,
             std::vector<std::pair<std::string, int>>& result);
    TrieNode* findNode(const std::string& prefix);
};

#endif // TRIE_H
