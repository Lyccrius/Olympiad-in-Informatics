#include <cstdio>
#include <map>

const int maxN = 1e9 + 10;
const int maxQ = 2e5 + 10;

typedef std::pair<int, int> pii;

int N, Q;
int op, a, b;
std::map<pii, bool> follow;

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d%d", &op, &a, &b);
		switch (op) {
			case 1: {
				follow[std::make_pair(a, b)] = true;
				break;
			}
			case 2: {
				follow[std::make_pair(a, b)] = false;
				break;
			}
			case 3: {
				if (follow[std::make_pair(a, b)] && follow[std::make_pair(b, a)]) printf("Yes\n");
				else printf("No\n");
			}
		}
	}
	return 0;
}