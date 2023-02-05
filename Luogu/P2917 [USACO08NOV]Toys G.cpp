#include <iostream>
#include <algorithm>
#include <deque>

const int maxD = 1e5;
const int maxT = 50;
const int maxC = 60;
const int maxN = 1e5;
const int inf = 1e9;

int D, N1, N2, C1, C2, Tc;
int T[maxD + 10];

struct Node {
    int t;
    int c;
};

int check(int x) {
    int ret = x * Tc;
    std::deque<Node> qc;
    std::deque<Node> q1;
    std::deque<Node> q2;
    for (int i = 1; i <= D; i++) {
        while (!qc.empty() && qc.front().t + N2 <= i) q2.push_back(qc.front()), qc.pop_front();
        while (!q2.empty() && q2.front().t + N1 <= i) q1.push_back(q2.front()), q2.pop_front();
        int Ti = T[i];
        int t = std::min(Ti, x);
        Ti -= t;
        x -= t;
        while (Ti && !q1.empty()) {
            int t = std::min(Ti, q1.back().c);
            Ti -= t;
            ret += t * C1;
            q1.back().c -= t;
            if (!q1.back().c) q1.pop_back();
        }
        while (Ti && !q2.empty()) {
            int t = std::min(Ti, q2.back().c);
            Ti -= t;
            ret += t * C2;
            q2.back().c -= t;
            if (!q2.back().c) q2.pop_back();
        }
        if (Ti) return inf;
        qc.push_back((Node) {i, T[i]});
    }
    return ret;
}

int main() {
    std::cin >> D >> N1 >> N2 >> C1 >> C2 >> Tc;
    if (N1 < N2) {
        std::swap(N1, N2);
        std::swap(C1, C2);
    }
    if (C1 > C2) {
        N1 = N2;
        C1 = C2;
    }
    for (int i = 1; i <= D; i++) std::cin >> T[i];
    int l = 1;
    int r = 0;
    for (int i = 1; i <= D; i++) r += T[i];
    while (r - l > 2) {
        int gap = (r - l) / 3;
        int lmid = l + gap;
        int rmid = r - gap;
        if (check(lmid) < check(rmid)) r = rmid;
        else l = lmid;
    }
    int ans = inf;
    for (int k = l; k <= r; k++) ans = std::min(ans, check(k));
    std::cout << ans;
    return 0;
}