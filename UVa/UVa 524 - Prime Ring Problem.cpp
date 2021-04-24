#include <iostream>
#include <vector>
#include <set>

int n;
int wasNumberBitmask;
std::vector<int> cycle;

const std::set<int> prime_numbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline bool isPrime(int number) {return prime_numbers.find(number) != prime_numbers.end();}

void backtrack(int index, std::vector<std::vector<int>>& results)
{
    if (index == n)
    {
        if (isPrime(cycle[index - 1] + cycle[0]))
        {
            results.push_back(cycle);
        }
        else
        {
            return;
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (!(wasNumberBitmask & 1 << (i - 1)) && isPrime(cycle[index - 1] + i))
        {
            cycle[index] = i;
            wasNumberBitmask ^= 1 << (i - 1);
            backtrack(index + 1, results);
            wasNumberBitmask ^= 1 << (i - 1);
        }
    }
}


int main()
{
    int test_case_enumerator = 1;
    while (scanf("%d", &n) == 1)
    {
        if (test_case_enumerator != 1)
            printf("\n");
        std::vector<std::vector<int>> results;
        cycle.resize(n);
        wasNumberBitmask = 1;
        cycle[0] = 1;
        backtrack(1, results);
        printf("Case %d:\n", test_case_enumerator);
        test_case_enumerator++;
        for (auto cycle : results)
        {
            for (int i = 0; i < n - 1; i++)
                printf("%d ", cycle[i]);
            printf("%d\n", cycle[n - 1]);
        }
    }
    return 0;
}
