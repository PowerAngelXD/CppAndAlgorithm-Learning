#include <iostream>
#include <vector>
#include <chrono>

int BFSearch(std::string source, std::string pat) {
    if (source.size() < pat.size()) return -1;

    int j = 0;
    for (int i = 0; i <= source.size() - pat.size(); i ++) {
        j = 0;
        while (source[i + j] == pat[j] && j < pat.size()) {
            j ++;
        }
        if (j == pat.size()) return i;
    }

    return -1;
}

std::vector<int> buildNext(std::string pat) {
    std::vector<int> next(pat.size(), 0);
    int j = 0;
    for (int i = 1; i < pat.size(); i ++) {
        while (j > 0 && pat[j] != pat[i]) {
            j = next[j - 1];
        }

        if (pat[j] == pat[i]) j ++;

        next[i] = j;
    }
    return next;
}

int KMPSearch(std::string source, std::string pat) {
    auto next = buildNext(pat);

    int j = 0;
    for (int i = 0; i < source.size(); i ++) {
        while (j > 0 && source[i] != pat[j]) {
            j = next[j - 1];
        }

        if (source[i] == pat[j]) j ++;

        if (j == pat.size()) {
            return i - pat.size() + 1;
        }
    }

    return -1;
}

int main() {
    std::string A = "OGenshinImpactOdwrgwrgGenshinImpactOGenshinImpactOgergGenshinImpactLPF.DF;.[.#@$@@FFBUBV]FGJCOMVONonvonbe#@$$??gbbjpjov---vdfbseblplfgggVONonvonpppPP";
    std::string B = "FGJCOMVON";
    auto bfStart = std::chrono::steady_clock::now();
    std::cout << BFSearch(A, B) << std::endl;
    auto bfEnd = std::chrono::steady_clock::now();
    std::cout << "BFSearch, cost: " << std::chrono::duration_cast<std::chrono::microseconds>(bfEnd - bfStart).count() << "ms" << std::endl;

    
    auto kmpStart = std::chrono::steady_clock::now();
    std::cout << KMPSearch(A, B) << std::endl;
    auto kmpEnd = std::chrono::steady_clock::now();
    std::cout << "KMPSearch, cost: " << std::chrono::duration_cast<std::chrono::microseconds>(kmpEnd - kmpStart).count() << "ms" << std::endl;
}