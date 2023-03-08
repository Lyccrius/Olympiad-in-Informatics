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

const int maxN = 100;

int N;
int x, y, z, r;
int xl[maxN + 10], xr[maxN + 10];
int yl[maxN + 10], yr[maxN + 10];
int zl[maxN + 10], zr[maxN + 10];
std::vector<int> rawX;
std::vector<int> rawY;
std::vector<int> rawZ;
int dif[maxN * 2 + 10][maxN * 2 + 10][maxN * 2 + 10];
int pre[maxN * 2 + 10][maxN * 2 + 10][maxN * 2 + 10];
lxl ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> x >> y >> z >> r;
        xl[i] = x - r; rawX.push_back(xl[i]);
        xr[i] = x + r; rawX.push_back(xr[i]);
        yl[i] = y - r; rawY.push_back(yl[i]);
        yr[i] = y + r; rawY.push_back(yr[i]);
        zl[i] = z - r; rawZ.push_back(zl[i]);
        zr[i] = z + r; rawZ.push_back(zr[i]);
    }
    std::sort(rawX.begin(), rawX.end());
    std::sort(rawY.begin(), rawY.end());
    std::sort(rawZ.begin(), rawZ.end());
    rawX.erase(std::unique(rawX.begin(), rawX.end()), rawX.end());
    rawY.erase(std::unique(rawY.begin(), rawY.end()), rawY.end());
    rawZ.erase(std::unique(rawZ.begin(), rawZ.end()), rawZ.end());
    for (int i = 1; i <= N; i++) {
        xl[i] = std::lower_bound(rawX.begin(), rawX.end(), xl[i]) - rawX.begin() + 1;
        xr[i] = std::lower_bound(rawX.begin(), rawX.end(), xr[i]) - rawX.begin() + 1;
        yl[i] = std::lower_bound(rawY.begin(), rawY.end(), yl[i]) - rawY.begin() + 1;
        yr[i] = std::lower_bound(rawY.begin(), rawY.end(), yr[i]) - rawY.begin() + 1;
        zl[i] = std::lower_bound(rawZ.begin(), rawZ.end(), zl[i]) - rawZ.begin() + 1;
        zr[i] = std::lower_bound(rawZ.begin(), rawZ.end(), zr[i]) - rawZ.begin() + 1;
        dif[xl[i]][yl[i]][zl[i]]++;
        dif[xr[i]][yl[i]][zl[i]]--;
        dif[xl[i]][yr[i]][zl[i]]--;
        dif[xl[i]][yl[i]][zr[i]]--;
        dif[xr[i]][yr[i]][zl[i]]++;
        dif[xr[i]][yl[i]][zr[i]]++;
        dif[xl[i]][yr[i]][zr[i]]++;
        dif[xr[i]][yr[i]][zr[i]]--;
    }
    for (int x = 1; x < rawX.size(); x++) {
        for (int y = 1; y < rawY.size(); y++) {
            for (int z = 1; z < rawZ.size(); z++) {
                pre[x][y][z] = dif[x][y][z]
                             + pre[x - 1][y][z]
                             + pre[x][y - 1][z]
                             + pre[x][y][z - 1]
                             - pre[x - 1][y - 1][z]
                             - pre[x - 1][y][z - 1]
                             - pre[x][y - 1][z - 1]
                             + pre[x - 1][y - 1][z - 1];
                if (pre[x][y][z]) {
                    ans += 1ll 
                         * (rawX[x] - rawX[x - 1])
                         * (rawY[y] - rawY[y - 1])
                         * (rawZ[z] - rawZ[z - 1]);
                            
                }
            }
        }
    }
    std::cout << ans;
    return 0;
}