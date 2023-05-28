#include <iostream>
#include <complex>
#include <cmath>

typedef double dbl;
typedef std::complex<dbl> cmd;

const int maxN = 2e6;
const int maxM = 2e6;
const dbl Pi = acos(-1.0);

int n, m;
int a[maxN + 10];
int b[maxM + 10];
cmd A[maxN + maxM + 10];
cmd B[maxM + maxM + 10];
cmd C[maxN + maxM + 10];

void FFT(cmd *a, int n, int t) {
    if (n == 1) return;
    int mid = n / 2;
    cmd al[mid];
    cmd ar[mid];
    for (int i = 0; i < mid; i++) al[i] = a[i * 2];
    for (int i = 0; i < mid; i++) ar[i] = a[i * 2 + 1];
    FFT(al, mid, t);
    FFT(ar, mid, t);
    cmd w1(cos(2.0 * Pi / n), t * sin(2.0 * Pi / n));
    cmd wk(1.0, 0.0);
    for (int i = 0; i < mid; i++, wk *= w1) {
        a[i] = al[i] + wk * ar[i];
        a[i + mid] = al[i] - wk * ar[i];
    }
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i <= n; i++) std::cin >> a[i];
    for (int i = 0; i <= m; i++) std::cin >> b[i];
    for (int i = 0; i <= n; i++) A[i].real(a[i]);
    for (int i = 0; i <= m; i++) B[i].real(b[i]);
    int N = 1;
    while (N < n + m + 1) N *= 2;
    FFT(A, N, 1);
    FFT(B, N, 1);
    for (int i = 0; i <= N; i++) C[i] = A[i] * B[i];
    FFT(C, N, -1);
    for (int i = 0; i <= n + m; i++) std::cout << (int) (C[i].real() / N + 0.5) << ' ';
    return 0;
}