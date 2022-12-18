#include <cstdio>
 
const int maxN = 18 + 1;
 
int n;
int s[maxN];
 
int main() {
	scanf("%d", &n);
	int head = 1;
	int tail = 1 << n;
	int lpow = 1;
	int rpow = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%1d", &s[i]);
		if (s[i] == 1) {
			head += lpow;
			lpow *= 2;
		} else {
			tail -= rpow;
			rpow *= 2;
		}
	}
	for (int i = head; i <= tail; i++) printf("%d ", i);
	return 0;
}