#pragma once
#include <string>
#include "engine/wordlist.hpp"

class OfflineCracker {
private:
    std::string target_hash;
    Wordlist& wordlist;

    std::string hash(const std::string& input);

public:
    OfflineCracker(const std::string& hash, Wordlist& wl);
    void run();
};
