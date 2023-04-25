#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxT = 50000;
const int maxN = 200000;

int t;
int n;
int a[maxN + 10];
int b[maxN + 10];
int c[maxN + 10];
vic raw;

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i];
    for (int i = 1; i <= n; i++) c[i] = 0;
    std::sort(b + 1, b + n + 1);
    b[0] = -1;
    int mex = -1;
    for (int i = 1; i <= n; i++) {
        if (b[i] == b[i - 1]) continue;
        if (b[i] == b[i - 1] + 1) continue;
        mex = b[i - 1] + 1;
        break;
    }
    if (mex == -1) mex = b[n] + 1;
    raw.clear();
    for (int i = 1; i <= n; i++) raw.push_back(b[i]);
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    /*
    for (int i = 1; i <= n; i++) {
        int x = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
        c[x]++;
    }
    */
    int l = 0;
    int r = 0;
    for (int i = 1; i <= n; i++) if (a[i] == mex + 1) r = i;
    for (int i = n; i >= 1; i--) if (a[i] == mex + 1) l = i;
    if (l) {
        //for (int i = 1; i <= n; i++) c[i] = 0;
        for (int i = 1; i < l; i++) {
            int x = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
            c[x]++;
        }
        for (int i = n; i > r; i--) {
            int x = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
            c[x]++;
        }
        for (int i = l; i <= r; i++) {
            if (a[i] >= mex + 1) continue;
            int x = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
            if (c[x] == 0) {
                std::cout << "No" << '\n';
                return;
            }
        }
        std::cout << "Yes" << '\n';
    } else {
        for (int i = 1; i <= n; i++) {
            int x = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
            c[x]++;
        }
        for (int i = 1; i <= n; i++) {
            int x = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
            if (c[x] >= 2) {
                std::cout << "Yes" << '\n';
                return;
            }
        }
        if (mex != b[n] + 1) {
            std::cout << "Yes" << '\n';
            return;
        }
        std::cout << "No" << '\n';
    }
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}