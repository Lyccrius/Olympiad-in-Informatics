#include <iostream>
#include <string>
#include <map>

const int maxN = 1e4;
const int maxM = 1e6;
const int maxK = 1e6;

int N, M;
std::string name;
std::map<std::string, int> list;
std::string A, B;
int K;
std::string X, Y;

struct DisjointSetUnion {
    int node[maxN + 10];

    void Init() {
        for (int i = 1; i <= N; i++) node[i] = i;
        return;
    }

    int Find(int x) {
        if (node[x] == x) return x;
        return node[x] = Find(node[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        node[x] = y;
        return;
    }
} DSU;

int main() {
    std::cin >> N >> M;
    DSU.Init();
    for (int i = 1; i <= N; i++) std::cin >> name, list[name] = i;
    for (int i = 1; i <= M; i++) std::cin >> A >> B, DSU.Union(list[A], list[B]);
    std::cin >> K;
    for (int i = 1; i <= K; i++) {
        std::cin >> X >> Y;
        if (DSU.Find(list[X]) == DSU.Find(list[Y])) std::cout << "Yes.\n";
        else std::cout << "No.\n";
    }
    return 0;
}