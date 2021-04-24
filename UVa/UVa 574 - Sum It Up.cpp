#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

int main()
{
    int t, n;
    scanf("%d %d", &t, &n);
    while (t != 0 && n != 0)
    {
        std::vector<std::string> results;
        printf("Sums of %d:\n", t);
        std::vector<int> list_of_numbers;
        for (int i = 0; i < n; i++)
        {
            int number;
            scanf("%d", &number);
            list_of_numbers.push_back(number);
        }
        std::sort(list_of_numbers.begin(), list_of_numbers.end());
        bool hasSum = false;
        for (unsigned bitmask = (1 << n) - 1; bitmask > 0; bitmask--)
        {
            int sum = 0;
            for (int i = 0; i < n; i++)
            {
                if (bitmask & (1 << i))
                    sum += list_of_numbers[i];
            }
            if (sum == t)
            {
                std::string result;
                hasSum = true;
                bool isBitFirst = true;
                for (int i = n - 1; i >= 0; i--)
                {
                    if (bitmask & (1 << i))
                    {
                        if (isBitFirst)
                        {
                            result += std::to_string(list_of_numbers[i]);
                            isBitFirst = false;
                        }
                        else
                        {
                            result += "+" + std::to_string(list_of_numbers[i]);
                        }
                    }
                }
                bool thisResultsWasObtainedBefore = false;
                for (auto prev_result : results) //poor anti-repetition implementation, I belive it can be done better
                {
                    if (prev_result == result)
                    {
                        thisResultsWasObtainedBefore = true;
                        break;
                    }
                }
                if (!thisResultsWasObtainedBefore)
                {
                    printf("%s\n", result.c_str());
                    results.push_back(result);
                }
            }
        }
        if (!hasSum)
            printf("NONE\n");
        scanf("%d %d", &t, &n);
    }
    return 0;
}
