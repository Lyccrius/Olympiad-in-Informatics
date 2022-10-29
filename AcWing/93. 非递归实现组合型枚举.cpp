#include <bits/stdc++.h>

using namespace std;

vector<int> chosen;

int sta[100010], top = 0, address = 0, n, m;

void call(int x, int ret_addr) {
    int old_top = top;

    sta[++ top] = x;
    sta[++ top] = ret_addr;
    sta[++ top] = old_top;

    return;
}

int ret() {
    int ret_addr = sta[top - 1];

    top = sta[top];

    return ret_addr;
}

int main() {
    cin >> n >> m;

    call(1, 0);

    while (top) {
        int x = sta[top - 2];

        switch(address) {
            case 0:
                if (chosen.size() > m || chosen.size() + (n - x + 1) < m) {
                    address = ret();
                    continue;
                }

                if (x == n + 1) {
                    for (int i = 0; i < chosen.size(); i ++) cout << chosen[i] << " ";
                    cout << endl;

                    address = ret();

                    continue;
                }

                chosen.push_back(x);

                call(x + 1, 1);

                address = 0;

                continue;

            case 1:
                chosen.pop_back();

                call(x + 1, 2);
                
                address = 0;

                continue;

            case 2:
                address = ret();
        }
    }

    return 0;
}