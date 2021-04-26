#include <iostream>
#include <cmath>

const double EPSILON = 0.000000001;
const double LN_BASE = 2.718281828;

int main()
{
    int p, q, r, s, t, u;
    while (scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) == 6)
    {
        double high = 1.0;
        double low = 0.0;
        double mid = (high + low) / 2.0;
        for (int i = 0; i < 40; i++) //hence we count up to 9 decimal places, and lg((1 - 0) / 10^-9) = lg(10^9) = 30
        {
            double expression = p * std::pow(LN_BASE, -mid) + q * std::sin(mid) + r * std::cos(mid) + s * std::tan(mid) + t * mid * mid + u;
            if (expression < EPSILON && expression > -EPSILON)
            {
                printf("%.4f\n", mid);
                goto solution_found;
            }
            else if (expression > EPSILON)
            {
                low = mid;
                mid = (low + high) / 2.0;
            }
            else
            {
                high = mid;
                mid = (low + high) / 2.0;
            }
        }
        printf("No solution\n");
        solution_found:
            continue;
    }
    return 0;
}
