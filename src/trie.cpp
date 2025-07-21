#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}
Trie::~Trie() {
    clear();
}
void Trie::clear() {
    deleteTrie(root);
    root = new TrieNode();
}

void Trie::deleteTrie(TrieNode* node) {
    if (!node) return;
    for (auto& [_, child] : node->children)
        deleteTrie(child);
    delete node;
}

void Trie::insert(const std::string& word, int freq) {
    TrieNode* curr = root;
    for (char ch : word) {
        if (!curr->children.count(ch))
            curr->children[ch] = new TrieNode();
        curr = curr->children[ch];
    }
    curr->isEndOfWord = true;
    curr->frequency += freq;
}

void Trie::increaseFrequency(const std::string& word) {
    TrieNode* curr = root;
    for (char ch : word) {
        if (!curr->children.count(ch)) return; // word not present
        curr = curr->children[ch];
    }
    if (curr->isEndOfWord)
        curr->frequency += 1;
}

bool Trie::search(const std::string& word) {
    TrieNode* curr = root;
    for (char ch : word) {
        if (!curr->children.count(ch)) return false;
        curr = curr->children[ch];
    }
    return curr->isEndOfWord;
}

TrieNode* Trie::findNode(const std::string& prefix) {
    TrieNode* curr = root;
    for (char ch : prefix) {
        if (!curr->children.count(ch)) return nullptr;
        curr = curr->children[ch];
    }
    return curr;
}

void Trie::dfs(TrieNode* node, std::string& current,
               std::vector<std::pair<std::string, int>>& result) {
    if (node->isEndOfWord) {
        result.push_back({current, node->frequency});
    }
    for (auto& [ch, child] : node->children) {
        current.push_back(ch);
        dfs(child, current, result);
        current.pop_back();
    }
}

void Trie::getAllWordsWithPrefix(const std::string& prefix,
                                 std::vector<std::pair<std::string, int>>& result) {
    TrieNode* node = findNode(prefix);
    if (!node) return;
    std::string current = prefix;
    dfs(node, current, result);
}
