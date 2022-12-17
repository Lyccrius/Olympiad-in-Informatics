#include <cstdio>
#include <algorithm>

const int maxN = 7 + 1;

int n;
struct Node {
	int id;
	int p;

	bool operator<(Node other) const {
		return p < other.p;
	}
} player[1 << maxN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= (1 << n); i++) player[i].id = i;
	for (int i = 1; i <= (1 << n); i++) scanf("%d", &player[i].p);
	std::sort(player + 1, player + (1 << (n - 1)) + 1);
	std::sort(player + (1 << (n - 1)) + 1, player + (1 << n) + 1);
	if (player[1 << (n - 1)].p < player[1 << n].p) printf("%d\n", player[1 << (n - 1)].id);
	else printf("%d\n", player[1 << n].id);
	return 0;
}