#include <iostream>
#include <string>

int main() {
    long long W = 0, H = 0, seuil = 0;
    std::cin >> W >> H >> seuil;

    int n = 0;
    std::cin >> n;

    int ok = 0;
    int aReprendre = 0;

    for (int i = 0; i < n; ++i) {
        std::string name;
        long long u = 0, y = 0, l = 0, h = 0, e = 0, d = 0;
        std::cin >> name >> u >> y >> l >> h >> e >> d;

        long long saillie = d + e / 2;
        long long faceArriere = d - e / 2;

        bool deborde = (u - l / 2 < -W / 2) || (u + l / 2 > W / 2)
                    || (y - h / 2 < 0) || (y + h / 2 > H);

        std::string verdict;

        if (deborde) {
            verdict = "DEBORDE";
        } else if (saillie <= 0) {
            verdict = "INVISIBLE";
        } else if (saillie < seuil) {
            verdict = "CLIGNOTE";
        } else if (faceArriere > seuil) {
            verdict = "DECOLLE";
        } else {
            verdict = "OK";
        }

        if (verdict == "OK") {
            ++ok;
        } else {
            ++aReprendre;
        }

        std::cout << name << " " << saillie << " " << verdict << "\n";
    }

    std::cout << "OK " << ok << "\n";
    std::cout << "A REPRENDRE " << aReprendre << "\n";

    return 0;
}