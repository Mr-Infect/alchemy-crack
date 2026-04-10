#include "gpu/gpu.hpp"
#include <iostream>

GPUCracker::GPUCracker() {}

bool GPUCracker::is_available() {
    // Placeholder (later CUDA detection)
    return false;
}

std::vector<std::string> GPUCracker::crack_batch(
    const std::vector<std::string>& candidates,
    const std::string& target_hash
) {
    // Placeholder logic
    std::vector<std::string> results;

    // Future: GPU kernel execution here

    return results;
}
