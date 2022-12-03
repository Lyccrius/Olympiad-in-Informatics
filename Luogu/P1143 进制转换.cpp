#include <cstdio>
#include <cstring>
#include <stack>

int n, m;
char str[50];

int main() {
	scanf("%d", &n);
	scanf("%s", str + 1);
	int len = std::strlen(str + 1);
	int a = 1;
	int num = 0;
	for (int i = len; i >= 1; i--) {
		if (str[i] >= '0' && str[i] <= '9') num += (str[i] - '0') * a;
		else num += (str[i] - 'A' + 10) * a;
		a = a * n;
	}
	scanf("%d", &m);
	std::stack<int> res;
	while (num) {
		if (num % m < 10) res.push(num % m + '0');
		else res.push(num % m - 10 + 'A');
		num /= m;
	}
	while (!res.empty()) {
		printf("%c", res.top());
		res.pop();
	}
	return 0;
}