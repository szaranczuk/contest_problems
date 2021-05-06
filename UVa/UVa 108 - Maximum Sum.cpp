#include <iostream>
#include <vector>

int main()
{
    int N;
    scanf("%d", &N);
    std::vector<std::vector<int>> table(N);
    std::vector<std::vector<int>> sum(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int value;
            scanf("%d", &value);
            table[i].push_back(value);
            sum[i].push_back(value);
            if (i - 1 >= 0)
            {
                sum[i][j] += sum[i - 1][j];
            }
            if (j - 1 >= 0)
            {
                sum[i][j] += sum[i][j - 1];
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sum[i][j] -= sum[i - 1][j - 1];
            }
        }
    }
    int result = sum[N - 1][N - 1];
    for (int left = 0; left < N; left++)
    {
        for (int right = left; right < N; right++)
        {
            int local_sum = 0;
            for (int k = 0; k < N; k++)
            {
                local_sum += sum[right][k];
                if (k - 1 >= 0)
                {
                    local_sum -= sum[right][k - 1];
                }
                if (left - 1 >= 0)
                {
                    local_sum -= sum[left - 1][k];
                }
                if (k - 1 >= 0 && left - 1 >= 0)
                {
                    local_sum += sum[left - 1][k - 1];
                }
                result = std::max(local_sum, result);
                if (local_sum < 0)
                    local_sum = 0;
            }
        }
    }
    printf("%d\n", result);
}