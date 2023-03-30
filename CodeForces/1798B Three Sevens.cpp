#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

typedef std::map<int, int> mii;
typedef std::vector<int> vic;

const int maxM = 5e4;
const int maxN = 5e4;
const int maxA = 5e4;

int t;
int m;
int n;
int a[maxN + 10];
int b[maxA + 10];
int c[maxM + 10];
int p[maxM + 10];
mii vis;
vic A;

void mian() {
	memset(c, 0, sizeof(c));
	vis.clear();
	A.clear();
	int maxA = 0;
	std::cin >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> n;
		for (int j = 1; j <= n; j++) {
			std::cin >> a[i];
			b[a[i]] = i;
            //printf("last %d = %d\n", a[i], i);
			if (vis[a[i]] == false) {
				vis[a[i]] = true;
				A.push_back(a[i]);
                //printf("A.push %d\n", a[i]);
			}
		}
	}
	for (auto i : A) {
        //printf("last of %d = %d\n", a[i], b[a[i]]);
		c[b[i]]++;
		p[b[i]] = i;
	}
	for (int i = 1; i <= m; i++) if (c[i] == 0) {std::cout << - 1 << '\n'; return;}
	for (int i = 1; i <= m; i++) std::cout << p[i] << ' '; std::cout << '\n';
	return;
}

int main() {
	std::cin >> t;
	while (t--) mian();
	return 0;
}