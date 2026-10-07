#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    int visibles = 0;
    int enPanne = 0;

    for (int i = 0; i < n; ++i) {
        std::string name;
        long long drapeaux = 0;
        long long sx = 0, sy = 0, sz = 0;
        long long distance = 0;
        long long lumieres = 0;
        long long ambiante = 0;
        long long proche = 0;

        std::cin >> name >> drapeaux >> sx >> sy >> sz >> distance
                  >> lumieres >> ambiante >> proche;

        std::string verdict;

        if ((drapeaux & 2LL) == 0) {
            verdict = "RENDER3D ETEINT";
        } else if (sx == 0 || sy == 0 || sz == 0) {
            verdict = "ECHELLE NULLE";
        } else {
            long long faceAvant = distance - sz / 2;
            if (faceAvant <= 0) {
                verdict = "CAMERA DANS LE CUBE";
            } else if (faceAvant < proche) {
                verdict = "COUPE PAR LE PLAN PROCHE";
            } else if (lumieres == 0 && ambiante == 0) {
                verdict = "PAS DE LUMIERE";
            } else {
                verdict = "VISIBLE";
            }
        }

        if (verdict == "VISIBLE") {
            ++visibles;
        } else {
            ++enPanne;
        }

        std::cout << name << " " << verdict << "\n";
    }

    std::cout << "VISIBLES " << visibles << "\n";
    std::cout << "EN PANNE " << enPanne << "\n";

    return 0;
}