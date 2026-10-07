#include <iostream>
#include <string>
#include <vector>

struct Wall {
    std::string name;
    long long xmin, xmax, zmin, zmax;
};

struct Angle {
    std::string label;
    long long xleft, xright, zlow, zhigh;
};

int main() {
    long long L = 0, e = 0;
    std::cin >> L >> e;

    long long h = L / 2;

    int n = 0;
    std::cin >> n;

    std::vector<Wall> walls(n);
    for (int i = 0; i < n; ++i) {
        std::string name;
        long long cx = 0, cz = 0, sx = 0, sz = 0;
        std::cin >> name >> cx >> cz >> sx >> sz;

        long long xmin = cx - sx / 2;
        long long xmax = cx + sx / 2;
        long long zmin = cz - sz / 2;
        long long zmax = cz + sz / 2;

        walls[i] = Wall{name, xmin, xmax, zmin, zmax};

        std::cout << name << " " << xmin << " " << xmax << " " << zmin
                  << " " << zmax << "\n";
    }

    std::vector<Angle> angles = {
        {"FOND_GAUCHE", -h - e, -h, -h - e, -h},
        {"FOND_DROIT", h, h + e, -h - e, -h},
        {"ENTREE_GAUCHE", -h - e, -h, h, h + e},
        {"ENTREE_DROIT", h, h + e, h, h + e}
    };

    int trous = 0;

    for (const auto& a : angles) {
        bool bouche = false;
        for (const auto& w : walls) {
            if (w.xmin <= a.xleft && w.xmax >= a.xright
                && w.zmin <= a.zlow && w.zmax >= a.zhigh) {
                bouche = true;
                break;
            }
        }

        std::cout << a.label << " " << (bouche ? "BOUCHE" : "TROU") << "\n";

        if (!bouche) {
            ++trous;
        }
    }

    std::cout << "TROUS " << trous << "\n";

    return 0;
}