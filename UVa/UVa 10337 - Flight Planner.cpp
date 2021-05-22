#include <iostream>
#include <vector>

std::vector<std::vector<int>> memotable(10);

std::vector<std::vector<int>> windstrengths(10);

int X;

const int MAX_INT = 1000000001;

int findResult(int altitude, int distance)
{
    if (altitude > 9 || altitude < 0)
    {
        return MAX_INT;
    }
    if (distance == X)
    {
        if (altitude == 0)
            return 0;
        return MAX_INT;
    }
    if (memotable[altitude][distance] != -1)
    {
        return memotable[altitude][distance];
    }
    int windstrength = windstrengths[altitude][distance];
    int result1 = findResult(altitude, distance + 1) + 30 - windstrength;
    int result2 = findResult(altitude + 1, distance + 1) + 60 - windstrength;
    int result3 = findResult(altitude - 1, distance + 1) + 20 - windstrength;
    int result = std::min(result1, std::min(result2,  result3));
    memotable[altitude][distance] = result;
    return result;
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        scanf("%d", &X);
        X /= 100;
        for (int i = 9; i >= 0; i--)
        {
            memotable[i].resize(X);
            windstrengths[i].resize(X);
            for (int j = 0; j < X; j++)
            {
                memotable[i][j] = -1;
                int windstrength;
                scanf("%d", &windstrength);
                windstrengths[i][j] = windstrength;
            }
        }
        int result = findResult(0, 0);
        printf("%d\n\n", result);
    }
}