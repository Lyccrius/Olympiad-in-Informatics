#include <iostream>
#include <algorithm>

const int maxN = 1e5;

int n;
struct Node {
    int f;
    int i;

    bool operator<(const Node &other) const {
        if (f != other.f) return f < other.f;
        return i > other.i;
    }
} node[maxN + 10];
int a[maxN + 10];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> node[i].f;
    for (int i = 1; i <= n; i++) node[i].i = i;
    std::sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; i++) a[node[i].i] = i;
    for (int i = 1; i <= n; i++) std::cout << a[i] << ' ';
    std::cout << '\n';
    return 0;
}