#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1e5 + 10;

int t;

int n;
char s[maxn];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        int fre[10];
        int ans = 0;
        for (int i = 1; i <= n; i++) {
        	std::memset(fre, 0, sizeof(fre));
			int maxFre = 0;
            int difCnt = 0;
            for (int j = i; j <= n && fre[s[j] - '0'] <= 10; j++) {
				fre[s[j] - '0']++;
				maxFre = std::max(maxFre, fre[s[j] - '0']);
                if (fre[s[j] - '0'] == 1) difCnt++;
                if (maxFre <= difCnt) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}