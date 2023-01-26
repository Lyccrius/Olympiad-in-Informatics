#include <iostream>
#include <algorithm>

const int maxN = 1e5;

int n;
struct Node {
    int x;
    int h;
    int id;
    int res;
    int next;

    bool operator<(const Node &other) const {
        return x < other.x;
    }
} node[maxN + 10];
int ans[maxN + 10];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> node[i].x >> node[i].h;
    for (int i = 1; i <= n; i++) node[i].id = i;
    for (int i = 1; i <= n; i++) node[i].res = 1;
    std::sort(node + 1, node + n + 1);
    for (int i = n; i >= 1; i--) {
        node[i].next = i + 1;
        while (node[i].next <= n && node[i].x + node[i].h - 1 >= node[node[i].next].x) {
            node[i].res += node[node[i].next].res;
            node[i].next = node[node[i].next].next;
        }
        ans[node[i].id] = node[i].res;
    }
    for (int i = 1; i <= n; i++) std::cout << ans[i] << ' ';
    return 0;
}