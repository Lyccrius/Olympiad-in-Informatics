#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const int maxN = 20 + 10;

int n;
char str[maxN][maxN];
int cnt[maxN];
int res;

int Check(int xStr, int yStr) {
    int xLen = std::strlen(str[xStr] + 1);
    int yLen = std::strlen(str[yStr] + 1);
    for (int len = 1; len <= std::min(xLen, yLen); len++) {
        bool ok = true;
        int i = xLen - len + 1;
        for (int j = 1; j <= len; j++) if (str[xStr][i + j - 1] != str[yStr][j]) {
            ok = false;
            break;
        }
        if (ok) return len;
    }
    return 0;
}

void DFS(int nowStr, int nowLen) {
	res = std::max(res, nowLen);
	for(int i = 1; i <= n; i++) {
		if(cnt[i] >= 2) continue;
		int c = Check(nowStr, i);
		if(c > 0) {
			cnt[i]++;
			DFS(i, nowLen + std::strlen(str[i] + 1) - c);
			cnt[i]--;
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%s", str[i] + 1);
    scanf("%s", str[0] + 1);
	DFS(0, 1);
	printf("%d\n", res);
    return 0;
}