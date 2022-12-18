#include <cstdio>
 
int t;
int x[5];
int y[5];
 
void mian() {
	int cnt = 0;
	for (int i = 1; i <= 3; i++) scanf("%d%d", &x[i], &y[i]);
	for (int i = 1; i <= 3; i++) for (int j = i + 1; j <= 3; j++) if (x[i] == x[j] || y[i] == y[j]) cnt++;
	if (cnt < 2) printf("YES\n");
	else printf("NO\n");
	return;
}
 
int main() {
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}