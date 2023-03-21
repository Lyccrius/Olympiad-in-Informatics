#include <iostream>
#include <algorithm>

const int maxN = 1e5;

int N;
int a[maxN + 10];
int x;
int s;
int mx;
int mn = maxN + 10;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) mx = std::max(mx, a[i]);
    for (int i = 1; i <= N; i++) mn = std::min(mn, a[i]);
    for (int i = 1; i <= N; i++) if (a[i] == mn) s++;
    if (s == N && mx < N - 1) s = 0;
    if (mx > mn + 1) {
        std::cout << "No" << '\n';
    } else if (s == 0) {
        x = mx;
    //  x = mn;
        if (2 * x <= N) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
    } else if (s == N) {
        x = mx + 1;
    //  x = mn + 1;
        if (x == N) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
    } else {
        x = mx;
        if (x - s <= 0) {
            std::cout << "No" << '\n';
        } else if (2 * (x - s) > N - s) {
            std::cout << "No" << '\n';
        } else {
            std::cout << "Yes" << '\n';
        }
    }
    /*
    if (mx == mn + 1) {
        if (mx > s && (mx - s) * 2 <= N - s) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
    } else if (mx == mn) {
        if (mn == N - 1) {
            std::cout << "Yes" << '\n';
        } else if (mn * 2 <= N) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
    }
    */
    return 0;
}