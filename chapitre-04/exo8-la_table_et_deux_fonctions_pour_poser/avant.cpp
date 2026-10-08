#include <iostream>
#include <string>

int main() {
    long long L = 0, P = 0, H = 0, ep = 0, pied = 0, tx = 0, tz = 0;
    std::cin >> L >> P >> H >> ep >> pied >> tx >> tz;

    std::cout << "PLATEAU " << tx << " " << (H - ep) + ep / 2 << " " << tz << "\n";

    long long dx = L / 2 - pied;
    long long dz = P / 2 - pied;
    long long hauteurPied = H - ep;

    std::cout << "PIED " << tx - dx << " " << hauteurPied / 2 << " " << tz - dz << "\n";
    std::cout << "PIED " << tx + dx << " " << hauteurPied / 2 << " " << tz - dz << "\n";
    std::cout << "PIED " << tx - dx << " " << hauteurPied / 2 << " " << tz + dz << "\n";
    std::cout << "PIED " << tx + dx << " " << hauteurPied / 2 << " " << tz + dz << "\n";

    int n = 0;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long sx = 0, sy = 0, sz = 0, x = 0, z = 0;
        std::string ou;
        std::cin >> nom >> sx >> sy >> sz >> x >> z >> ou;

        if (ou == "SOL") {
            std::cout << nom << " " << x << " " << sy / 2 << " " << z << "\n";
        } else {
            std::cout << nom << " " << x << " " << H + sy / 2 << " " << z << "\n";
        }
    }

    return 0;
}