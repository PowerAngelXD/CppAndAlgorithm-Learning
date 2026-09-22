#include <iostream>

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

int main() {
    std::string A = "hello litle cat???";
    std::string B = "e c";
    std::cout << BFSearch(A, B) << std::endl;
}