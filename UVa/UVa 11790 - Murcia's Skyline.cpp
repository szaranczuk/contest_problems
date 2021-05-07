#include <iostream>
#include <vector>
#include <algorithm>

int findLIS(int index, std::vector<int>& heights, std::vector<int>& widths, std::vector<int>& memotable)
{
    if (memotable[index] != -1)
        return memotable[index];
    if (index == 0)
    {
        memotable[0] = widths[0];
        return memotable[0];
    }
    int LIS = widths[index];
    for (int i = 0; i < index; i++)
    {
        if (heights[i] < heights[index])
        {
            LIS = std::max(LIS, findLIS(i, heights, widths, memotable) + widths[index]);
        }
    }
    memotable[index] = LIS;
    return LIS;
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int n;
        scanf("%d", &n);
        std::vector<int> skyline;
        std::vector<int> negative_skyline;
        std::vector<int> memotable;
        std::vector<int> negative_memotable;
        skyline.reserve(n);
        negative_skyline.reserve(n); //LIS of negated set will be LDS of that set
        memotable.reserve(n);
        negative_skyline.reserve(n);
        for (int i = 0; i < n; i++)
        {
            int value;
            scanf("%d", &value);
            skyline.push_back(value);
            negative_skyline.push_back(-value);
            memotable.push_back(-1);
            negative_memotable.push_back(-1);
        }
        std::vector<int> widths;
        widths.reserve(n);
        for (int i = 0; i < n; i++)
        {
            int value;
            scanf("%d", &value);
            widths.push_back(value);
        }
        int LIS_size = 0;
        int LDS_size = 0;
        for (int i = 0; i < n; i++)
        {
            LIS_size = std::max(LIS_size, findLIS(i, skyline, widths, memotable));
            LDS_size = std::max(LDS_size, findLIS(i, negative_skyline, widths, negative_memotable));
        }
        if (LDS_size > LIS_size)
            printf("Case %d. Decreasing (%d). Increasing (%d).\n", i + 1, LDS_size, LIS_size);
        else
            printf("Case %d. Increasing (%d). Decreasing (%d).\n", i + 1, LIS_size, LDS_size);
    }
}