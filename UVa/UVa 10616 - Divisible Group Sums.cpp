#include <iostream>
#include <vector>
#include <cmath>

int findResult(int index, int M, int D, int sum, std::vector<int> &numbers, std::vector<std::vector<std::vector<int>>> &memotable)
{
    // D - 1 is shift for negative numbers
    if (index != numbers.size() && memotable[index][M][sum + D - 1] != -1)
    {
        return memotable[index][M][sum + D - 1];
    }
    if (M == 0)
    {
        if (sum == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (index == numbers.size())
    {
        return 0;
    }
    int result = 0;
    //result is sum of all valid groups where we insert number with actual index, and all valid groups where we not insert this number
    result += findResult(index + 1, M, D, sum, numbers, memotable);
    result += findResult(index + 1, M - 1, D, (sum + numbers[index]) % D, numbers, memotable);
    memotable[index][M][sum + D - 1] = result;
    return result;
}

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    int set_counter = 1;
    while (N != 0 || Q != 0)
    {
        printf("SET %d:\n", set_counter);
        set_counter++;
        std::vector<int> numbers;
        numbers.reserve(N);
        for (int i = 0; i < N; i++)
        {
            int number;
            scanf("%d", &number);
            numbers.push_back(number);
        }
        for (int i = 0; i < Q; i++)
        {
            int D, M;
            scanf("%d %d", &D, &M);
            int result = 0;
            std::vector<std::vector<std::vector<int>>> memotable;
            for (int i = 0; i < numbers.size(); i++)
            {
                memotable.push_back({});
                for (int j = 0; j <= M; j++)
                {
                    memotable[i].push_back({});
                    for (int k = 0; k < 2 * D - 1; k++) //shift for negative numbers, see findResult implementation
                    {
                        memotable[i][j].push_back(-1);
                    }
                }
            }
            result = findResult(0, M, D, 0, numbers, memotable);
            printf("QUERY %d: %d\n", i + 1, result);
        }
        scanf("%d %d", &N, &Q);
    }
}