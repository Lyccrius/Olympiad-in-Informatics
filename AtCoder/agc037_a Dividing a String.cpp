#include <cstdio>
#include <string>
#include <iostream>

const int maxn = 2e5 + 10;

std::string S;

int main() {
    std::cin >> S;
    int len = S.size();
    std::string nowS;
    std::string last;
    int k = 0;
    for (int i = 0; i < len; i++) {
        nowS += S[i];
        if (nowS != last) {
            last = nowS;
            nowS = "";
            k++;
        }
    }
    printf("%d\n", k);
    return 0;
}