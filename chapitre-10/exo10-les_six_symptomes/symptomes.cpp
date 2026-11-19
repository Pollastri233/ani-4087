#include <iostream>
#include <string>

void ajouter(std::string& liste, const std::string& symptome)
{
    if (!liste.empty())
    {
        liste += " ";
    }
    liste += symptome;
}

int main()
{
    int N = 0;
    std::cin >> N;

    int muettes = 0;

    for (int i = 1; i <= N; ++i)
    {
        std::string fin;
        int g = 1;
        int d = 1;
        char instant = 'P';
        char pose = 'R';
        char espace = 'S';
        std::cin >> fin >> g >> d >> instant >> pose >> espace;

        std::string symptomes;
        if (fin == "JAMAIS")
        {
            ajouter(symptomes, "FIGE");
        }
        else if (fin == "SI_RENDU")
        {
            ajouter(symptomes, "NE_REPART_PAS");
        }
        if (g == 0)
        {
            ajouter(symptomes, "OEIL_NOIR_G");
        }
        if (d == 0)
        {
            ajouter(symptomes, "OEIL_NOIR_D");
        }
        if (instant == 'N')
        {
            ajouter(symptomes, "TREMBLE");
        }
        if (pose == 'F')
        {
            ajouter(symptomes, "DE_TRAVERS");
        }
        if (espace == 'L')
        {
            ajouter(symptomes, "DECALE");
        }

        bool dit = (fin != "TOUJOURS") || g == 0 || d == 0;

        std::cout << i << " CASQUE " << (symptomes.empty() ? "AUCUN" : symptomes) << "\n";
        std::cout << i << " SIMULATEUR " << (dit ? "DIT" : "MUET") << "\n";

        if (!dit && !symptomes.empty())
        {
            ++muettes;
        }
    }

    std::cout << "MUETTES " << muettes << "\n";
    return 0;
}
