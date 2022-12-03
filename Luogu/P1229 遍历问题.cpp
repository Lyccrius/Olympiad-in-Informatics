#include <cstdio>
#include <cstring>

const int maxN = 100 + 10;

char s1[maxN];
char s2[maxN];

int main() {
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	int n = std::strlen(s1 + 1);
	int cnt = 0;
	for (int i = 1; i < n; i++) for (int j = 2; j <= n; j++) if (s1[i] == s2[j] && s1[i + 1] == s2[j - 1]) cnt++;
	printf("%d\n", 1 << cnt);
	return 0;
}