#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

bool finitParCpp(const std::string& nom)
{
    const std::string suffixe = ".cpp";
    return nom.size() >= suffixe.size()
        && nom.compare(nom.size() - suffixe.size(), suffixe.size(), suffixe) == 0;
}

int main()
{
    int E = 0;
    std::cin >> E;

    std::set<std::string> externes;
    for (int i = 0; i < E; ++i)
    {
        std::string nom;
        std::cin >> nom;
        externes.insert(nom);
    }

    int F = 0;
    std::cin >> F;

    std::vector<std::string> ordre;
    std::map<std::string, std::vector<std::string>> inclusions;
    for (int i = 0; i < F; ++i)
    {
        std::string nom;
        int k = 0;
        std::cin >> nom >> k;

        std::vector<std::string> liste;
        for (int j = 0; j < k; ++j)
        {
            std::string inclus;
            std::cin >> inclus;
            liste.push_back(inclus);
        }
        ordre.push_back(nom);
        inclusions[nom] = liste;
    }

    int touchees = 0;
    int unites = 0;

    for (const std::string& unite : ordre)
    {
        if (!finitParCpp(unite))
        {
            continue;
        }
        ++unites;

        std::map<std::string, std::string> parent;
        std::set<std::string> vus;
        std::queue<std::string> file;
        vus.insert(unite);
        file.push(unite);

        std::string trouve;
        while (!file.empty() && trouve.empty())
        {
            std::string courant = file.front();
            file.pop();

            auto it = inclusions.find(courant);
            if (it == inclusions.end())
            {
                continue;
            }

            for (const std::string& inclus : it->second)
            {
                if (vus.count(inclus) > 0)
                {
                    continue;
                }
                vus.insert(inclus);
                parent[inclus] = courant;

                if (externes.count(inclus) > 0)
                {
                    trouve = inclus;
                    break;
                }
                file.push(inclus);
            }
        }

        if (trouve.empty())
        {
            std::cout << unite << " NON\n";
        }
        else
        {
            std::vector<std::string> chemin;
            for (std::string cur = trouve; cur != unite; cur = parent[cur])
            {
                chemin.push_back(cur);
            }
            chemin.push_back(unite);
            std::reverse(chemin.begin(), chemin.end());

            std::cout << unite << " OUI ";
            for (std::size_t i = 0; i < chemin.size(); ++i)
            {
                if (i > 0)
                {
                    std::cout << ">";
                }
                std::cout << chemin[i];
            }
            std::cout << "\n";
            ++touchees;
        }
    }

    std::cout << "TOUCHEES " << touchees << " SUR " << unites << "\n";
    return 0;
}
