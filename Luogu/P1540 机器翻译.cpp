#include <bits/stdc++.h>

using namespace std;

int M, N;

int line[110];

int x, cnt;

bool check(int q) {
	for (int i = 0; i < M; i ++) {
        if (line[i] == q) return true;
    }
		
	return false;
}

int main() {
	cin >> M >> N;

	memset(line, -1, sizeof(line));

	for (int i = 1; i <= N; i ++) {
		int tmp;

		cin >> tmp;

		if (!check(tmp)) {
			line[x] = tmp;
			x = (x + 1) % M;
			cnt ++;
		}
	}
    
    cout << cnt << endl;

	return 0;
}