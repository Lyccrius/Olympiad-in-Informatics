#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

lxl N;
vic bit;
int sum;
int top;

int main() {
    std::cin >> N;
    while (N) bit.push_back(N % 10), N /= 10;
    for (auto i : bit) sum += i;
    top = (bit.size() - 1) * 9 + (bit.back() - 1);
    std::cout << std::max(sum, top);
    return 0;
}