#include "search_engine.h"
#include <iostream>
#include <cctype>
#include <limits>

std::string toLower(const std::string& s) {
    std::string out;
    for (char ch : s) out += std::tolower(ch);
    return out;
}

int main() {
    SearchEngine engine("data/keywords.txt");
    std::cout << "======== E-Commerce Search Suggestion Engine ========" << std::endl;
    while (true) {
        std::cout << "\nCommands: add | search | suggest | stats | exit\n> ";
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "exit") break;
        else if (cmd == "add") {
            std::string word;
            int freq = 1;
            std::cout << "Word to add: ";
            std::cin >> word;
            std::cout << "Frequency (default 1): ";
            if(!(std::cin >> freq)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                freq = 1;
            }
            word = toLower(word);
            engine.addKeyword(word, freq);
            std::cout << "> '" << word << "' added with freq=" << freq << "\n";
        } else if (cmd == "search") {
            std::string word;
            std::cout << "Word to search: ";
            std::cin >> word;
            word = toLower(word);
            engine.searchKeyword(word);
        } else if (cmd == "suggest") {
            std::string prefix;
            int k = 5;
            std::cout << "Prefix: ";
            std::cin >> prefix;
            prefix = toLower(prefix);
            std::cout << "How many suggestions (default 5): ";
            if (!(std::cin >> k)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                k = 5;
            }
            auto suggestions = engine.suggest(prefix, k);
            std::cout << "\nSuggestions for '" << prefix << "':\n";
            int idx = 1;
            for (const auto& [word, freq] : suggestions) {
                std::cout << idx++ << ". " << word << " (freq: " << freq << ")\n";
            }
            if (suggestions.empty()) std::cout << "(no suggestions)\n";
        } else if (cmd == "stats") {
            engine.printStats();
        } else {
            std::cout << "Unknown command.\n";
        }
    }
    std::cout << "Saving and exiting...\n";
    // Destructor of engine auto-saves
    return 0;
}
