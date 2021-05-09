//this was one of the most simply-way overcomplicated problems that I have ever done

#include <iostream>
#include <vector>
#include <cmath>

const int MAX_INT = 1000000001;

int N, x, T, K;
int full_tea_price;
int money_minus_tee_price;
std::vector<int> prices;
std::vector<int> favours;
std::vector<std::vector<std::vector<int>>> memotable;

int findResult(int index, int money_left, int ordered_before)
{
    int money_after_serive_charge = money_left - std::ceil(0.1 * static_cast<double>(money_minus_tee_price - money_left + full_tea_price));
    if (money_after_serive_charge < 0)
        return -MAX_INT;
    if (index == 2 * K || ordered_before == 2 * N + 2 || money_after_serive_charge == 0)
    {
        return 0;
    }
    if (memotable[index][money_left][ordered_before] != -1)
        return memotable[index][money_left][ordered_before];
    int result = std::max(findResult(index + 1, money_left, ordered_before), findResult(index + 1, money_left - prices[index], ordered_before + 1) + favours[index]);
    memotable[index][money_left][ordered_before] = result;
    return result;
}

int main()
{
    scanf("%d %d %d %d", &N, &x, &T, &K);
    while (N != 0 || x != 0 || T != 0 || K != 0)
    {
        prices.resize(2 * K);
        favours.resize(2 * K);
        for (int i = 0; i < 2 * K; i += 2)
        {
            int value;
            int favour;
            scanf("%d %d", &value, &favour);
            prices[i] = value;
            prices[i + 1] = value;
            favours[i] = favour;
            favours[i + 1] = favour;
            for (int j = 0; j < N; j++)
            {
                int favour;
                scanf("%d", &favour);
                favours[i] += favour;
                favours[i + 1] += favour;
            }
        }
        memotable.resize(2 * K);
        for (int i = 0; i < 2 * K; i++)
        {
            memotable[i].resize((N + 1) * x + 1);
            for (int j = 0; j <= (N + 1) * x; j++)
            {
                memotable[i][j].resize(2 * (N + 1));
                for (int k = 0; k < 2 * (N + 1); k++)
                {
                    memotable[i][j][k] = -1;
                }
            }
        }
        full_tea_price = (N + 1) * T;
        money_minus_tee_price = (N + 1) * x - full_tea_price;
        double result = static_cast<double>(findResult(0, money_minus_tee_price, 0)) / static_cast<double>(N + 1);
        printf("%.2lf\n", result);
        scanf("%d %d %d %d", &N, &x, &T, &K);
    }
}