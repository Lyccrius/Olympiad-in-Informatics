#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<lxl> vlc;

int t;
lxl b, k;
lxl sx, sy;
lxl gx, gy;
vlc ds, xs, ys;
vlc dg, xg, yg;

lxl dis(lxl x1, lxl y1, lxl x2, lxl y2) {
    lxl ret = 0;
    if (x1 % b == 0 && x2 % b == 0 && y1 / b == y2 / b) {
        if (x1 == x2) return std::abs(y1 - y2);
        if (x1 != x2) return std::abs(x1 - x2) + std::min(y1 % b + y2 % b, 2 * b - y1 % b - y2 % b);
    }
    if (y1 % b == 0 && y2 % b == 0 && x1 / b == x2 / b) {
        if (y1 == y2) return std::abs(x1 - x2);
        if (y1 != y2) return std::abs(y1 - y2) + std::min(x1 % b + x2 % b, 2 * b - x1 % b - x2 % b);
    }
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void mian() {
    ds.clear();
    xs.clear();
    ys.clear();
    dg.clear();
    xg.clear();
    yg.clear();
    std::cin >> b >> k;
    std::cin >> sx >> sy;
    std::cin >> gx >> gy;
    if (sx % b == 0 || sy % b == 0) {
        ds.push_back(0); xs.push_back(sx); ys.push_back(sy);
    } else {
        ds.push_back(1ll * (sx - sx / b * b) * k); xs.push_back(sx / b * b); ys.push_back(sy);
        ds.push_back(1ll * (sy - sy / b * b) * k); xs.push_back(sx); ys.push_back(sy / b * b);
        ds.push_back(1ll * ((sy / b + 1) * b - sy) * k); xs.push_back(sx); ys.push_back((sy / b + 1) * b);
        ds.push_back(1ll * ((sx / b + 1) * b - sx) * k); xs.push_back((sx / b + 1) * b); ys.push_back(sy);
    }
    if (gx % b == 0 || gy % b == 0) {
        dg.push_back(0); xg.push_back(gx); yg.push_back(gy);
    } else {
        dg.push_back(1ll * (gx - gx / b * b) * k); xg.push_back(gx / b * b); yg.push_back(gy);
        dg.push_back(1ll * (gy - gy / b * b) * k); xg.push_back(gx); yg.push_back(gy / b * b);
        dg.push_back(1ll * ((gy / b + 1) * b - gy) * k); xg.push_back(gx); yg.push_back((gy / b + 1) * b);
        dg.push_back(1ll * ((gx / b + 1) * b - gx) * k); xg.push_back((gx / b + 1) * b); yg.push_back(gy);
    }
    lxl ans = 1ll * (std::abs(sx - gx) + std::abs(sy - gy)) * k;
    for (int i = 0; i < ds.size(); i++) {
        for (int j = 0; j < dg.size(); j++) {
            lxl res = ds[i] + dg[j] + dis(xs[i], ys[i], xg[j], yg[j]);
            ans = std::min(ans, res);
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}