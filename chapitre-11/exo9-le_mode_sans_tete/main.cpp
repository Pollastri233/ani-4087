#include <iostream>
#include <string>
#include <vector>

int main()
{
    long long hz = 0;
    std::cin >> hz;

    std::string mode;
    std::cin >> mode;

    long long pose[5] = {0, 0, 0, 1700, 0};
    if (mode == "FIXE")
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cin >> pose[i];
        }
    }

    int T = 0;
    std::cin >> T;

    std::vector<long long> a;
    std::vector<long long> b;
    if (T > 0)
    {
        a.resize(T);
        b.resize(T);
        for (int i = 0; i < T; ++i)
        {
            std::cin >> a[i];
        }
        for (int i = 0; i < T; ++i)
        {
            std::cin >> b[i];
        }
    }

    if (hz <= 1)
    {
        hz = 72;
    }
    const long long p = 1000000000LL / hz;

    std::cout << "PERIODE " << p << "\n";
    std::cout << "POSE";
    for (int i = 0; i < 5; ++i)
    {
        std::cout << " " << pose[i];
    }
    std::cout << "\n";

    int premierBrut = 0;
    int premierRelatif = 0;

    for (int i = 0; i < T; ++i)
    {
        const long long predA = a[i] + p;
        const long long predB = b[i] + p;
        const long long predA0 = a[0] + p;
        const long long predB0 = b[0] + p;

        const long long brut = predB - predA;
        const long long relatif = (predB - predB0) - (predA - predA0);
        const long long scripte = static_cast<long long>(i + 1) * p;

        if (brut != 0 && premierBrut == 0)
        {
            premierBrut = i + 1;
        }
        if (relatif != 0 && premierRelatif == 0)
        {
            premierRelatif = i + 1;
        }

        std::cout << (i + 1) << " BRUT " << brut << " RELATIF " << relatif
                  << " SCRIPTE " << scripte << "\n";
    }

    if (premierBrut == 0)
    {
        std::cout << "BRUT IDENTIQUE\n";
    }
    else
    {
        std::cout << "BRUT DIFFERENT " << premierBrut << "\n";
    }

    if (premierRelatif == 0)
    {
        std::cout << "RELATIF IDENTIQUE\n";
    }
    else
    {
        std::cout << "RELATIF DIFFERENT " << premierRelatif << "\n";
    }

    return 0;
}
