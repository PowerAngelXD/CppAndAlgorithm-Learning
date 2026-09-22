#include <iostream>
#include <vector>

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
    std::string A = "hello litle cat???";
    std::string B = "e c";
    std::cout << KMPSearch(A, B) << std::endl;
}