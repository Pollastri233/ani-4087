#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Reglage
{
    bool getenv = false;
    bool lit = false;
    bool pose = false;
};

int main()
{
    int R = 0;
    std::cin >> R;

    std::vector<std::string> ordre;
    std::map<std::string, Reglage> reglages;

    for (int i = 0; i < R; ++i)
    {
        std::string nom;
        std::string action;
        std::cin >> nom >> action;

        if (reglages.find(nom) == reglages.end())
        {
            ordre.push_back(nom);
        }

        Reglage& r = reglages[nom];
        if (action == "GETENV")
        {
            r.getenv = true;
        }
        else if (action == "LIT")
        {
            r.lit = true;
        }
        else if (action == "ECRIT" || action == "ENV")
        {
            r.pose = true;
        }
    }

    int menus = 0;
    for (const std::string& nom : ordre)
    {
        const Reglage& r = reglages[nom];
        std::string classe;

        if (r.getenv)
        {
            classe = "CACHE";
        }
        else if (!r.lit)
        {
            classe = "FANTOME";
        }
        else if (!r.pose)
        {
            classe = "CONSTANTE";
        }
        else
        {
            classe = "MENU";
            ++menus;
        }

        std::cout << nom << " " << classe << "\n";
    }

    std::cout << "MENU " << menus << " SUR " << ordre.size() << "\n";
    return 0;
}
