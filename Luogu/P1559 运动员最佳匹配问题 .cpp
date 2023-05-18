#include <iostream>

const int maxN = 20;
const int inf = 1e9 + 10;

int n;
int p[maxN + 10][maxN + 10];
int q[maxN + 10][maxN + 10];
int w[maxN + 10][maxN + 10];

int visB[maxN + 10];
int visG[maxN + 10];
int match[maxN + 10];
int slack[maxN + 10];
int expectB[maxN + 10];
int expectG[maxN + 10];

bool DFS(int u) {
    visB[u] = true;
    for (int v = 1; v <= n; v++) {
        if (visG[v]) continue;
        int gap = expectB[u] + expectG[v] - w[u][v];
        if (gap == 0) {
            visG[v] = true;
            if (match[v] == 0 || DFS(match[v])) {
                match[v] = u;
                return true;
            }
        } else {
            slack[v] = std::min(slack[v], gap);
        }
    }
    return false;
}

int KM() {
    int ret = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) expectB[i] = std::max(expectB[i], w[i][j]);
    for (int i = 1; i <= n; i++) {
        for (int i = 1; i <= n; i++) visB[i] = false;
        for (int i = 1; i <= n; i++) visG[i] = false;
        for (int i = 1; i <= n; i++) slack[i] = inf;
        while (!DFS(i)) {
            int delta = inf;
            for (int j = 1; j <= n; j++) if (!visG[j]) delta = std::min(delta, slack[j]);
            for (int j = 1; j <= n; j++) if (visB[j]) expectB[j] -= delta;
            for (int j = 1; j <= n; j++) if (visG[j]) expectG[j] += delta; else slack[j] -= delta;
            for (int j = 1; j <= n; j++) visB[j] = false;
            for (int j = 1; j <= n; j++) visG[j] = false;
        }
    }
    for (int i = 1; i <= n; i++) ret += w[match[i]][i];
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> p[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> q[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) w[i][j] = p[i][j] * q[j][i];
    std::cout << KM() << '\n';
    return 0;
}