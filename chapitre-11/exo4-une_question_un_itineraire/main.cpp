#include <cstdlib>
#include <iostream>
#include <string>

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

std::string extraire(const std::string& texte, std::string& valeur)
{
    const std::string cle = "\"library_path\"";

    std::size_t pos = texte.find(cle);
    if (pos == std::string::npos)
    {
        return "CLE";
    }

    std::size_t deuxPoints = texte.find(':', pos + cle.size());
    if (deuxPoints == std::string::npos)
    {
        return "DEUX_POINTS";
    }

    std::size_t debut = texte.find('"', deuxPoints + 1);
    if (debut == std::string::npos)
    {
        return "GUILLEMET";
    }

    std::size_t fin = texte.find('"', debut + 1);
    if (fin == std::string::npos)
    {
        return "GUILLEMET";
    }

    std::string brut = texte.substr(debut + 1, fin - debut - 1);
    if (brut.empty())
    {
        return "VIDE";
    }

    valeur.clear();
    for (std::size_t k = 0; k < brut.size(); ++k)
    {
        if (brut[k] == '\\' && k + 1 < brut.size() && brut[k + 1] == '\\')
        {
            continue;
        }
        valeur += brut[k];
    }
    return "";
}

int main()
{
    std::string ligne;
    if (!lireLigne(ligne))
    {
        return 0;
    }
    int K = std::atoi(ligne.c_str());

    for (int i = 1; i <= K; ++i)
    {
        std::string registre;
        lireLigne(registre);

        std::string ligneL;
        lireLigne(ligneL);
        int L = std::atoi(ligneL.c_str());

        std::string texte;
        for (int j = 0; j < L; ++j)
        {
            std::string contenu;
            lireLigne(contenu);
            texte += contenu;
            texte += '\n';
        }

        if (registre == "-")
        {
            std::cout << i << " REGISTRE AUCUN\n";
            continue;
        }

        std::cout << i << " MANIFESTE " << registre << "\n";

        if (L < 0)
        {
            std::cout << i << " ECHEC ILLISIBLE\n";
            continue;
        }

        std::string valeur;
        std::string raison = extraire(texte, valeur);
        if (!raison.empty())
        {
            std::cout << i << " ECHEC " << raison << "\n";
            continue;
        }

        std::cout << i << " VALEUR " << valeur << "\n";

        bool absolu = (valeur.size() >= 2 && valeur[1] == ':')
            || valeur[0] == '\\' || valeur[0] == '/';

        std::string charge = valeur;
        if (absolu)
        {
            std::cout << i << " ABSOLU\n";
        }
        else
        {
            std::cout << i << " RELATIF\n";
            std::size_t sep = registre.find_last_of("\\/");
            std::string dossier;
            if (sep != std::string::npos)
            {
                dossier = registre.substr(0, sep + 1);
            }
            charge = dossier + valeur;
        }
        std::cout << i << " CHARGE " << charge << "\n";
    }
    return 0;
}
