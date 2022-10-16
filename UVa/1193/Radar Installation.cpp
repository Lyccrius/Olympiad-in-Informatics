#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> pdd;

int n, d;
int x, y;

pdd island[1010];
double pos = -0x3f3f3f3f;
int ans = 0;

int t = 0;

void solve() {
	ans = 0;
	pos = -0x3f3f3f3f;
	bool flag = false;

	for (int i = 1; i <= n; i ++) {
        cin >> x >> y;
        
        if (y > d) {
			flag = true;
		}

        double sec = sqrt((double)d * d - (double)y * y);

		island[i].first = (double)x - sec;
        island[i].second = (double)x + sec;
    }

	if (flag) {
		printf("Case %d: -1\n", t);
		return;
	}
    
	sort(island + 1, island + n + 1);
    
	for (int i = 1; i <= n; i ++) {
		if (pos < island[i].first) {
			ans ++;
			pos = island[i].second;
		} else {
            pos = min(island[i].second, pos);
        }
	}

	printf("Case %d: ", t);
    
    cout << ans << endl;
}

int main() {
	while (scanf("%d%d", &n, &d) && n && d) {
		t++;
		solve();
	}

	return 0;
}