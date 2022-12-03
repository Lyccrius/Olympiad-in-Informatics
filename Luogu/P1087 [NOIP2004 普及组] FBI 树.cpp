#include <cstdio>

const int maxN = 10 + 1;

int N;
char str[1 << maxN];
char type[1 << maxN][1 << maxN];

void DFS(int l, int r) {
	if (l == r) {
		if (str[l] == '0') type[l][r] = 'B';
		else type[l][r] = 'I';
	} else {
		int mid = (l + r) / 2;
		DFS(l, mid);
		DFS(mid + 1, r);
		if (type[l][mid] == type[mid + 1][r]) type[l][r] = type[l][mid];
		else type[l][r] = 'F';
	}
	printf("%c", type[l][r]);
	return;
}

int main() {
	scanf("%d", &N);
	scanf("%s", str + 1);
	DFS(1, 1 << N);
	return 0;
}