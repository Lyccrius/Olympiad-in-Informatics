#include <iostream>
#include <cmath>

const double eps = 1e-6;

double Ax, Ay, Bx, By;
double Cx, Cy, Dx, Dy;
double P, Q, R;

double dis(double ax, double ay, double bx, double by) {
    double dx = ax - bx;
    double dy = ay - by;
    return std::sqrt(dx * dx + dy * dy);
}

double calc(double Ex, double Ey, double Fx, double Fy) {
    double ret = 0;
    ret += dis(Ax, Ay, Ex, Ey) / P;
    ret += dis(Ex, Ey, Fx, Fy) / R;
    ret += dis(Fx, Fy, Dx, Dy) / Q;
    return ret;
}

double solveF(double lx, double ly, double rx, double ry, double Ex, double Ey) {
    while (std::fabs(rx - lx) >= eps || std::fabs(ry - ly) >= eps) {
        double gx = (rx - lx) / 3;
        double gy = (ry - ly) / 3;
        double lxm = lx + gx;
        double rxm = rx - gx;
        double lym = ly + gy;
        double rym = ry - gy;
        if (calc(Ex, Ey, lxm, lym) > calc(Ex, Ey, rxm, rym)) lx = lxm, ly = lym;
        else rx = rxm, ry = rym;
    }
    return calc(Ex, Ey, lx, ly);
}

double solveE(double lx, double ly, double rx, double ry) {
    while (std::fabs(rx - lx) >= eps || std::fabs(ry - ly) >= eps) {
        double gx = (rx - lx) / 3;
        double gy = (ry - ly) / 3;
        double lxm = lx + gx;
        double rxm = rx - gx;
        double lym = ly + gy;
        double rym = ry - gy;
        if (solveF(Cx, Cy, Dx, Dy, lxm, lym) > solveF(Cx, Cy, Dx, Dy, rxm, rym)) lx = lxm, ly = lym;
        else rx = rxm, ry = rym;
    }
    return solveF(Cx, Cy, Dx, Dy, lx, ly);
}

int main() {
    std::cin >> Ax >> Ay >> Bx >> By;
    std::cin >> Cx >> Cy >> Dx >> Dy;
    std::cin >> P >> Q >> R;
    printf("%.2lf\n", solveE(Ax, Ay, Bx, By));
    return 0;
}