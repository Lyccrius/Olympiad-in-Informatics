#include <iostream>
#include <algorithm>

const int maxD = 100;
const int maxG = 100;
const int maxT = 1000;
const int maxF = 30;
const int maxH = 25;

int D, G;
int f[maxD + 10];

struct Node {
    int T, F, H;

    bool operator<(const Node &other) const {
        return T < other.T;
    }
} node[maxG + 10];

int main() {
    f[0] = 10;
    std::cin >> D >> G;
    for (int i = 1; i <= G; i++) std::cin >> node[i].T >> node[i].F >> node[i].H;
    std::sort(node + 1, node + G + 1);
    for (int i = 1; i <= G; i++) {
        for (int j = D; j >= 0; j--) {
            if (f[j] >= node[i].T) {
                if (j + node[i].H >= D) {
                    std::cout << node[i].T << '\n';
                    return 0;
                }
                f[j + node[i].H] = std::max(f[j + node[i].H], f[j]);
                f[j] += node[i].F;
            }
        }
    }
    std::cout << f[0] << '\n';
    return 0;
}