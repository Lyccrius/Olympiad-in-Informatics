#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 1e6;
const int maxM = 1e6;

int n, m;
char ch[maxM + 10];
int k[maxM + 10], a[maxM + 10];
int c[maxM + 10], s[maxM + 10];

int array[maxN + 10];
vic range;
//int tot;

int lowbit(int x) {
    return x & -x;
}

struct BinaryIndexedTree {
    lxl node[maxM + 10];

    void Add(int pos, int val) {
        while (pos <= m) {
            node[pos] += val;
            pos += lowbit(pos);
        }
        return;
    }

    lxl Ask(int pos) {
        lxl ret = 0;
        while (pos >= 1) {
            ret += node[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
} cnt, sum;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> ch[i];
        if (ch[i] == 'U') {
            std::cin >> k[i] >> a[i];
            range.push_back(a[i]);
        } else {
            std::cin >> c[i] >> s[i];
            range.push_back(s[i]);
        }
    }
    range.push_back(0xcfcfcfcf);
    std::sort(range.begin(), range.end());
    //tot = std::unique(range.begin(), range.end()) - range.begin() - 1;
    //while (range.size() > tot) range.pop_back();
    for (int i = 1; i <= m; i++) {
        if (ch[i] == 'U') {
            a[i] = std::lower_bound(range.begin(), range.end(), a[i]) - range.begin();
            if (array[k[i]]) {
                cnt.Add(array[k[i]], -1);
                sum.Add(array[k[i]], -range[array[k[i]]]);
            }
            array[k[i]] = a[i];
            cnt.Add(array[k[i]], 1);
            sum.Add(array[k[i]], range[array[k[i]]]);
        } else {
            s[i] = std::lower_bound(range.begin(), range.end(), s[i]) - range.begin();
            //printf("%d, %d, %d, %d\n", c[i], cnt.Ask(m), cnt.Ask(s[i] - 1), range[s[i]]);
            //printf("%d, %d\n", sum.Ask(s[i] - 1), (c[i] - (cnt.Ask(m) - cnt.Ask(s[i] - 1))) * range[s[i]]);
            if (sum.Ask(s[i] - 1) >= 1ll * (c[i] - (cnt.Ask(m) - cnt.Ask(s[i] - 1))) * range[s[i]]) {
                std::cout << "TAK\n";
            } else {
                std::cout << "NIE\n";
            }
        }
    }
    return 0;
}