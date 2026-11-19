#include <iostream>
#include <string>

int main()
{
    int K = 0;
    int N = 0;
    std::cin >> K >> N;

    bool ouverte = false;
    int indice[2] = {0, 0};
    bool prise[2] = {false, false};
    int journal = 0;
    int avertissements = 0;
    int silencieux = 0;

    for (int i = 1; i <= N; ++i)
    {
        std::string nom;
        std::cin >> nom;
        std::string reponse;

        if (nom == "wait")
        {
            if (ouverte)
            {
                reponse = "REFUSE";
                ++journal;
            }
            else
            {
                reponse = "OK";
            }
        }
        else if (nom == "begin")
        {
            if (ouverte)
            {
                reponse = "REFUSE";
                ++journal;
            }
            else
            {
                reponse = "OK";
                ouverte = true;
            }
        }
        else if (nom == "acquire" || nom == "release")
        {
            std::string oeil;
            std::cin >> oeil;
            int o = (oeil == "G") ? 0 : 1;

            if (nom == "acquire")
            {
                if (prise[o])
                {
                    reponse = "REFUSE";
                    ++silencieux;
                }
                else
                {
                    reponse = "OK " + std::to_string(indice[o]);
                    prise[o] = true;
                }
            }
            else
            {
                if (!prise[o])
                {
                    reponse = "REFUSE";
                    ++silencieux;
                }
                else
                {
                    reponse = "OK";
                    prise[o] = false;
                    indice[o] = (indice[o] + 1) % K;
                }
            }
        }
        else if (nom == "end")
        {
            std::string a;
            std::cin >> a;
            bool projection = (a != "-");
            bool renseigne[2] = {false, false};
            if (projection)
            {
                std::string d;
                std::cin >> d;
                renseigne[0] = (a == "1");
                renseigne[1] = (d == "1");
            }

            if (!ouverte)
            {
                reponse = "REFUSE AUCUNE";
                ++journal;
            }
            else
            {
                ouverte = false; // la trame se ferme dans tous les cas
                if (projection && renseigne[0] && prise[0])
                {
                    reponse = "REFUSE ACQUISE G";
                    ++journal;
                }
                else if (projection && renseigne[1] && prise[1])
                {
                    reponse = "REFUSE ACQUISE D";
                    ++journal;
                }
                else
                {
                    reponse = "OK";
                    if (projection)
                    {
                        std::string manque;
                        for (int o = 0; o < 2; ++o)
                        {
                            if (!renseigne[o])
                            {
                                manque += (o == 0) ? " G" : " D";
                                ++avertissements;
                            }
                        }
                        if (!manque.empty())
                        {
                            reponse += " AVERT" + manque;
                        }
                    }
                }
            }
        }

        std::cout << i << " " << nom << " " << reponse << "\n";
    }

    std::cout << "JOURNAL " << journal << "\n";
    std::cout << "AVERTISSEMENTS " << avertissements << "\n";
    std::cout << "SILENCIEUX " << silencieux << "\n";
    return 0;
}