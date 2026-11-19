#include <cmath>
#include <iostream>

unsigned long long absolu(long long v)
{
    return static_cast<unsigned long long>(v < 0 ? -v : v);
}

int main()
{
    long long N = 0;
    long long d = 0;
    std::cin >> N >> d;

    long long sommePosition = 0;
    long long sommeAngle = 0;

    for (long long t = 1; t <= N; ++t)
    {
        long long x1 = 0;
        long long z1 = 0;
        long long a1 = 0;
        long long x2 = 0;
        long long z2 = 0;
        long long a2 = 0;
        std::cin >> x1 >> z1 >> a1 >> x2 >> z2 >> a2;

        unsigned long long ux = absolu(x2 - x1);
        unsigned long long uz = absolu(z2 - z1);
        unsigned long long s = ux * ux + uz * uz;

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

        long long angle = static_cast<long long>(absolu(a2 - a1));

        std::cout << t << " POSITION " << r << " ANGLE " << angle << "\n";
        sommePosition += static_cast<long long>(r);
        sommeAngle += angle;
    }

    if (N <= 0 || d <= 0)
    {
        std::cout << "AUCUNE\n";
        return 0;
    }

    std::cout << "MOYENNE POSITION " << sommePosition / N << "\n";
    std::cout << "MOYENNE ANGLE " << sommeAngle / N << "\n";
    std::cout << "VITESSE " << sommeAngle / (N * d) << "\n";
    return 0;
}
