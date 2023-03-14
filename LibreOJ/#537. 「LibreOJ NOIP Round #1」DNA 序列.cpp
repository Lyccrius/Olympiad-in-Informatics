#include <iostream>
#include <string>
#include <unordered_map>

typedef std::string str;
typedef std::unordered_map<str, int> msi;

const int maxN = 5e6;

int n;
str s;
int k;
msi cnt;
int ans;

int main() {
    std::cin >> s;
    std::cin >> k;
    n = s.size();
    for (int i = 0; i + k - 1 < n; i++) {
        cnt[s.substr(i, k)]++;
        if (ans < cnt[s.substr(i, k)]) {
            ans = cnt[s.substr(i, k)];
        }
    }
    std::cout << ans;
    return 0;
}