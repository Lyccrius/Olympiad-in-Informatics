#include <iostream>
#include <stack>

std::string X;
std::stack<char> S;

int main() {
    std::cin >> X;
    int n = X.size() - 1;
    int ans = n + 1;
    for (int i = 0; i <= n; i++) {
        if (!S.empty() && S.top() == 'S' && X[i] == 'T') {
            S.pop();
            ans -= 2;
        } else {
            S.push(X[i]);
        }
    }
    std::cout << ans;
}