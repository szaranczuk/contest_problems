#include <iostream>
#include <vector>

std::vector<std::vector<long long>> memotable;

long long binomial(int n, int k)
{
    if (k == 0 || k == n)
    {
        return 1;
    }
    if (memotable[n][k] != -1)
    {
        return memotable[n][k];
    }
    long long result = (binomial(n - 1, k - 1) + binomial(n - 1, k)) % 1000000;
    memotable[n][k] = result;
    return result;
}

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);
    while (N != 0 || K != 0)
    {
        memotable.resize(N + K);
        for (int i = 0; i < N + K; i++)
        {
            memotable[i].resize(K);
            for (int j = 0; j < K; j++)
            {
                memotable[i][j] = -1;
            }
        }
        long long result = binomial(N + K - 1, K - 1);
        printf("%lld\n", result);
        scanf("%d %d", &N, &K);
    }
}