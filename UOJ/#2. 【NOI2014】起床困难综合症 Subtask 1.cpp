#include <iostream>
#include <string>

typedef std::string str;

const str OR = "OR";
const str XOR = "XOR";
const str AND = "AND";

const int maxN = 100;
const int maxM = 0;

int n, m;
str op; int t;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> op >> t;
        if (op == OR) {
            m |= t;
        } else if (op == XOR) {
            m ^= t;
        } else if (op == AND) {
            m &= t;
        }
    }
    std::cout << m << '\n';
    return 0;
}