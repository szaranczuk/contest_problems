#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int n = 1000;
    ll local_res = 1ll;
    ll global_res = 0ll;
    queue<ll> numbers;
    for (int i = 0; i < n; i++)
    {
        char input;
        cin >> input;
        if (input == '0')
        {
            numbers = queue<ll>();
            local_res = 1ll;
            continue;
        }
        numbers.push(input - '0');
        local_res *= (ll) (input - '0');
        if (numbers.size() > 13)
        {
            local_res /= numbers.front();
            numbers.pop();
        }
        if (numbers.size() == 13) global_res = max(global_res, local_res);
    }
    cout << global_res << '\n';
}