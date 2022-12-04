#include <cstdio>

char ch;
int cur = 1;
char quote[2][5] = {"''", "``"};

int main() {
	while (scanf("%c", &ch) != EOF) {
		if (ch == '"') printf("%s", quote[cur]), cur ^= 1;
		else printf("%c", ch);
	}
	return 0;
}