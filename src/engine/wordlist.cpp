#include "engine/wordlist.hpp"
#include <fstream>

Wordlist::Wordlist(const std::string& file_path) : path(file_path) {}

bool Wordlist::load() {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        words.push_back(line);
    }

    return true;
}

const std::vector<std::string>& Wordlist::get_words() const {
    return words;
}
