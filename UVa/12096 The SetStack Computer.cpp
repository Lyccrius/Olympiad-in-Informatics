#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <map>

typedef std::string str;
typedef std::deque<int> diq;
typedef std::set<int> sit;

const int maxT = 5;
const int maxN = 2000;
const str PUSH = "PUSH";
const str DUP = "DUP";
const str UNION = "UNION";
const str INTERSECT = "INTERSECT";
const str ADD = "ADD";

int t;
int n;
str opt;

struct SetStackComputer {
    std::deque<sit> sst;
    std::map<sit, int> msi;
    diq ssc;

    int ID(sit x) {
        if (!msi.count(x)) {
            sst.push_back(x);
            msi[x] = sst.size() - 1;
        }
        return msi[x];
    }

    void Init() {
        sst.clear();
        msi.clear();
        ssc.clear();
        return;
    }

    void Push() {
        ssc.push_back(ID(sit()));
        return;
    }

    void Dup() {
        ssc.push_back(ssc.back());
        return;
    }

    void Union() {
        int x = ssc.back(); ssc.pop_back();
        int y = ssc.back(); ssc.pop_back();
        sit sx = sst[x];
        sit sy = sst[y];
        sit res;
        for (auto i : sx) res.insert(i);
        for (auto i : sy) res.insert(i);
        ssc.push_back(ID(res));
        return;
    }

    void Intersect() {
        int x = ssc.back(); ssc.pop_back();
        int y = ssc.back(); ssc.pop_back();
        sit sx = sst[x];
        sit sy = sst[y];
        sit res;
        for (auto i : sx) {
            if (sy.count(i)) {
                res.insert(i);
            }
        }
        ssc.push_back(ID(res));
        return;
    }

    void Add() {
        int x = ssc.back(); ssc.pop_back();
        int y = ssc.back(); ssc.pop_back();
        sit sx = sst[x];
        sit sy = sst[y];
        sit res;
        res = sy;
        res.insert(ID(sx));
        ssc.push_back(ID(res));
        return;
    }
} SSC;

void mian() {
    SSC.Init();
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> opt;
        if (opt == PUSH) SSC.Push();
        if (opt == DUP) SSC.Dup();
        if (opt == UNION) SSC.Union();
        if (opt == INTERSECT) SSC.Intersect();
        if (opt == ADD) SSC.Add();
        std::cout << SSC.sst[SSC.ssc.back()].size() << '\n';
    }
    std::cout << "***" << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}