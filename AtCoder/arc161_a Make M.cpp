#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 2e5;

int n;
int a[maxN + 10];
vic arr;
vic odd;
vic eve;

bool check(int x) {
    //printf("check %d\n", x);
    if (arr[x] <= arr[x - 1]) {
        //printf("%d - 1\n", x);
        return false;
    }
    if (arr[x] <= arr[x + 1]) {
        //printf("%d + 1\n", x);
        return false;
    }
    return true;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) arr.push_back(a[i]);
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        if (i * 2 < n) odd.push_back(arr[i]);
        else eve.push_back(arr[i]);
    }
    arr.clear();
    for (int i = 1; i * 2 < n; i++) arr.push_back(odd[i - 1]), arr.push_back(eve[i - 1]);
    arr.push_back(odd.back());
    //for (auto i : arr) printf("%d\n", i);
    for (int i = 1; i * 2 < n; i++) {
        if (!check(2 * i - 1)) {
            std::cout << "No" << '\n';
            return 0;
        }
    }
    std::cout << "Yes" << '\n';
    return 0;
}