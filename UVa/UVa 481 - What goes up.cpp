#include <iostream>
#include <vector> 
#include <algorithm>
#include <stack>

//This was O(n ^ 2) solution, but it recieved TLE
/*int findLongestIncreasingSubsequence(int index, std::vector<int>& numbers, std::vector<std::vector<int>>& memotable)
{
    if (memotable[index].size() != 0)
        return memotable[index].size();
    if (index == 0)
    {
        memotable[0].push_back(numbers[0]);
        return 1;
    }
    int max_LIS_size = 0;
    for (int i = index - 1; i >= 0; i--)
    {
        if (numbers[i] < numbers[index])
        {
            int LIS_size = findLongestIncreasingSubsequence(i, numbers, memotable) + 1;
            if (LIS_size > max_LIS_size)
            {
                memotable[index] = memotable[i];
                max_LIS_size = LIS_size;
            }
        }
    }
    memotable[index].push_back(numbers[index]);
}*/

//this is O(n log k) solution, where n stands for numbers quantity, and k for LIS size
int main()
{
    int number;
    std::vector<int> numbers;
    std::vector<int> LIS;
    while (scanf("%d", &number) == 1)
    {
        numbers.push_back(number);
    }
    LIS.reserve(numbers.size());
    std::vector<std::vector<int>> place_in_original_sequence(numbers.size());
    for (int i = 0; i < numbers.size(); i++)
    {
        auto not_less_than_number_pos = std::lower_bound(LIS.begin(), LIS.end(), numbers[i]);
        if (not_less_than_number_pos == LIS.end())
            LIS.push_back(numbers[i]);
        else
            *not_less_than_number_pos = numbers[i];
        place_in_original_sequence[not_less_than_number_pos - LIS.begin()].push_back(i);
    }
    printf("%d\n-\n", LIS.size());
    std::stack<int> output_stack;
    output_stack.push(LIS[LIS.size() - 1]);
    int previous_place_in_original_sequence = *(place_in_original_sequence[LIS.size() - 1].end() - 1);
    for (int i = LIS.size() - 2; i >= 0; i--)
    {
        for (int j = place_in_original_sequence[i].size() - 1; j >= 0; j--)
        {
            if (place_in_original_sequence[i][j] < previous_place_in_original_sequence)
            {
                previous_place_in_original_sequence = place_in_original_sequence[i][j];
                output_stack.push(numbers[place_in_original_sequence[i][j]]);
                break;
            }
        }
    }
    while (!output_stack.empty())
    {
        printf("%d\n", output_stack.top());
        output_stack.pop();
    }
}