#include <iostream>
#include <string>

int main()
{
    int N = 0;
    int T = 0;
    std::cin >> N >> T;

    if (N < 1 || N > 4)
    {
        std::cout << "CHAINE REFUSEE\n";
        return 0;
    }

    std::string mot;
    if (T > 0)
    {
        std::cin >> mot;
    }

    int prochaine = 0;
    int fins = 0;
    int rendues = 0;
    int sautees = 0;

    for (int t = 1; t <= T; ++t)
    {
        int lacet = t - 1;
        bool rendre = (mot[t - 1] == '1');

        if (rendre)
        {
            std::cout << t << " OUI 1 " << lacet << " " << prochaine << "\n";
            prochaine = (prochaine + 1) % N;
            ++rendues;
        }
        else
        {
            std::cout << t << " NON 0\n";
            ++sautees;
        }
        ++fins; // une fin de trame par image, rendue ou non
    }

    std::cout << "FINS " << fins << "\n";
    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "SAUTEES " << sautees << "\n";
    std::cout << "PROCHAINE " << prochaine << "\n";
    return 0;
}