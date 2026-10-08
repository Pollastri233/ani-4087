#include <iostream>
#include <string>

struct Vec3 {
    long long x;
    long long y;
    long long z;
};

Vec3 PoserAuSol(long long sy, long long x, long long z) {
    return Vec3{x, sy / 2, z};
}

Vec3 PoserSurTable(long long sy, long long hauteurSupport, long long x, long long z) {
    return Vec3{x, hauteurSupport + sy / 2, z};
}

static void Afficher(const std::string& nom, const Vec3& v) {
    std::cout << nom << " " << v.x << " " << v.y << " " << v.z << "\n";
}

int main() {
    long long L = 0, P = 0, H = 0, ep = 0, pied = 0, tx = 0, tz = 0;
    std::cin >> L >> P >> H >> ep >> pied >> tx >> tz;

    Vec3 plateau = PoserSurTable(ep, H - ep, tx, tz);
    Afficher("PLATEAU", plateau);

    long long dx = L / 2 - pied;
    long long dz = P / 2 - pied;
    long long hauteurPied = H - ep;

    Afficher("PIED", PoserAuSol(hauteurPied, tx - dx, tz - dz));
    Afficher("PIED", PoserAuSol(hauteurPied, tx + dx, tz - dz));
    Afficher("PIED", PoserAuSol(hauteurPied, tx - dx, tz + dz));
    Afficher("PIED", PoserAuSol(hauteurPied, tx + dx, tz + dz));

    int n = 0;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long sx = 0, sy = 0, sz = 0, x = 0, z = 0;
        std::string ou;
        std::cin >> nom >> sx >> sy >> sz >> x >> z >> ou;

        Vec3 centre = (ou == "SOL") ? PoserAuSol(sy, x, z) : PoserSurTable(sy, H, x, z);
        Afficher(nom, centre);
    }

    return 0;
}