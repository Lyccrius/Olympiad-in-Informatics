#include <iostream>

using namespace std;

int n, k;

int c[510];

bool f[510][510] = {1};

int x;

int main(){
	cin >> n >> k;

	for (int i = 1; i <= n; i ++){
		cin >> c[i];
	}

	for (int x = 1; x <= n; x ++){
		for (int i = k - c[x]; i >= 0; i --){
			for (int j = i; j >= 0; j --){
				if (f[i][j]){
					f[i+c[x]][j+c[x]] = true;
					f[i+c[x]][j] = true;
				}
			}
		}
	}

	for (int i = 0; i <= k; i ++){
		if (f[k][i]){
			x ++;
		}
	}

	cout << x << endl;

	for (int i = 0; i <= k; i ++){
		if (f[k][i]){
			cout << i << " ";
		}
	}

	return 0;
}