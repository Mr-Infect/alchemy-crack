#pragma once
#include <atomic>

struct Metrics {
    std::atomic<long long> attempts{0};
};
