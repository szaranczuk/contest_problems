#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n = 2e6;
    vector<bool> isPrime(n, true);
    long long result = 0ll;
    for (int i = 2; i < n; i++)
    {
        if (isPrime[i])
        {
            result += i;
            for (int j = 2 * i; j < n; j += i) isPrime[j] = false;
        }
    }
    cout << result << '\n';
}