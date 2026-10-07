#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    int deplaces = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        std::string name;
        long long tx = 0, ty = 0, tz = 0;
        long long sx = 0, sy = 0, sz = 0;
        std::cin >> name >> tx >> ty >> tz >> sx >> sy >> sz;

        long long mx = (sx * tx) / 1000;
        long long my = (sy * ty) / 1000;
        long long mz = (sz * tz) / 1000;

        long long ex = tx - mx;
        if (ex < 0) {
            ex = -ex;
        }
        long long ey = ty - my;
        if (ey < 0) {
            ey = -ey;
        }
        long long ez = tz - mz;
        if (ez < 0) {
            ez = -ez;
        }

        long long ecart = ex;
        if (ey > ecart) {
            ecart = ey;
        }
        if (ez > ecart) {
            ecart = ez;
        }

        if (ecart != 0) {
            ++deplaces;
        }
        if (ecart > pire) {
            pire = ecart;
        }

        std::cout << name << " " << mx << " " << my << " " << mz
                  << " " << ecart << "\n";
    }

    std::cout << "DEPLACES " << deplaces << "\n";
    std::cout << "PIRE " << pire << "\n";

    return 0;
}