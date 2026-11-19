#include <iostream>

struct Pose
{
    long long x;
    long long y;
    long long z;
    int k;
};

Pose composer(const Pose& a, const Pose& p)
{
    long long rx = p.x;
    long long rz = p.z;

    if (a.k == 1)
    {
        rx = p.z;
        rz = -p.x;
    }
    else if (a.k == 2)
    {
        rx = -p.x;
        rz = -p.z;
    }
    else if (a.k == 3)
    {
        rx = -p.z;
        rz = p.x;
    }

    Pose r;
    r.x = a.x + rx;
    r.y = a.y + p.y;
    r.z = a.z + rz;
    r.k = (a.k + p.k) % 4;
    return r;
}

int main()
{
    Pose ancre = {0, 0, 0, 0};
    int N = 0;
    std::cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k;
    std::cin >> N;

    int justes = 0;
    int fausses = 0;

    for (int i = 1; i <= N; ++i)
    {
        char D = 'S';
        char C = 'S';
        Pose p = {0, 0, 0, 0};
        std::cin >> D >> C >> p.x >> p.y >> p.z >> p.k;

        Pose vraie = (D == 'S') ? p : composer(ancre, p);
        Pose crue = (C == 'S') ? p : composer(ancre, p);

        long long dx = crue.x - vraie.x;
        long long dy = crue.y - vraie.y;
        long long dz = crue.z - vraie.z;
        int dk = (crue.k - vraie.k + 4) % 4;

        std::cout << i << " CRU " << crue.x << " " << crue.y << " "
                  << crue.z << " " << crue.k << "\n";
        std::cout << i << " ECART " << dx << " " << dy << " "
                  << dz << " " << dk << "\n";

        if (dx == 0 && dy == 0 && dz == 0 && dk == 0)
        {
            ++justes;
        }
        else
        {
            ++fausses;
        }
    }

    std::cout << "JUSTES " << justes << "\n";
    std::cout << "FAUSSES " << fausses << "\n";
    return 0;
}