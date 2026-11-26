#include <iostream>

int main()
{
    long long hz = 0;
    long long ipd = 0;
    int n = 0;
    std::cin >> hz >> ipd >> n;

    long long x = 0;
    long long y = 0;
    long long z = 0;
    long long k0 = 0;
    long long dk = 0;
    long long vx = 0;
    std::cin >> x >> y >> z >> k0 >> dk >> vx;

    if (hz <= 1)
    {
        hz = 72;
    }
    const long long p = 1000000000LL / hz;
    const long long demi = ipd / 2;

    const long long droiteX[4] = {1, 0, -1, 0};
    const long long droiteZ[4] = {0, -1, 0, 1};

    std::cout << "PERIODE " << p << "\n";

    for (int t = 1; t <= n; ++t)
    {
        const long long pas = t - 1;
        const long long lacet = ((k0 + pas * dk) % 4 + 4) % 4;
        const long long tx = x + pas * vx;

        const long long gx = tx - demi * droiteX[lacet];
        const long long gz = z - demi * droiteZ[lacet];
        const long long dx = tx + demi * droiteX[lacet];
        const long long dz = z + demi * droiteZ[lacet];

        std::cout << t << " G " << gx << " " << y << " " << gz
                  << " D " << dx << " " << y << " " << dz
                  << " I " << t * p << "\n";
    }

    return 0;
}
