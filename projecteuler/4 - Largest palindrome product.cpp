#include <bits/stdc++.h>

using namespace std;

bool isPalindrome(string& x)
{
    for (int i = 0; i < (x.size() + 1) / 2; i++)
    {
        if (x[i] != x[x.size() - i - 1]) return false;
    }
    return true;
}

int main()
{
    int result = -1;
    for (int i = 100; i < 1000; i++)
    {
        for (int j = 100; j < 1000; j++)
        {
            int prod = i * j;
            stringstream ss;
            ss << prod;
            string prod_str = ss.str();
            if (isPalindrome(prod_str)) result = max(prod, result);
        }
    }
    cout << result << '\n';
}