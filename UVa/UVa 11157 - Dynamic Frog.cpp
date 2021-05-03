#include <iostream>
#include <vector>

struct Rock
{
    char type;
    int distance;
    bool is_drowned;
};

int main()
{
    int test_cases;
    scanf("%d\n", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int N, D;
        scanf("%d %d\n", &N, &D);
        std::vector<Rock> rocks;
        rocks.push_back({'B', 0, false});
        for (int i = 0; i < N; i++)
        {
            char type;
            int distance;
            scanf(" %c-%d", &type, &distance);
            rocks.push_back({type, distance, false});
        }
        rocks.push_back({'B', D, false});
        int min_leap = 0;
        int local_min_leap = 0;
        bool prevWasSmall = false;
        for (int i = 1; i < N + 2 ; i++)
        {
            if (rocks[i].is_drowned)
                continue;
            if (rocks[i].type == 'B')
            {
                local_min_leap += rocks[i].distance - rocks[i - 1].distance;
                min_leap = std::max(min_leap, local_min_leap);
                local_min_leap = 0;
            }
            else
            {
                if (prevWasSmall)
                {
                    local_min_leap += rocks[i].distance - rocks[i - 1].distance;
                    prevWasSmall = false;
                }
                else
                {
                    local_min_leap += rocks[i].distance - rocks[i - 1].distance;
                    min_leap = std::max(min_leap, local_min_leap);
                    local_min_leap = 0;
                    prevWasSmall = true;
                    rocks[i].is_drowned = true;
                }
            }
        }
        for (int i = N; i >= 0; i--)
        {
            if (rocks[i].is_drowned)
            {
                local_min_leap += rocks[i + 1].distance - rocks[i].distance;
                continue;
            }
            local_min_leap += rocks[i + 1].distance - rocks[i].distance;
            min_leap = std::max(min_leap, local_min_leap);
            local_min_leap = 0;
        }
        printf("Case %d: %d\n", i + 1, min_leap);
    }
    return 0;
}
