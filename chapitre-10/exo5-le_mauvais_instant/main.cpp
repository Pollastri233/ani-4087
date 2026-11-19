#include <iostream>

long long absolu(long long x)
{
    return (x < 0) ? -x : x;
}

int main()
{
    long long w = 0;
    int T = 0;
    std::cin >> w >> T;

    int fausses = 0;
    long long pireCasque = 0;
    long long pireSimulateur = 0;

    for (int t = 1; t <= T; ++t)
    {
        long long P = 0;
        long long S = 0;
        long long A = 0;
        char M = 'R';
        std::cin >> P >> S >> A >> M;

        long long casque = (M == 'F') ? w * (S - P) : 0;
        long long simulateur = w * (A - P);

        if (casque != 0)
        {
            ++fausses;
        }
        if (absolu(casque) > pireCasque)
        {
            pireCasque = absolu(casque);
        }
        if (absolu(simulateur) > pireSimulateur)
        {
            pireSimulateur = absolu(simulateur);
        }

        std::cout << t << " CASQUE " << casque
                  << " SIMULATEUR " << simulateur << "\n";
    }

    std::cout << "FAUSSES " << fausses << "\n";
    std::cout << "PIRE CASQUE " << pireCasque << "\n";
    std::cout << "PIRE SIMULATEUR " << pireSimulateur << "\n";
    return 0;
}