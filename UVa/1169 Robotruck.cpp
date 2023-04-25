#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxC = 100;
const int maxN = 100000;

int t;
int c, n;
int x[maxN + 10], y[maxN + 10], w[maxN + 10];
int o[maxN + 10];
int d[maxN + 10];
int p[maxN + 10];
int f[maxN + 10];

int abs(int x) {
    if (x < 0) x = - x;
    return x;
}

/*
int load(int i + 1, int j)
    return o[i + 1] + d[j] - d[i + 1] + o[j];
*/

/*
int func(int i) {
    return f[i] - d[i + 1] + o[i + 1];
}
*/

/*
int func(int i - 1)
    return f[i - 1] - d[i] + o[i]
*/

int load(int i, int j) {
    return o[i] + (d[j] - d[i]) + o[j];
}

int func(int i) {
    return f[i] + load(i + 1, n);
}

void mian() {
    std::cin >> c >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i] >> y[i] >> w[i];
        o[i] = abs(x[i]) + abs(y[i]);
        d[i] = d[i - 1] + abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]);
        p[i] = p[i - 1] + w[i];
    }
    diq q;
    q.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (q.size() && p[i] - p[q.front()] > c) q.pop_front();
        f[i] = f[q.front()] + load(q.front() + 1, i);
        //f[i] = func(q.front()) + d[i] + o[i];
        //while (q.size() && func(i) <= func(q.back())) q.pop_back();
        while (q.size() && func(q.back()) >= func(i)) q.pop_back();
        q.push_back(i);
    }
    std::cout << f[n] << '\n';
    if (t) std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}