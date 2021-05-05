/**************************************************************************************************
 *                        THIS IS NOT A VALID SOLUTION TO UVa 787                                 *
 *      Time and memory complexity is both O(n), so it shouldn't recieve a TLE or MLE             *
 *     The only problem is that integer (long long as well) will overflow in medium case          *
 *   In Java you can just replace int with BigInteger, and I'm almost sure that this will work    *
 *             In C++ you have to write BigInteger implementation for yourself                    *
 **************************************************************************************************/

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>

const int MAX_INT = 1000000001;

int findMaxProduct(int number, std::vector<std::array<int, 2>> &memotable, std::vector<int> &numbers, int type)
{
    if (number == numbers.size())
        return 1;
    if (memotable[number][type] != -MAX_INT)
        return memotable[number][type];
    else
    {
        int positive_res = numbers[number];
        int negative_res = numbers[number];
        positive_res = std::max(positive_res, findMaxProduct(number + 1, memotable, numbers, 0) * numbers[number]);
        positive_res = std::max(positive_res, findMaxProduct(number + 1, memotable, numbers, 1) * numbers[number]);
        negative_res = std::min(negative_res, findMaxProduct(number + 1, memotable, numbers, 1) * numbers[number]);
        memotable[number][0] = positive_res;
        memotable[number][1] = negative_res;
        return memotable[number][type];
    }
}

int main()
{
    int number;
    std::vector<int> numbers;
    while (scanf("%d", &number) == 1)
    {
        if (number == -999999)
        {
            std::vector<std::array<int, 2>> memotable(numbers.size());
            for (int i = 0; i < numbers.size(); i++)
            {
                memotable[i][0] = -MAX_INT;
                memotable[i][1] = -MAX_INT;
            }
            findMaxProduct(0, memotable, numbers, 0);
            int max_product = -MAX_INT;
            for (int i = 0; i < numbers.size(); i++)
            {
                max_product = std::max(max_product, memotable[i][0]);
            }
            printf("%d\n", max_product);
            numbers.erase(numbers.begin(), numbers.end());
        }
        else
            numbers.push_back(number);
    }
    return 0;
}