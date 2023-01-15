#include <cstdio>
#include <set>

const int maxN = 1e6;
const int maxW = 1e6;

int n, q;
int a[maxN + 10];
int opt, x;

int cnt[maxW + 10];
std::set<int> s;

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]]++, s.insert(a[i]);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &opt, &x);
        if (opt == 1) {
            if (s.count(x) == 0) {
                printf("%d\n", -1);
                continue;
            }
            cnt[x]--;
            if (cnt[x] == 0) s.erase(x);
        } else {
            cnt[x]++;
            s.insert(x);
        }
        printf("%d\n", (*s.rbegin() - *s.begin()) * 2);
    }
    return 0;
}