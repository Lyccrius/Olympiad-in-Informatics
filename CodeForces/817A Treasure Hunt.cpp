#include <bits/stdc++.h>

using namespace std;

int x_1, y_1;
int x_2, y_2;
int x, y;

int main() {
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    cin >> x >> y;

    int dx = abs(x_1 - x_2);
    int dy = abs(y_1 - y_2);

    if ((dx % x | dy % y) || (dx / x % 2 ^ dy / y % 2)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }

    return 0;
}