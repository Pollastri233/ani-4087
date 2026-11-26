#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool lireLigne(std::string& ligne)
{
    if (!std::getline(std::cin, ligne))
    {
        return false;
    }
    if (!ligne.empty() && ligne.back() == '\r')
    {
        ligne.pop_back();
    }
    return true;
}

bool estSigneDeNom(char c)
{
    unsigned char u = static_cast<unsigned char>(c);
    return std::isalnum(u) != 0 || c == '_';
}

bool contientNom(const std::string& texte, const std::string& nom)
{
    if (nom.empty())
    {
        return false;
    }

    std::size_t pos = texte.find(nom);
    while (pos != std::string::npos)
    {
        bool avantOk = (pos == 0) || !estSigneDeNom(texte[pos - 1]);
        std::size_t apres = pos + nom.size();
        bool apresOk = (apres >= texte.size()) || !estSigneDeNom(texte[apres]);
        if (avantOk && apresOk)
        {
            return true;
        }
        pos = texte.find(nom, pos + 1);
    }
    return false;
}

bool contientUnDesNoms(const std::string& texte, const std::vector<std::string>& noms)
{
    for (const std::string& nom : noms)
    {
        if (contientNom(texte, nom))
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> lireNoms(const std::string& ligne)
{
    std::istringstream flux(ligne);
    std::string etiquette;
    int n = 0;
    flux >> etiquette >> n;

    std::vector<std::string> noms;
    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        flux >> nom;
        noms.push_back(nom);
    }
    return noms;
}

int main()
{
    std::string ligneC;
    std::string ligneD;
    std::string ligneN;
    lireLigne(ligneC);
    lireLigne(ligneD);
    lireLigne(ligneN);

    std::vector<std::string> noms = lireNoms(ligneC);
    std::vector<std::string> defines = lireNoms(ligneD);
    int N = std::atoi(ligneN.c_str());

    int decisions = 0;
    int fuites = 0;
    int definis = 0;

    for (int l = 1; l <= N; ++l)
    {
        std::string ligne;
        lireLigne(ligne);

        std::size_t espace = ligne.find_first_of(" \t");
        std::string zone = ligne.substr(0, espace);
        std::string texte;
        if (espace != std::string::npos)
        {
            texte = ligne.substr(espace + 1);
        }

        std::size_t debut = texte.find_first_not_of(" \t");
        if (debut != std::string::npos && texte.compare(debut, 2, "//") == 0)
        {
            continue;
        }

        bool aNom = contientUnDesNoms(texte, noms);
        bool aDefine = contientUnDesNoms(texte, defines);

        if (aNom && zone == "INIT")
        {
            ++decisions;
        }

        if (aNom && (zone == "BOUCLE" || zone == "SCENE"))
        {
            std::cout << "FUITE " << l << " " << zone << "\n";
            ++fuites;
        }

        if (aDefine && zone != "FABRIQUE")
        {
            std::cout << "DEFINI " << l << " " << zone << "\n";
            ++definis;
        }
    }

    std::cout << "DECISIONS " << decisions << "\n";
    std::cout << "FUITES " << fuites << "\n";
    std::cout << "DEFINIS " << definis << "\n";
    if (fuites == 0 && definis == 0)
    {
        std::cout << "ABSTRACTION TENUE\n";
    }
    else
    {
        std::cout << "ABSTRACTION FUIT\n";
    }
    return 0;
}
