#include <iostream>
#include <string>

int main()
{
    std::string mode;
    int T = 0;
    std::cin >> mode >> T;

    std::string mot;
    if (T > 0)
    {
        std::cin >> mot;
    }

    bool ouverte = false;
    int rendues = 0;
    int perdues = 0;
    int erreurs = 0;
    int premierRefus = 0; // 0 = aucun

    for (int t = 1; t <= T; ++t)
    {
        bool signe = (mot[t - 1] == '1');
        bool rendre = false;
        std::string w;
        std::string b;
        std::string e = "-";

        if (ouverte)
        {
            w = "REFUSE";
            ++erreurs;
            if (premierRefus == 0)
            {
                premierRefus = t;
            }
        }
        else
        {
            w = "OK";
            rendre = signe;
        }

        if (ouverte)
        {
            b = "REFUSE";
            ++erreurs;
        }
        else
        {
            b = "OK";
            ouverte = true;
        }

        if (mode == "TOUJOURS" || rendre)
        {
            if (ouverte)
            {
                e = "OK";
                ouverte = false;
            }
            else
            {
                e = "REFUSE";
                ++erreurs;
            }
        }

        if (rendre)
        {
            ++rendues;
        }
        else if (signe)
        {
            ++perdues;
        }

        std::cout << t << " " << w << " " << b << " "
                  << (rendre ? "OUI" : "NON") << " " << e << "\n";
    }

    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "PERDUES " << perdues << "\n";
    std::cout << "ERREURS " << erreurs << "\n";
    if (premierRefus == 0)
    {
        std::cout << "PREMIER REFUS AUCUN\n";
    }
    else
    {
        std::cout << "PREMIER REFUS " << premierRefus << "\n";
    }
    return 0;
}