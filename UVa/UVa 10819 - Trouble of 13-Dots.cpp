//this runs in 0.21-0.23s in UVa OJ and I have no idea how to optimize it more (best is less than 0.01)

#include <iostream>


const int MAX_N = 101;
const int MAX_M = 10201;
const int MAX_INT = 1000000001;

int prices[MAX_N];
int favours[MAX_N];
int memotable[MAX_N][MAX_M];
int n, m;

int findResult(int index, int money_left)
{
    if (money_left < -200)
        return -MAX_INT;
    if (m < 1800 && money_left < 0)
        return -MAX_INT;
    if (index == n || money_left == -200)
    {
        if (m - money_left > 2000)
            money_left += 200;
        if (money_left < 0)
            return -MAX_INT;
        return 0;
    }
    if (memotable[index][money_left + 200] != -1)
    {
        return memotable[index][money_left + 200];
    }
    int result;
    result = std::max(findResult(index + 1, money_left), findResult(index + 1, money_left - prices[index]) + favours[index]);
    memotable[index][money_left + 200] = result;
    return result;
}

int main()
{
    while (scanf("%d %d", &m, &n) == 2)
    {
        for (int i = 0; i < n; i++)
        {
            int price, favour;
            scanf("%d %d", &price, &favour);
            prices[i] = price;
            favours[i] = favour;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= m + 200; j++)
            {
                memotable[i][j] = -1;
            }
        }
        printf("%d\n", findResult(0, m));
    }
    return 0;
}