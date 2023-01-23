#include <iostream>
#include <stack>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 20;

int N;
int a[maxN + 10];
int b[maxN + 10][maxN + 10];
int c[maxN + 10];
int f[maxN + 10];

int res;
int ans;
std::stack<int> rec;

int main() {
    promote();
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) std::cin >> b[i][j];
    for (int i = 1; i <= N; i++) b[0][i] = 1;
    for (int i = 1; i <= N; i++) for (int j = 0; j < i; j++) {
        if (f[i] < f[j] + a[i] && b[j][i]) {
            f[i] = f[j] + a[i];
            c[i] = j;
        } 
    }
    for (int i = 1; i <= N; i++) {
        if (ans < f[i]) {
            ans = f[i];
            res = i;
        }
    }
    while (res) {
        rec.push(res);
        res = c[res];
    }
    bool fir = true;
    while (!rec.empty()) {
        if (!fir) std::cout << ' ';
        fir = false;
        std::cout << rec.top();
        rec.pop();
    }
    std::cout << '\n';
    std::cout << ans;
    return 0;
}