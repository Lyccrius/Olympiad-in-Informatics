#include <cstdio>
#include <algorithm>

int t;
int n;
char s[110];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		scanf(" %s", s);
		char ans = '0';
		for (int i = 0; s[i] != '\0'; i++) ans = std::max((int)ans, (int)s[i]);
		printf("%d\n", ans - 'a' + 1);
	}
	return 0;
}