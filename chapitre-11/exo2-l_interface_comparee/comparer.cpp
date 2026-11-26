#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace
{
std::vector<std::string> lireListe()
{
    int n = 0;
    std::cin >> n;
    std::vector<std::string> noms;
    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        std::cin >> nom;
        noms.push_back(nom);
    }
    return noms;
}
}  // namespace

int main()
{
    const std::vector<std::string> a = lireListe();
    const std::vector<std::string> b = lireListe();

    const std::set<std::string> ensembleA(a.begin(), a.end());
    const std::set<std::string> ensembleB(b.begin(), b.end());

    int communs = 0;
    for (const std::string& nom : ensembleA)
    {
        if (ensembleB.count(nom) > 0)
        {
            ++communs;
        }
    }
    std::cout << "DEUX " << communs << "\n";

    int differentes = 0;

    std::set<std::string> dejaA;
    for (const std::string& nom : a)
    {
        if (ensembleB.count(nom) == 0 && dejaA.insert(nom).second)
        {
            std::cout << "SEUL_A " << nom << "\n";
            ++differentes;
        }
    }

    std::set<std::string> dejaB;
    for (const std::string& nom : b)
    {
        if (ensembleA.count(nom) == 0 && dejaB.insert(nom).second)
        {
            std::cout << "SEUL_B " << nom << "\n";
            ++differentes;
        }
    }

    const int total = communs + differentes;
    std::cout << "DIFFERENTES " << differentes << " SUR " << total << "\n";
    return 0;
}
