#include <bits/stdc++.h>

using namespace std;

int main()
{
    for (int i = 1; i <= 1000; i++)
    {
        for (int j = 1; j <= 1000 - i; j++)
        {
            int c = 1000 - i - j;
            if (i * i + j * j == c * c)
            {
                cout << (i * j * c) << '\n';
                return 0;
            }
        }
    }
}