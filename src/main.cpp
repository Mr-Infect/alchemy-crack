#include <iostream>
#include "engine/wordlist.hpp"
#include "modules/offline.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage:\n";
        std::cout << "./alchemy-crack <hash> <wordlist>\n";
        return 1;
    }

    std::string target_hash = argv[1];
    std::string wordlist_path = argv[2];

    Wordlist wordlist(wordlist_path);

    if (!wordlist.load()) {
        std::cerr << "Failed to load wordlist\n";
        return 1;
    }

    OfflineCracker cracker(target_hash, wordlist);
    cracker.run();

    return 0;
}
