#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll input;
    cin >> input;
    ll result = -1;
    for (ll i = 2; i * i <= input; i++)
    {
        while (input % i == 0)
        {
            result = i;
            input /= i;
        }
    }
    cout << max(result, input) << '\n';
}