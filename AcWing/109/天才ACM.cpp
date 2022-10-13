#include <bits/stdc++.h>

using namespace std;

int K;
int N, M;
long long T;
long long A[500010];

long long t[500010];
long long tmp[500010];
int ans;

bool check(int l, int mid, int r) {
    for (int i = mid + 1; i <= r; i ++) {
        t[i] = A[i];
    }
        
    sort(t + mid + 1, t + r + 1);

    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (t[i] < t[j]) {
            tmp[k ++ ] = t[i ++ ];
        } else {
            tmp[k ++ ] = t[j ++ ];
        }
    }

    while (i <= mid) {
        tmp[k ++] = t[i ++];
    }

    while (j <= r) {
        tmp[k ++] = t[j ++];
    }

    long long sum = 0, x;

    for (i = 0; i < M && i < k; i ++ , k --) {
        x = tmp[i] - tmp[k - 1];
        sum += x * x;
    }
        
    return sum <= T;
}

int main() {
    cin >> K;

    while (K --){
        cin >> N >> M >> T;

        for (int i = 1; i <= N; i ++) {
            cin >> A[i];
        }

        ans = 0;

        int q;
        int L = 1, R = 0;

        while (R < N) {
            q = 1;

            while (q) {
                if (R + q <= N && check(L, R, R + q)) {
                    R += q;
                    q *= 2;

                    if (R >= N) {
                        break;
                    }

                    for (int i = L; i <= R; i ++) {
                        t[i] = tmp[i - L];
                    }
                } else {
                    q /= 2;
                }
            }

            L = R + 1;
            
            ans ++;
        }

        cout << ans << endl;
    }

    return 0;
}