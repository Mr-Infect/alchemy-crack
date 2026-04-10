#pragma once
#include <vector>
#include <string>

class GPUCracker {
public:
    GPUCracker();

    bool is_available();

    std::vector<std::string> crack_batch(
        const std::vector<std::string>& candidates,
        const std::string& target_hash
    );
};
