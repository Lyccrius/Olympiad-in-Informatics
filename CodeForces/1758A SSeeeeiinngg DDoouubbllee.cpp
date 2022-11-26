#include <cstdio>
#include <cstring>
 
int t;
char s[110];
 
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s + 1);
		int len = std::strlen(s + 1);
		for (int i = 1; i <= len; i++) printf("%c", s[i]);
		for (int i = len; i >= 1; i--) printf("%c", s[i]);
		printf("\n");
	}
	return 0;
}