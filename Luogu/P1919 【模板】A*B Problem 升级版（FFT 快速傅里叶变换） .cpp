#include <iostream>
#include <complex>
#include <cstring>
#include <cmath>

typedef char chr;
typedef double dbl;
typedef std::complex<dbl> cmd;

const int maxN = 1e6;
const int maxM = 1e6;
const dbl pi = acos(- 1.0);

int n, m;
chr a[maxN + 10];
chr b[maxM + 10];
cmd A[2 * maxN + 2 * maxM + 10];
cmd B[2 * maxN + 2 * maxM + 10];
cmd C[2 * maxN + 2 * maxM + 10];
int c[2 * maxN + 2 * maxM + 10];

void FFT(cmd *a, int n, int t) {
    if (n == 1) return;
    int mid = n / 2;
    cmd al[mid];
    cmd ar[mid];
    for (int i = 0; i < mid; i++) {
        al[i] = a[2 * i];
        ar[i] = a[2 * i + 1];
    }
    FFT(al, mid, t);
    FFT(ar, mid, t);
    cmd w1(cos(2.0 * pi / n), t * sin(2.0 * pi / n));
    cmd wk(1.0, 0.0);
    for (int i = 0; i < mid; i++, wk *= w1) {
        a[i] = al[i] + wk * ar[i];
        a[i + mid] = al[i] - wk * ar[i];
    }
    return;
}

int main() {
    std::cin >> a;
    std::cin >> b;
    n = strlen(a) - 1;
    m = strlen(b) - 1;
    for (int i = 0; i <= n; i++) A[i].real(a[n - i] - '0');
    for (int i = 0; i <= m; i++) B[i].real(b[m - i] - '0');
    int N = 1;
    while (N < n + m + 1) N *= 2;
    FFT(A, N, 1);
    FFT(B, N, 1);
    for (int i = 0; i < N; i++) C[i] = A[i] * B[i];
    FFT(C, N, -1);
    for (int i = 0; i < N; i++) c[i] = C[i].real() / N + 0.5;
    for (int i = 0; i < N; i++) c[i + 1] += c[i] / 10, c[i] %= 10;
    while (!c[N]) N--;
    for (int i = N; i >= 0; i--) std::cout << c[i];
    return 0;
}