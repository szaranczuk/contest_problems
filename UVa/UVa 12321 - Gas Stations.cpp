#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main()
{
    int L, G;
    scanf("%d %d", &L, &G);
    while (L != 0 || G != 0)
    {
        std::vector<std::pair<int, int>> gas_stations;
        for (int i = 0; i < G; i++)
        {
            int x, r;
            scanf("%d %d", &x, &r);
            gas_stations.push_back({x, r});
        }
        std::sort(gas_stations.begin(), gas_stations.end(), [L](std::pair<int, int> a, std::pair<int, int> b)
                  {
                      if (std::max(a.first - a.second, 0) == std::max(b.first - b.second, 0))
                        return (std::min(a.first + a.second, L) > std::min(b.first + b.second, L));
                      else
                        return std::max(a.first - a.second, 0) < std::max(b.first - b.second, 0);
                  });
        int max_right = 0;
        int potential_max_right = 0;
        int counter = 0;
        for (auto station : gas_stations)
        {
            if (station.first - station.second > potential_max_right)
            {
                printf("-1\n");
                goto road_not_covered;
            }
            if (station.first - station.second > max_right)
            {
                max_right = potential_max_right;
                counter++;
            }
            if (station.first + station.second > potential_max_right)
            {
                potential_max_right = station.first + station.second;
                if (potential_max_right >= L)
                {
                    counter++;
                    break;
                }
            }
        }
        if (potential_max_right < L)
        {
            printf("-1\n");
            goto road_not_covered;
        }
        printf("%d\n", G - counter);
        road_not_covered:
            scanf("%d %d", &L, &G);
    }
    return 0;
}
