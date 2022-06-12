#include <bits/stdc++.h>

using namespace std;

int main()
{
    for (int i = 1; i < 1e5; i++)
    {
        int divisors = 1;
        int number1 = i;
        int number2 = i + 1;
        if (number1 % 2 == 0) number1 /= 2;
        else number2 /= 2;
        for (int j = 2; j * j <= number1; j++)
        {
            int exponent = 1;
            while (number1 % j == 0)
            {
                exponent++;
                number1 /= j;
            }
            divisors *= exponent;
        }
        for (int j = 2; j * j <= number2; j++)
        {
            int exponent = 1;
            while (number2 % j == 0)
            {
                exponent++;
                number2 /= j;
            }
            divisors *= exponent;
        }
        if (number1 > 1) divisors *= 2;
        if (number2 > 1) divisors *= 2;
        if (divisors > 500)
        {
            cout << i * (i + 1) / 2 << '\n';
            return 0;
        }
    }
}