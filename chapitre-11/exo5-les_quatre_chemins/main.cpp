#include <iostream>
#include <string>

int main()
{
    int K = 0;
    std::cin >> K;
    if (K <= 0)
    {
        std::cout << "AUCUNE MACHINE\n";
        return 0;
    }

    for (int i = 1; i <= K; ++i)
    {
        std::string D;
        std::string V;
        std::string L;
        std::string R;
        std::string B;
        std::string G;
        std::cin >> D >> V >> L >> R >> B >> G;

        int chargees = 0;
        int liberees = 0;
        bool casque = false;

        if (D == "SIMULATEUR")
        {
            std::cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        }
        else
        {
            bool chargee = false;
            bool entree = false;
            std::string typeChargee;
            std::string source;

            if (V == "ABSENT")
            {
                std::cout << i << " VARIABLE IGNOREE\n";
            }
            else if (V == "BON" || V == "SANS")
            {
                std::cout << i << " VARIABLE CHARGEE\n";
                ++chargees;
                chargee = true;
                typeChargee = V;
                source = "VARIABLE";
            }

            if (!chargee)
            {
                if (L == "ABSENT")
                {
                    std::cout << i << " LOADER ABSENT\n";
                }
                else if (L == "BON" || L == "SANS")
                {
                    std::cout << i << " LOADER CHARGE\n";
                    ++chargees;
                    chargee = true;
                    typeChargee = L;
                    source = "LOADER";
                }
            }

            if (chargee)
            {
                if (typeChargee == "BON")
                {
                    entree = true;
                }
                else
                {
                    std::cout << i << " SANS_ENTREE\n";
                    ++liberees;
                    chargee = false;
                }
            }

            if (!entree)
            {
                std::cout << i << " DIRECT " << R << "\n";
                if (R == "NEGO_KO" || R == "BON")
                {
                    ++chargees;
                    chargee = true;
                    if (R == "BON")
                    {
                        entree = true;
                        source = "DIRECT";
                    }
                }
            }

            if (!entree)
            {
                std::cout << i << " BACKEND INDISPONIBLE\n";
                if (chargee)
                {
                    ++liberees;
                    chargee = false;
                }
            }
            else
            {
                std::cout << i << " BACKEND OPENXR " << source << "\n";
                if (B == "NON")
                {
                    std::cout << i << " LIAISON ECHOUEE\n";
                    ++liberees;
                    chargee = false;
                }
                else
                {
                    casque = true;
                }
            }
        }

        if (casque)
        {
            std::cout << i << " NIVEAU 1 CASQUE\n";
        }
        else if (G == "OUI")
        {
            std::cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        }
        else
        {
            std::cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";
        }

        std::cout << i << " CHARGEES " << chargees << " LIBEREES " << liberees << "\n";
    }
    return 0;
}
