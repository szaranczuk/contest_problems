#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n = 1000001;
    int cnt = 10001;
    vector<bool> isPrime(n + 1, true);
    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i + i; j <= n; j += i) isPrime[j] = false;
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i]) cnt--;
        if (cnt == 0)
        {
            cout << i << '\n';
            return 0;
        }
    }
}