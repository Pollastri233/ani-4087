#include <cmath>
#include <iostream>
#include <string>

void tourner(long long x, long long z, int k, long long& rx, long long& rz)
{
    if (k == 1)
    {
        rx = z;
        rz = -x;
    }
    else if (k == 2)
    {
        rx = -x;
        rz = -z;
    }
    else if (k == 3)
    {
        rx = -z;
        rz = x;
    }
    else
    {
        rx = x;
        rz = z;
    }
}

unsigned long long absolu(long long v)
{
    return static_cast<unsigned long long>(v < 0 ? -v : v);
}

int main()
{
    long long ax = 0;
    long long ay = 0;
    long long az = 0;
    int ak = 0;
    long long ex = 0;
    long long ey = 0;
    long long ez = 0;
    int N = 0;
    std::cin >> ax >> ay >> az >> ak;
    std::cin >> ex >> ey >> ez;
    std::cin >> N;

    for (int i = 1; i <= N; ++i)
    {
        std::string espace;
        long long x = 0;
        long long y = 0;
        long long z = 0;
        int k = 0;
        long long w = 0;
        long long h = 0;
        std::cin >> espace >> x >> y >> z >> k >> w >> h;

        bool stage = (espace == "S");
        long long cx = x;
        long long cy = y;
        long long cz = z;
        int ck = k;

        if (!stage)
        {
            long long rx = 0;
            long long rz = 0;
            tourner(x, z, ak, rx, rz);
            cx = ax + rx;
            cy = ay + y;
            cz = az + rz;
            ck = (ak + k) % 4;
        }

        std::cout << "PANNEAU " << i << " " << (stage ? "STAGE" : "LOCAL") << "\n";

        long long coinX[4] = {-w / 2, w / 2, w / 2, -w / 2};
        long long coinY[4] = {-h / 2, -h / 2, h / 2, h / 2};

        for (int c = 0; c < 4; ++c)
        {
            long long rx = 0;
            long long rz = 0;
            tourner(coinX[c], 0, ck, rx, rz);
            std::cout << cx + rx << " " << cy + coinY[c] << " " << cz + rz << "\n";
        }

        unsigned long long ux = absolu(cx - ex);
        unsigned long long uy = absolu(cy - ey);
        unsigned long long uz = absolu(cz - ez);
        unsigned long long s = ux * ux + uy * uy + uz * uz;

        unsigned long long r = static_cast<unsigned long long>(std::sqrt(static_cast<long double>(s)));
        while (r * r > s)
        {
            --r;
        }
        while ((r + 1) * (r + 1) <= s)
        {
            ++r;
        }
        if (s > r * r + r)
        {
            ++r;
        }

        std::cout << "DISTANCE " << r << "\n";
    }

    std::cout << "PANNEAUX " << N << "\n";
    return 0;
}