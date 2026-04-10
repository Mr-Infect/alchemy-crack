#include "engine/rules.hpp"
#include <algorithm>

std::vector<std::string> RuleEngine::apply(const std::string& word) {
    std::vector<std::string> results;

 
    results.push_back(word);

    
    std::string upper = word;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    results.push_back(upper);

   
    results.push_back(word + "123");
    results.push_back(word + "2024");


    std::string leet = word;
    std::replace(leet.begin(), leet.end(), 'a', '4');
    std::replace(leet.begin(), leet.end(), 'e', '3');
    results.push_back(leet);

    return results;
}
