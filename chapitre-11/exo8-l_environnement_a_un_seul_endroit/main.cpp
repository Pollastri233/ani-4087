#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool lireNombre(const std::string& s, std::size_t& pos, long long& valeur)
{
    std::size_t i = pos;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) {
        ++i;
    }
    bool negatif = false;
    if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
        negatif = (s[i] == '-');
        ++i;
    }
    bool chiffre = false;
    long long v = 0;
    while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
        v = v * 10 + (s[i] - '0');
        chiffre = true;
        ++i;
    }
    if (!chiffre) {
        valeur = 0;
        pos = i;
        return false;
    }
    valeur = negatif ? -v : v;
    pos = i;
    return true;
}

bool lireInterrupteur(const std::string& s)
{
    if (s[0] == '0' || s == "false") {
        return false;
    }
    return true;
}

void retirerCR(std::string& s)
{
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

}  // namespace

int main()
{
    std::string ligne;

    std::getline(std::cin, ligne);
    retirerCR(ligne);
    std::istringstream l1(ligne);
    std::string backend, demi, profondeur, liste;
    long long hz = 0, latence = 0;
    l1 >> backend >> hz >> demi >> profondeur >> liste >> latence;
    bool bDemi = (demi == "OUI");
    bool bProf = (profondeur == "OUI");
    bool bListe = (liste == "OUI");

    std::string loader;
    std::getline(std::cin, loader);
    retirerCR(loader);

    std::getline(std::cin, ligne);
    retirerCR(ligne);
    std::istringstream l3(ligne);
    std::string modePose;
    l3 >> modePose;
    bool fixe = (modePose == "FIXE");
    long long pose[5] = {0, 0, 0, 0, 0};
    if (fixe) {
        for (int i = 0; i < 5; ++i) {
            l3 >> pose[i];
        }
    }

    std::getline(std::cin, ligne);
    int m = std::atoi(ligne.c_str());
    int appliquees = 0;
    int ignorees = 0;

    for (int k = 0; k < m; ++k) {
        std::string var;
        std::getline(std::cin, var);
        retirerCR(var);

        std::size_t egal = var.find('=');
        if (egal == std::string::npos) {
            ++ignorees;
            continue;
        }
        std::string nom = var.substr(0, egal);
        std::string val = var.substr(egal + 1);

        if (val.empty()) {
            ++ignorees;
            continue;
        }

        if (nom == "NK_XR_BACKEND") {
            if (val == "openxr") {
                backend = "OPENXR";
                ++appliquees;
            } else {
                ++ignorees;
            }
        } else if (nom == "NK_XR_HZ") {
            std::size_t p = 0;
            lireNombre(val, p, hz);
            ++appliquees;
        } else if (nom == "NK_XR_SIM_LATENCY_MS") {
            std::size_t p = 0;
            lireNombre(val, p, latence);
            ++appliquees;
        } else if (nom == "NK_XR_HALF_RATE") {
            bDemi = lireInterrupteur(val);
            ++appliquees;
        } else if (nom == "NK_XR_DEPTH_LAYER") {
            bProf = lireInterrupteur(val);
            ++appliquees;
        } else if (nom == "NK_XR_LIST_EXT") {
            bListe = lireInterrupteur(val);
            ++appliquees;
        } else if (nom == "NK_XR_OPENXR_LOADER") {
            loader = val;
            ++appliquees;
        } else if (nom == "NK_XR_SIM_POSE") {
            std::vector<long long> nombres;
            std::size_t p = 0;
            while (p < val.size() && nombres.size() < 5) {
                long long n = 0;
                if (!lireNombre(val, p, n)) {
                    break;
                }
                nombres.push_back(n);
                while (p < val.size() && (val[p] == ',' || val[p] == ' ')) {
                    ++p;
                }
            }
            if (nombres.size() == 5) {
                fixe = true;
                for (int i = 0; i < 5; ++i) {
                    pose[i] = nombres[static_cast<std::size_t>(i)];
                }
                ++appliquees;
            } else {
                ++ignorees;
            }
        } else {
            ++ignorees;
        }
    }

    std::cout << "BACKEND " << backend << "\n";
    std::cout << "HZ " << hz << "\n";
    std::cout << "DEMI " << (bDemi ? "OUI" : "NON") << "\n";
    std::cout << "PROFONDEUR " << (bProf ? "OUI" : "NON") << "\n";
    std::cout << "LISTE " << (bListe ? "OUI" : "NON") << "\n";
    std::cout << "LOADER " << loader << "\n";
    std::cout << "LATENCE " << latence << "\n";
    if (fixe) {
        std::cout << "POSE FIXE";
        for (int i = 0; i < 5; ++i) {
            std::cout << " " << pose[i];
        }
        std::cout << "\n";
    } else {
        std::cout << "POSE LIBRE\n";
    }
    std::cout << "APPLIQUEES " << appliquees << "\n";
    std::cout << "IGNOREES " << ignorees << "\n";
    return 0;
}
