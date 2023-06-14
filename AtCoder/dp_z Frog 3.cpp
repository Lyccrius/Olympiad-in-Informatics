#include <iostream>
#include <deque>

typedef long long lxl;
typedef double dbl;
typedef std::deque<int> diq;

const int maxN = 2e5;

lxl n, c;
lxl h[maxN + 10];
lxl f[maxN + 10];
diq q;

lxl x(int i) {
    return h[i];
}

lxl y(int i) {
    return f[i] + h[i] * h[i];
}

dbl slope(int a, int b) {
    dbl dx = x(b) - x(a);
    dbl dy = y(b) - y(a);
    return dy / dx;
}

int main() {
    q.push_back(1);
    std::cin >> n >> c;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    for (int i = 2; i <= n; i++) {
        int l = 0, r = q.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (slope(q[mid], q[mid + 1]) >= 2 * h[i]) r = mid;
            else l = mid + 1;
        }
        int j = q[l];
        f[i] = f[j] + (h[i] - h[j]) * (h[i] - h[j]) + c;
        while (q.size() > 1 && slope(q[q.size() - 2], q[q.size() - 1]) >= slope(q[q.size() - 2], i)) q.pop_back();
        q.push_back(i);
    }
    std::cout << f[n] << '\n';
    return 0;
}