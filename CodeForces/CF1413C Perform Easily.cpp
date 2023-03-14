#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e5;
const int inf = 1e9;

int n;
int a[10];
int b[maxN + 10];
int c[maxN + 10];
int t;
int ans = inf;

struct Node {
    int i;
    int d;

    bool operator<(const Node &other) const {
        return d < other.d;
    }
};

typedef std::vector<Node>::iterator vit;

std::vector<Node> node;

void Add(Node node) {
    if (c[node.i] == 0) t++;
    c[node.i]++;
    return;
}

void Del(Node node) {
    c[node.i]--;
    if (c[node.i] == 0) t--;
    return;
}

int main() {
    for (int i = 1; i <= 6; i++) std::cin >> a[i];
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= n; j++) {
            node.push_back((Node) {j, b[j] - a[i]});
        }
    }
    std::sort(node.begin(), node.end());
    vit l = node.begin();
    vit r = node.begin();
    //Add(*node.begin());
    //for (int i = 0; i < node.size(); i++) printf("%4d ", i); printf("\n");
    //for (int i = 0; i < node.size(); i++) printf("%4d ", node[i].i); printf("\n");
    //for (int i = 0; i < node.size(); i++) printf("%4d ", node[i].d); printf("\n");
    while (r < node.end()) {
        while (t < n && r < node.end()) Add(*r), r++;
        while (t >= n) {
            //printf("[%d, %d]: %d\n", l - node.begin(), r - node.begin(), r->d - l->d);
            ans = std::min(ans, (r - 1)->d - l->d), Del(*l), l++;
        }
    }
    std::cout << ans;
    return 0;
}