#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int different_types;
        scanf("%d", &different_types);
        if (different_types == 1)
        {
            printf("1\n");
            continue;
        }
        std::vector<int> coins;
        for (int i = 0; i < different_types; i++)
        {
            int coin;
            scanf("%d", &coin);
            coins.push_back(coin);
        }
        int counter = 2;
        int sum = 1;
        for (int i = 1; i < coins.size() - 1; i++)
        {
            if (sum + coins[i] < coins[i + 1])
            {
                counter++;
                sum += coins[i];
            }
        }
        printf("%d\n", counter);
    }
}
