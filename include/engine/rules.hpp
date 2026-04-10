#pragma once
#include <string>
#include <vector>

class RuleEngine {
public:
    static std::vector<std::string> apply(const std::string& word);
};
