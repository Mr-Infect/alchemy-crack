#include "modules/offline.hpp"
#include "engine/threadpool.hpp"
#include "engine/rules.hpp"
#include "core/metrics.hpp"
#include "ui/tui.hpp"

#include <iostream>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <thread>
#include <chrono>

// Constructor
OfflineCracker::OfflineCracker(const std::string& hash, Wordlist& wl)
    : target_hash(hash), wordlist(wl) {}

// SHA256 hash function
std::string OfflineCracker::hash(const std::string& input) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), digest);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return ss.str();
}

// Main cracking logic
void OfflineCracker::run() {
    std::cout << "[*] Starting multithreaded brute force...\n";

    const auto& words = wordlist.get_words();

    std::atomic<bool> found(false);
    Metrics metrics;

    ThreadPool pool(std::thread::hardware_concurrency());

    // Start TUI
    start_ui();

    // UI update thread
    std::thread ui_thread([&]() {
        while (!found) {
            update_ui(metrics.attempts.load());
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });

    // Submit tasks
    for (const auto& word : words) {
        if (found) break;

        pool.enqueue([&, word]() {
            if (found) return;

            auto variants = RuleEngine::apply(word);

            for (const auto& variant : variants) {
                if (found) return;

                metrics.attempts++;

                std::string hashed = hash(variant);

                if (hashed == target_hash) {
                    found = true;

                    // Stop UI safely before printing
                    stop_ui();

                    std::cout << "\n[+] Password found: " << variant << "\n";
                    return;
                }
            }
        });
    }

    // Wait until found
    while (!found) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Shutdown thread pool
    pool.shutdown();

    // Stop UI thread
    if (ui_thread.joinable())
        ui_thread.join();

    stop_ui();
}
