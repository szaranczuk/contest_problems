#include <iostream>
#include <vector>

int main()
{
    int test_cases;
    std::cin >> test_cases;
    for (int i = 0; i < test_cases; i++)
    {
        int n, p;
        std::cin >> n >> p;
        std::vector<int> bars;
        bars.reserve(p);
        for (int i = 0; i < p; i++)
        {
            int bar;
            std::cin >> bar;
            bars.push_back(bar);
        }
        bool isPossible = false;
        for (int i = 0; i < (1 << p); i++)
        {
            int bitmask_combination = i;
            int index_of_bit = 0;
            int length_of_combination = 0;
            while (bitmask_combination > 0)
            {
                if (bitmask_combination & 1)
                {
                    length_of_combination += bars[index_of_bit];
                }
                bitmask_combination = bitmask_combination >> 1;
                index_of_bit++;
            }
            if (length_of_combination == n)
            {
                isPossible = true;
                break;
            }
        }
        if (isPossible)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }
    return 0;
}
