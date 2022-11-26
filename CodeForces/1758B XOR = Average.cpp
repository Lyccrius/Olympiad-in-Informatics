#include <cstdio>
 
int t;
int n;
 
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		if (n & 1) {
            for (int i = 1; i <= n; i++) printf("%d ", 1);
        } else {
            printf("%d ", 1);
            for (int i = 2; i <= n; i++) printf("%d ", n + 1);
        }
		printf("\n");
	}
	return 0;
}