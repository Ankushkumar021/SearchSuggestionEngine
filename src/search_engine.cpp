#include "search_engine.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>

SearchEngine::SearchEngine(const std::string& filename)
    : filename(filename) {
    loadFromFile();
}

SearchEngine::~SearchEngine() {
    saveToFile();
}

void SearchEngine::loadFromFile() {
    trie.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "❌ Failed to open file: " << filename << "\n";
        return;
    }

    std::string line;
    while (getline(fin, line)) {
        std::cout << "Reading line: " << line << std::endl; // DEBUG PRINT
        std::istringstream iss(line);
        std::string word;
        int freq = 1;
        if (getline(iss, word, ':')) {
            std::string freqStr;
            if (getline(iss, freqStr)) {
                freq = std::stoi(freqStr);
                std::cout << "Parsed: " << word << " -> " << freq << "\n"; // DEBUG PRINT
                trie.insert(word, freq);
            }
        }
    }
}


void SearchEngine::saveToFile() {
    std::ofstream fout(filename);
    std::vector<std::pair<std::string, int>> allWords;
    trie.getAllWordsWithPrefix("", allWords);
    for (auto& [word, freq] : allWords) {
        fout << word << ":" << freq << std::endl;
    }
}

void SearchEngine::addKeyword(const std::string& word, int freq) {
    trie.insert(word, freq);
    saveToFile();
}

void SearchEngine::searchKeyword(const std::string& word) {
    if (trie.search(word)) {
        trie.increaseFrequency(word);
        std::cout << "> '" << word << "' found! Frequency increased.\n";
        saveToFile();
    } else {
        std::cout << "> '" << word << "' not present. Adding with freq=1.\n";
        trie.insert(word, 1);
        saveToFile();
    }
}

std::vector<std::pair<std::string, int>> SearchEngine::suggest(const std::string& prefix, int k) {
    std::vector<std::pair<std::string, int>> found;
    trie.getAllWordsWithPrefix(prefix, found);
    // Use min-heap to keep top-K
    auto cmp = [](const std::pair<std::string, int>& a,
                  const std::pair<std::string, int>& b) {
        if (a.second == b.second) return a.first > b.first;
        return a.second > b.second;
    };
    std::priority_queue<
        std::pair<std::string, int>,
        std::vector<std::pair<std::string, int>>,
        decltype(cmp)
    > minHeap(cmp);

    for (auto& p : found) {
        minHeap.push(p);
        if ((int)minHeap.size() > k) minHeap.pop();
    }

    std::vector<std::pair<std::string, int>> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void SearchEngine::printStats() {
    std::vector<std::pair<std::string, int>> all;
    trie.getAllWordsWithPrefix("", all);
    std::cout << "Total keywords: " << all.size() << "\n";
}
