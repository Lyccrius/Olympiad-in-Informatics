#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		string str;
		cin >> str;
		string ans = str;
		for (int i = 0; i < str.length(); i++) {
			string t;
			t = str.substr(i, str.length() - i) + str.substr(0, i);
			if (t < ans) ans = t;
		}
		cout << ans << endl;
	}
	return 0;
} 