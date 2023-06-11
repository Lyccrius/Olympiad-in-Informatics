#include <iostream>
#include <deque>

typedef long long lxl;
typedef double dbl;
typedef std::deque<int> diq;

const int maxN = 1e6;

int n;
lxl a, b, c;
lxl x[maxN + 10];
lxl p[maxN + 10];
lxl f[maxN + 01];
diq q;

lxl X(int i) {
    return p[i];
}

lxl Y(int i) {
    return f[i] + a * p[i] * p[i] - b * p[i];
}

dbl slope(int i, int j) {
    return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i));
}

int main() {
    q.push_back(0);
    std::cin >> n;
    std::cin >> a >> b >> c;
    for (int i = 1; i <= n; i++) std::cin >> x[i];
    for (int i = 1; i <= n; i++) p[i] = p[i - 1] + x[i];
    for (int i = 1; i <= n; i++) {
        int l = 0;
        int r = q.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (slope(q[mid], q[mid + 1]) < 2 * a * p[i]) r = mid;
            else l = mid + 1;
        }
        int j = q[l];
        f[i] = f[j] + a * (p[i] - p[j]) * (p[i] - p[j]) + b * (p[i] - p[j]) + c;
        while (q.size() > 1 && slope(q[q.size() - 2], q.back()) < slope(q[q.size() - 2], i)) q.pop_back();
        q.push_back(i);
    }
    std::cout << f[n] << '\n';
    return 0;
}