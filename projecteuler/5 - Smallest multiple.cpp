#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll res = 1;
    for (ll i = 2; i <= 20; i++)
    {
        res = res * i / __gcd(res, i);
    }
    cout << res << '\n';
}