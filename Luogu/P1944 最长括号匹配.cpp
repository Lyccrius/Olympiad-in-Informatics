#include <cstdio>
#include <cstring>

const int maxN = 1e6 + 10;

char str[maxN];
int f[maxN];
int res;
int pos;

int main() {
	scanf("%s", str + 1);
	int len = std::strlen(str + 1);
	for (int i = 1; i <= len; i++) {
		if (str[i] == '(' || str[i] == '[') continue;
		else {
			if ((str[i] == ')' && str[i - f[i - 1] - 1] == '(') ||
				(str[i] == ']' && str[i - f[i - 1] - 1] == '[')) {
				f[i] = f[i - 1] + 2 + f[i - f[i - 1] - 2];
				if (f[i] > res) {
					res = f[i];
					pos = i;
				}
			}
		}
	}
	for (int i = pos - res + 1; i <= pos; i++) printf("%c", str[i]);
	printf("\n");
	return 0;
}