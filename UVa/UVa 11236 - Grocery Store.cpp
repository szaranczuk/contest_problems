#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

int main()
{
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(2);
    for (long long a = 1; a < 2000; a++)
    {
        for (long long b = a; b < 2000 - a; b++)
        {
            for (long long c = b; c < 2000 - a - b; c++)
            {
                long long sum = a + b + c;
                long long product = a * b * c;
                if (product == 1000000)
                {
                    continue;
                }
                if ((sum * 1000000) % (product - 1000000) != 0)
                    continue;
                long long d = (sum * 1000000) / (product - 1000000);
                if (d > 0 && d >= c && sum + d <= 2000)
                {
                    std::cout << a / 100.0 << " " << b / 100.0 << " " << c / 100.0 << " " << d / 100.0 << '\n';
                }
            }
        }
    }
    return 0;
}
