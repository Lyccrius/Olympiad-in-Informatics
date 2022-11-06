#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1e6 + 10;
const int mod = 131;

int t;

int n;
char s[maxn];

int ans;

unsigned long long hash[maxn];
unsigned long long rash[maxn];
unsigned long long pow[maxn];

unsigned long long Hash(int l, int r) {
    return hash[r] - hash[l - 1] * pow[r - l + 1];
}

unsigned long long Rash(int l, int r) {
    return rash[l] - rash[r + 1] * pow[r - l + 1];
}

namespace Odd {
    void mian() {
        for (int i = 1; i <= n; i++) {
            int l = 0;
            int r = std::min(i - 1, n - i);
            while (l < r) {
		    	int mid = (l + r + 1) >> 1;
                if (Hash(i - mid, i) == Rash(i, i + mid)) l = mid;
		    	else r = mid - 1;
		    }
            int len = l * 2 + 1;
            ans = std::max(ans, len);
        }
        return;
    }
}

namespace Even {
    void mian() {
        for (int i = 1; i <= n; i++) {
            int l = 0;
            int r = std::min(i, n - i + 1);
            while (l < r) {
		    	int mid = (l + r + 1) >> 1;
                if (Hash(i - mid, i - 1) == Rash(i, i + mid - 1)) l = mid;
		    	else r = mid - 1;
		    }
            int len = l * 2;
            ans = std::max(ans, len);
        }
        return;
    }
}

int main() {
    while (scanf("%s", s + 1) && s[1] != 'E') {
        t++;
        printf("Case %d: ", t);
        n = strlen(s + 1);
        ans = 0;
        hash[0] = 0;
        rash[n + 1] = 0;
        pow[0] = 1;
        for (int i = 1; i <= n; i++) hash[i] = hash[i - 1] * mod + (s[i] - 'a' + 1);
        for (int i = n; i >= 1; i--) rash[i] = rash[i + 1] * mod + (s[i] - 'a' + 1);
        for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * mod;
        Odd::mian();
        Even::mian();
        printf("%d\n", ans);
    }
    return 0;
}