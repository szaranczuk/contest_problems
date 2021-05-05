#include <iostream>

const int MAX_DIM = 21;

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int A, B, C;
        scanf("%d %d %d", &A, &B, &C);
        long long garbage_heap[MAX_DIM][MAX_DIM][MAX_DIM];
        long long sum[MAX_DIM][MAX_DIM][MAX_DIM];
        for (int i = 0; i < A; i++)
        {
            for (int j = 0; j < B; j++)
            {
                for (int k = 0; k < C; k++)
                {
                    long long value;
                    scanf("%lld", &value);
                    garbage_heap[i][j][k] = value;
                    sum[i][j][k] = value;
                    if (i - 1 >= 0)
                        sum[i][j][k] += sum[i - 1][j][k];
                    if (j - 1 >= 0)
                        sum[i][j][k] += sum[i][j - 1][k];
                    if (k - 1 >= 0)
                        sum[i][j][k] += sum[i][j][k - 1];
                    if (i - 1 >= 0 && j - 1 >= 0)
                        sum[i][j][k] -= sum[i - 1][j - 1][k];
                    if (i - 1 >= 0 && k - 1 >= 0)
                        sum[i][j][k] -= sum[i - 1][j][k - 1];
                    if (j - 1 >= 0 && k - 1 >= 0)
                        sum[i][j][k] -= sum[i][j - 1][k - 1];
                    if (i - 1 >= 0 && j - 1 >= 0 && k - 1 >= 0)
                        sum[i][j][k] += sum[i - 1][j - 1][k - 1];
                }
            }
        }
        long long answer = sum[A - 1][B - 1][C - 1];
        //std::cout << answer;
        for (int i = 0; i < A; i++)
        {
            for (int j = 0; j < B; j++)
            {
                for (int i2 = i; i2 < A; i2++)
                {
                    for (int j2 = j; j2 < B; j2++)
                    {
                        long long local_answer = 0;
                        for (int k = 0; k < C; k++)
                        {
                            local_answer += sum[i2][j2][k];
                            if (k - 1 >= 0)
                                local_answer -= sum[i2][j2][k - 1];
                            if (i - 1 >= 0)
                            {
                                local_answer -= sum[i - 1][j2][k];
                                if (k - 1 >= 0)
                                    local_answer += sum[i - 1][j2][k - 1];
                            }
                            if (j - 1 >= 0)
                            {
                                local_answer -= sum[i2][j - 1][k];
                                if (k - 1 >= 0)
                                    local_answer += sum[i2][j - 1][k - 1];
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)
                            {
                                local_answer += sum[i - 1][j - 1][k];
                                if (k - 1 >= 0)
                                    local_answer -= sum[i - 1][j - 1][k - 1];
                            }
                            answer = std::max(answer, local_answer);
                            if (local_answer < 0)
                                local_answer = 0;
                        }
                    }
                }
            }
        }
        printf("%lld\n", answer);
        if (i != test_cases - 1)
            printf("\n");
    }
}