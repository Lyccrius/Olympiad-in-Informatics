#include <cstdio>
#include <cstring>

const int maxN = 1e6 + 10;

int k;
char a[maxN];
int next[maxN];
long long ans;

int main() {
    scanf("%d", &k);
    scanf("%s", a + 1);
    for (int i = 2, j = 0; i <= k; i++) {
        while (j && a[i] != a[j + 1]) j = next[j];
        if (a[i] == a[j + 1]) j++;
        next[i] = j;
    }
    for (int i = 2, j = i; i <= k; i++, j = i) {
        while (next[j]) j = next[j];
        if (next[i]) next[i] = j;
        ans += i - j;
    }
    printf("%lld\n", ans);
	return 0;
}