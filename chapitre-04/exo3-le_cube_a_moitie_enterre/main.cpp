#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        std::string name;
        long long e = 0;
        long long y = 0;
        std::cin >> name >> e >> y;

        long long demiHauteur = e / 2;
        long long bas = y - demiHauteur;
        long long haut = y + demiHauteur;

        std::string verdict;
        if (haut <= 0) {
            verdict = "SOUS LE SOL";
        } else if (bas < 0) {
            verdict = "ENTERRE";
        } else if (bas == 0) {
            verdict = "POSE";
        } else {
            verdict = "FLOTTE";
        }

        if (verdict != "POSE") {
            ++aCorriger;
        }

        long long ecart = (bas < 0) ? -bas : bas;
        if (ecart > pire) {
            pire = ecart;
        }

        std::cout << name << " " << bas << " " << haut << " " << verdict
                  << " " << demiHauteur << "\n";
    }

    std::cout << "A CORRIGER " << aCorriger << "\n";
    std::cout << "PIRE " << pire << "\n";

    return 0;
}