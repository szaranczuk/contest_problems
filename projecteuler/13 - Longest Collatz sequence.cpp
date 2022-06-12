#include <bits/stdc++.h>

using namespace std;

vector<int> memo(1e7, -1);

int dp(long long n)
{
    if (n >= 1e7) return 1 + dp(n % 2 == 0 ? n / 2 : 3 * n + 1);
    if (memo[n] != -1) return memo[n];
    return memo[n] = 1 + dp(n % 2 == 0 ? n / 2 : 3 * n + 1);
}

int main()
{
    memo[1] = 1;
    int maximum_val = 1;
    int result = 1;
    for (int i = 2; i < 1e6; i++)
    {
        int local_res = dp(i);
        if (local_res > maximum_val)
        {
            maximum_val = local_res;
            result = i;
        }
    }
    cout << result << '\n';
}