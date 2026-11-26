#include <iostream>
#include <string>
#include <vector>

static bool estCaractereNom(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static bool estLettreChiffreOuTiret(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || c == '_';
}

static bool estCommentaire(const std::string& ligne)
{
    std::string::size_type p = 0;
    while (p < ligne.size() && (ligne[p] == ' ' || ligne[p] == '\t')) {
        ++p;
    }
    return ligne.compare(p, 2, "//") == 0;
}

static void chercherVariables(const std::string& ligne,
                              std::vector<std::string>& trouvees)
{
    for (std::string::size_type i = 0; i + 3 <= ligne.size(); ++i) {
        if (ligne.compare(i, 3, "NK_") != 0) {
            continue;
        }
        if (i > 0 && estLettreChiffreOuTiret(ligne[i - 1])) {
            continue;
        }
        std::string::size_type j = i + 3;
        while (j < ligne.size() && estCaractereNom(ligne[j])) {
            ++j;
        }
        if (j > i + 3 && j < ligne.size() && ligne[j] == '=') {
            const std::string nom = ligne.substr(i, j - i);
            bool dejaVu = false;
            for (const std::string& v : trouvees) {
                if (v == nom) {
                    dejaVu = true;
                }
            }
            if (!dejaVu) {
                trouvees.push_back(nom);
            }
            i = j - 1;
        }
    }
}

int main()
{
    long long n = 0;
    if (!(std::cin >> n)) {
        n = 0;
    }
    std::string reste;
    std::getline(std::cin, reste);

    std::vector<std::string> lignes;
    for (long long i = 0; i < n; ++i) {
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            break;
        }
        if (!ligne.empty() && ligne.back() == '\r') {
            ligne.pop_back();
        }
        lignes.push_back(ligne);
    }

    std::vector<std::string>::size_type e = 0;
    while (e < lignes.size() && estCommentaire(lignes[e])) {
        ++e;
    }

    std::vector<std::string> variables;
    for (std::vector<std::string>::size_type i = 0; i < e; ++i) {
        chercherVariables(lignes[i], variables);
    }

    const long long entete = static_cast<long long>(e);
    const long long part = (n > 0) ? (100 * entete / n) : 0;

    std::cout << "ENTETE " << entete << "\n";
    std::cout << "IGNOREES " << ((n > 0) ? n - entete : 0) << "\n";
    if (variables.empty()) {
        std::cout << "VARIABLE AUCUNE\n";
    } else {
        for (const std::string& v : variables) {
            std::cout << "VARIABLE " << v << "\n";
        }
    }
    std::cout << "PART " << part << "\n";
    return 0;
}