#include <cstdio>
#include <stack>

int n;

void pow(int x) {
	std::stack<int> factor;
	int a = 1;
	int b = 0;
	while (x) {
		if (x & 1) factor.push(b);
		x /= 2;
		a *= 2;
		b += 1;
	}
	int tot = factor.size();
	int cnt = tot;
	while (!factor.empty()) {
		int f = factor.top();
		factor.pop();
		if (tot - cnt) printf("+");
		cnt--;
		if (f == 0) {
			printf("2(0)");
			continue;
		}
		if (f == 1) {
			printf("2");
			continue;
		}
		printf("2(");
		pow(f);
		printf(")");
	}
}

int main() {
	scanf("%d", &n);
	pow(n);
	printf("\n");
	return 0;
}