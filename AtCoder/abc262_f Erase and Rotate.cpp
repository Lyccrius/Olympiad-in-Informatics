#include <iostream>
#include <vector>
#include <deque>

typedef std::vector<int> vic;
typedef std::deque<int> diq;

const int maxN = 2e5;

int n, k;
int a[maxN + 10];

diq solve1() {
    diq q;
    int c = 0;
    for (int i = 1; i <= n; i++) {
        while (c < k && q.size() && q.back() > a[i]) {
            q.pop_back();
            c++;
        }
        q.push_back(a[i]);
    }
    while (c < k) {
        q.pop_back();
        c++;
    }
    return q;
}

diq solve2() {
    diq q1;
    diq q2;
    int p = n + 1;
    int c = 0;
    for (int i = n - k + 1; i <= n; i++) {
        if (a[i] < a[p] || p > n) {
            p = i;
        }
    }
    for (int i = p; i <= n; i++) {
        while (q1.size() && q1.back() > a[i]) {
            q1.pop_back();
        }
        q1.push_back(a[i]);
    }
    for (int i = 1; i <= p - 1; i++) {
        while (c < k - (n - p + 1) && q2.size() && q2.back() > a[i]) {
            q2.pop_back();
            c++;
        }
        q2.push_back(a[i]);
    }
    while (c < k - (n - p + 1)) {
        q2.pop_back();
        c++;
    }
    while (q1.size() && q2.size() && q1.back() > q2.front()) q1.pop_back();
    for (auto i : q2) q1.push_back(i);
    return q1;
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    diq res1 = solve1();
    diq res2 = solve2();
    if (res1 < res2) {
        for (auto i : res1) {
            std::cout << i << ' ';
        }
    } else {
        for (auto i : res2) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
    return 0;
}