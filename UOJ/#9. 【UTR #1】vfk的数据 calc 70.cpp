#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxN = 1e4;
const int maxM = 100;

int n;

struct Node {
    chr str[maxM + 10];
    int num;

    bool operator<(const Node &other) const {
        return num < other.num;
    }
} node[maxN + 10];

int get(chr *str) {
    int m = strlen(str + 1);
    diq b;
    m -= 3;
    while (m >= 1 && isdigit(str[m])) {
        b.push_back(str[m] - '0');
        m--;
    }
    int ret = 0;
    while (b.size()) {
        ret = ret * 10;
        ret = ret + b.back();
        b.pop_back();
    }
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> (node[i].str + 1);
        node[i].num = get(node[i].str);
    }
    std::sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; i++) {
        std::cout << (node[i].str + 1) << '\n';
    }
    return 0;
}