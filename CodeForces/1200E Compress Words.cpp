#include <cstdio>
#include <string>
#include <iostream>

const int maxN = 1e6 + 10;

int n;
std::string str[maxN];
std::string ans;

int getNext(std::string s) {
    int next[maxN] = {-1};
    int i = 0;
    int j = -1;
    while (i < s.size()) {
        if (j == -1 || s[i] == s[j]) next[++i] = ++j;
        else j = next[j];
    }
    return j;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> str[i];
    ans = str[1];
    for (int i = 2; i <= n; i++) {
        int len = std::min(ans.size(), str[i].size());
        int sta = ans.size() - len;
        std::string tmp = str[i] + " " + ans.substr(sta);
        int res = std::min(len, getNext(tmp));
        ans += str[i].substr(res);
    }
    std::cout << ans << std::endl;
    return 0;
}