#include <bits/stdc++.h>

using namespace std;

int n, m;

vector<int> chosen;

void calc(int x) {
    if (chosen.size() > m || chosen.size() + (n - x + 1) < m) return;

    if (x == n + 1) {
        for (int i = 0; i < chosen.size(); i ++) cout << chosen[i] << " ";
        cout << endl;
        
        return;
    }
    
    chosen.push_back(x);
    
    calc(x + 1);
    
    chosen.pop_back();
    
    calc(x + 1);
    
    return;
}

int main() {
    cin >> n >> m;
    
    calc(1);
    
    return 0;
}