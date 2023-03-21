#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 100;

int N;
int b[maxN + 10];
vic ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> b[i];
    while (N) {
        int cur = 0;
        for (int i = N; i >= 1; i--) {
            if (b[i] == i) {
                cur = i;
                break;
            }
        }
        if (cur == 0) {
            std::cout << - 1 << '\n';
            return 0;
        }
        ans.push_back(cur);
        for (int i = cur; i < N; i++) b[i] = b[i + 1];
        N--;
    }
    while (!ans.empty()) {
        std::cout << ans.back() << '\n';
        ans.pop_back();
    }
    return 0;
}