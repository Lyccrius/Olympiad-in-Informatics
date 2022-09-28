#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> pdd;

const double eps = 0.000001;

int n, d;
int x, y;

pdd island[1010];
double pos = -0x3f3f3f3f;
int ans = 0;

int main() {
    cin >> n >> d;

	for (int i = 1; i <= n; i ++) {
        cin >> x >> y;
        
        if (y > d) {
			cout << -1 << endl;
			return 0;
		}

        double sec = sqrt((double)d * d - (double)y * y);

		island[i].first = (double)x - sec;
        island[i].second = (double)x + sec;
    }
    
	sort(island + 1, island + n + 1);
    
	for (int i = 1; i <= n; i ++) {
		if (pos + eps < island[i].first) {
			ans ++;
			pos = island[i].second;
		} else {
            pos = min(island[i].second, pos);
        }
	}
    
    cout << ans << endl;

	return 0;
}