#pragma once
#include <vector>
#include <string>

class Wordlist {
private:
    std::string path;
    std::vector<std::string> words;

public:
    Wordlist(const std::string& file_path);
    bool load();
    const std::vector<std::string>& get_words() const;
};
