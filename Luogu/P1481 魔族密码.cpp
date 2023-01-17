#include <algorithm>
#include <iostream>
#include <string>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2000;
const int maxS = 75;

int N;
std::string str;
int ans;

struct TrieTree {
    struct Node {
        int next[26];
        int val;
    } node[maxN * maxS + 10];

    int tot;

    void Insert(std::string str) {
        int u = 0;
        int res = 1;
        for (int i = 0; i < str.size(); i++) {
            int ch = str[i] - 'a';
            if (node[u].next[ch] == 0) node[u].next[ch] = ++tot;
            u = node[u].next[ch];
            res += node[u].val;
        }
        node[u].val++;
        ans = std::max(ans, res);
        return;
    }
} TT;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> str, TT.Insert(str);
    std::cout << ans << '\n';
    return 0;
}