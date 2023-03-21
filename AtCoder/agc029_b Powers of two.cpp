#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int N;
int A[maxN + 10];
int ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    std::sort(A + 1, A + N + 1);
    for (int p = 30; p >= 1; p--) {
        int l = 1;
        int r = N;
        while (l < r) {
            while (l < r && A[l] == 0) l++;
            while (l < r && A[r] == 0) r--;
            while (l < r && A[l] + A[r] < (1 << p)) l++;
            while (l < r && A[l] + A[r] > (1 << p)) r--;
            if (A[l] == 0) continue;
            if (A[r] == 0) continue;
            if (l < r && A[l] + A[r] == (1 << p)) {
                ans++;
                A[l] = 0;
                A[r] = 0;
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}