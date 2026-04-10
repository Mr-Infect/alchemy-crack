#include "modules/offline.hpp"
#include "engine/threadpool.hpp"
#include "engine/rules.hpp"
#include "core/metrics.hpp"
#include "ui/tui.hpp"
#include "gpu/gpu.hpp"

#include <iostream>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <thread>
#include <chrono>
#include <vector>


OfflineCracker::OfflineCracker(const std::string& hash, Wordlist& wl)
    : target_hash(hash), wordlist(wl) {}


std::string OfflineCracker::hash(const std::string& input) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), digest);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2)
           << std::setfill('0')
           << (int)digest[i];
    }
    return ss.str();
}


void OfflineCracker::run() {
    std::cout << "[*] Starting multithreaded brute force...\n";

    const auto& words = wordlist.get_words();

    std::atomic<bool> found(false);
    Metrics metrics;

    ThreadPool pool(std::thread::hardware_concurrency());

    
    GPUCracker gpu;
    bool use_gpu = gpu.is_available();

    
    start_ui();

   
    std::thread ui_thread([&]() {
        while (!found) {
            update_ui(metrics.attempts.load());
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });

    
    for (const auto& word : words) {
        if (found) break;

        pool.enqueue([&, word]() {
            if (found) return;

            auto variants = RuleEngine::apply(word);

            std::vector<std::string> batch;

            for (const auto& variant : variants) {
                if (found) return;

                batch.push_back(variant);

               
                if (batch.size() >= 1000) {

                    if (use_gpu) {
                        auto results = gpu.crack_batch(batch, target_hash);

                        if (!results.empty()) {
                            found = true;
                            stop_ui();
                            std::cout << "\n[+] Password found: " << results[0] << "\n";
                            return;
                        }
                    } else {
                        for (const auto& item : batch) {
                            metrics.attempts++;

                            std::string hashed = hash(item);

                            if (hashed == target_hash) {
                                found = true;
                                stop_ui();
                                std::cout << "\n[+] Password found: " << item << "\n";
                                return;
                            }
                        }
                    }

                    batch.clear();
                }
            }

            
            for (const auto& item : batch) {
                if (found) return;

                metrics.attempts++;

                std::string hashed = hash(item);

                if (hashed == target_hash) {
                    found = true;
                    stop_ui();
                    std::cout << "\n[+] Password found: " << item << "\n";
                    return;
                }
            }
        });
    }

   
    while (!found) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    pool.shutdown();

    if (ui_thread.joinable())
        ui_thread.join();

    stop_ui();
}
