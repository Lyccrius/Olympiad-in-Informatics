#include <iostream>
#include <deque>

typedef std::deque<int> diq;
typedef long long lxl;

const int maxN = 5e4;
const int maxL = 1e7;
const int maxC = 1e7;
const int inf = 1e9 + 10;

int n, L;
lxl c[maxN + 10];
lxl s[maxN + 10];
lxl f[maxN + 10];
diq q;

lxl x(int i) {
    return s[i];
}

lxl y(int i) {
    return f[i] + s[i] * s[i];
}

lxl slope(int i, int j) {
    return (y(j) - y(i)) / (x(j) - x(i));
}

int main() {
    q.push_back(0);
    std::cin >> n >> L; L++;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) c[i] += c[i - 1];
    for (int i = 1; i <= n; i++) s[i] = c[i] + i;
    for (int i = 1; i <= n; i++) {
        int l = 0;
        int r = q.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (slope(q[mid], q[mid + 1]) >= -2 * (L - s[i])) r = mid;
            else l = mid + 1;
        }
        int j = q[l];
        f[i] = f[j] + s[j] * s[j] + 2 * s[j] * (L - s[i]) + (s[i] - L) * (s[i] - L);
        while (q.size() > 1 && slope(q[q.size() - 2], q.back()) > slope(q.back(), i)) q.pop_back();
        q.push_back(i);
    }
    std::cout << f[n] << '\n';
    return 0;
}