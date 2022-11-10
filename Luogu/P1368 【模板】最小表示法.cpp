#include <cstdio>
#include <algorithm>

const int maxn = 3e5 + 10;

int n;
int flaw[maxn << 1];
int ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &flaw[i]);
    for (int i = 1; i <= n; i++) flaw[i + n] = flaw[i];
    int i = 1, j = 2, k;
    while (i <= n && j <= n) {
        k = 1;
        while (k <= n && flaw[i + k - 1] == flaw[j + k - 1]) k++;
        if (k > n) break;
        if (flaw[i + k - 1] > flaw[j + k - 1]) {
            i = i + k;
            if (i == j) i++;
        }
        if (flaw[i + k - 1] < flaw[j + k - 1]) {
            j = j + k;
            if (i == j) j++;
        }
    }
    ans = std::min(i, j);
    for (int i = ans; i <= ans + n - 1; i++) printf("%d ", flaw[i]);
    return 0;
}