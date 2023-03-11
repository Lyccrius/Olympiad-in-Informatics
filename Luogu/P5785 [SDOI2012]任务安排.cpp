#include <iostream>
#include <algorithm>
#include <deque>

typedef long long lxl;
typedef std::deque<int> dic;

const int maxN = 3e5;

int n;
int s;
lxl t[maxN + 10];
lxl c[maxN + 10];
lxl f[maxN + 10];
dic q;

int main() {
    std::cin >> n;
    std::cin >> s;
    q.push_back(0);
    for (int i = 1; i <= n; i++) std::cin >> t[i] >> c[i];
    for (int i = 1; i <= n; i++) t[i] = t[i - 1] + t[i];
    for (int i = 1; i <= n; i++) c[i] = c[i - 1] + c[i];
    for (int i = 1; i <= n; i++) {
        int l = 0;
        int r = q.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (f[q[mid + 1]] - f[q[mid]] > (t[i] + s) * (c[q[mid + 1]] - c[q[mid]])) r = mid;
            else l = mid + 1;
        }
        int j = q[l];
        f[i] = f[j] - (t[i] + s) * c[j] + t[i] * c[i] + s * c[n];
        while (q.size() > 1 && (f[q.back()] - f[q[q.size() - 2]]) * (c[i] - c[q.back()]) >= (f[i] - f[q.back()]) * (c[q.back()] - c[q[q.size() - 2]])) q.pop_back();
        q.push_back(i);
    }
    std::cout << f[n];
    return 0;
}