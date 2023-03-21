#include <iostream>

const int maxN = 1e5;

int N;
int A[maxN + 10];

int main() {
    int ans = 0;
    int now = 0;
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) {
        if (i == N) {
            if (now == 0) ans++;
            break;
        }
        switch(now) {
            case 0: {
                ans++;
                if (A[i] < A[i + 1]) now = 1;
                if (A[i] > A[i + 1]) now = 2;
                if (A[i] == A[i + 1]) now = 3;
                break;
            }
            case 1: {
                if (A[i] > A[i + 1]) now = 0;
                break;
            }
            case 2: {
                if (A[i] < A[i + 1]) now = 0;
                break;
            }
            case 3: {
                if (A[i] < A[i + 1]) now = 1;
                if (A[i] > A[i + 1]) now = 2;
                break;
            }
        }
    }
    std::cout << ans;
    return 0;
}