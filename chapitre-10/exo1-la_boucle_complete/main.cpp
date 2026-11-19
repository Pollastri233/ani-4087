#include <iostream>
#include <string>

int main()
{
    int T = 0;
    std::cin >> T;
    int justes = 0;
    int fautives = 0;

    for (int t = 1; t <= T; ++t)
    {
        int n = 0;
        std::cin >> n;

        bool waited = false;
        bool begun = false;
        bool ended = false;
        bool viewed = false;
        bool pris[2] = {false, false};
        std::string code;
        int place = 0;

        for (int i = 1; i <= n; ++i)
        {
            std::string appel;
            std::cin >> appel;
            if (!code.empty())
            {
                continue; // première faute déjà retenue : on ignore la suite
            }

            if (ended)
            {
                code = "APRES_END";
            }
            else if (appel == "WAIT")
            {
                if (begun) code = "WAIT_APRES_BEGIN";
                else waited = true;
            }
            else if (appel == "BEGIN")
            {
                if (begun) code = "DOUBLE_BEGIN";
                else if (!waited) code = "BEGIN_SANS_WAIT";
                else begun = true;
            }
            else if (appel == "VUES")
            {
                if (!waited) code = "VUES_SANS_WAIT";
                else viewed = true;
            }
            else if (appel == "PREND_G" || appel == "PREND_D")
            {
                int oeil = (appel == "PREND_G") ? 0 : 1;
                if (!begun) code = "PREND_SANS_BEGIN";
                else if (!viewed) code = "PREND_SANS_VUES";
                else if (pris[oeil]) code = "DOUBLE_PREND";
                else pris[oeil] = true;
            }
            else if (appel == "LACHE_G" || appel == "LACHE_D")
            {
                int oeil = (appel == "LACHE_G") ? 0 : 1;
                if (!pris[oeil]) code = "LACHE_SANS_PREND";
                else pris[oeil] = false;
            }
            else if (appel == "END")
            {
                if (!begun) code = "END_SANS_BEGIN";
                else if (pris[0] || pris[1]) code = "END_IMAGE_PRISE";
                else ended = true;
            }

            if (!code.empty())
            {
                place = i;
            }
        }

        if (code.empty() && !ended)
        {
            code = "SANS_END";
            place = n + 1;
        }

        if (code.empty())
        {
            std::cout << t << " OK\n";
            ++justes;
        }
        else
        {
            std::cout << t << " FAUTE " << place << " " << code << "\n";
            ++fautives;
        }
    }

    std::cout << "JUSTES " << justes << "\n";
    std::cout << "FAUTIVES " << fautives << "\n";
    return 0;
}