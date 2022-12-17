#include <cstdio>
#include <deque>

const int maxN = 4e6 + 10;

int n, m;
int a[maxN];

std::deque<int> q;
int sum;
int ansi, ansj, anssum;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int head = 1;
	for (int i = 1; i <= n; i++) {
		q.push_back(a[i]);
		sum += a[i];
		while (sum > m) {
			q.pop_front();
			sum -=a [i];
			if (sum > anssum){
				anssum = sum;
				ansj = i - 1;
				ansi = head;
			}
			sum += a[i];
			sum -= a[head];
			head++;
		}
	}
	printf("%d %d %d\n", ansi, ansj, anssum);
	return 0;
}