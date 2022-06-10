#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll n = 100;
    ll sum = 0ll;
    ll square_sum = 0ll;
    for (ll i = 1; i <= n; i++)
    {
        square_sum += i * i;
        sum += i;
    }
    sum *= sum;
    cout << sum - square_sum << '\n';
}