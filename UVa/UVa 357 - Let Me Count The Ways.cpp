#include <iostream>
#include <vector>

const std::vector<int> nominals = {50, 25, 10, 5, 1};
const int NOMINALS_SIZE = nominals.size();
std::vector<std::vector<long long>> memotable(NOMINALS_SIZE);

long long findResult(int index, int sum)
{
    if (index == NOMINALS_SIZE)
        return 0;
    if (sum < 0)
        return 0;
    if (sum == 0)
    {
        return 1;
    }
    if (memotable[index][sum] != -1)
    {
        return memotable[index][sum];
    }
    long long result = findResult(index, sum - nominals[index]) + findResult(index + 1, sum);
    memotable[index][sum] = result;
    return result;
}

int main()
{
    int value_to_find;
    while (scanf("%d", &value_to_find) == 1)
    {
        for (int i = 0; i < NOMINALS_SIZE; i++)
        {
            memotable[i].resize(value_to_find + 1);
            for (int j = 0; j < value_to_find + 1; j++)
            {
                memotable[i][j] = -1;
            }
        }
        long long result = findResult(0, value_to_find);
        if (result == 1)
        {
            printf("There is only 1 way to produce %d cents change.\n", value_to_find);
        }
        else
        {
            printf("There are %lld ways to produce %d cents change.\n", result, value_to_find);
        }
    }
}