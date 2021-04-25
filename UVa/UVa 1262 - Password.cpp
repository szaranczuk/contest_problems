#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const int PASSWD_SIZE = 5;


void backtrack(int p_index, int& counter, int K, bool& isSolved, std::string result, const std::vector<std::vector<char>>& grid)
{
    if (isSolved)
        return;
    if (p_index + 1 == PASSWD_SIZE)
    {
        counter++;
        if (counter == K)
        {
            isSolved = true;
            printf("%s\n", result.c_str());
        }
        return;
    }
    for (int i = 0; i < grid[p_index + 1].size(); i++)
    {
        result.push_back(grid[p_index + 1][i]);
        backtrack(p_index + 1, counter, K, isSolved, result, grid);
        result.erase(result.end() - 1);
    }
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int K;
        scanf("%d", &K);
        std::vector<std::vector<char>> grid1;
        grid1.resize(PASSWD_SIZE);
        for (int i = 0; i < 6; i++)
        {
            scanf("\n");
            for (int j = 0; j < PASSWD_SIZE; j++)
            {
                char password_char;
                scanf("%c", &password_char);
                //printf("%c", password_char);
                grid1[j].push_back(password_char);
            }
        }
        for (auto it = grid1.begin(); it != grid1.end(); it++)
            std::sort(it->begin(), it->end());

        std::vector<std::vector<char>> grid2;
        grid2.resize(PASSWD_SIZE);
        for (int i = 0; i < 6; i++)
        {
            scanf("\n");
            for (int j = 0; j < PASSWD_SIZE; j++)
            {
                char password_char;
                scanf("%c", &password_char);
                grid2[j].push_back(password_char);
            }
        }
        for (auto it = grid2.begin(); it != grid2.end(); it++)
            std::sort(it->begin(), it->end());

        //intersection of two grids
        std::vector<std::vector<char>> result_grid;
        int possible_combinations = 1;
        for (int i = 0; i < PASSWD_SIZE; i++)
        {
            std::vector<char> result_column;
            for (int j = 0; j < 6; j++)
            {
                //std::cout << std::binary_search(grid2[i].begin(), grid2[i].end(), grid1[i][j]);
                if ((!std::binary_search(result_column.begin(), result_column.end(), grid1[i][j])) && std::binary_search(grid2[i].begin(), grid2[i].end(), grid1[i][j]))
                    result_column.push_back(grid1[i][j]);
            }
            possible_combinations *= result_column.size();
            result_grid.push_back(result_column);
        }
        if (possible_combinations < K)
            printf("NO\n");
        else
        {
            bool isSolved = false;
            int counter = 0;
            for (char passwd_char : result_grid[0])
            {
                std::string result;
                result.push_back(passwd_char);
                backtrack(0, counter, K, isSolved, result, result_grid);
            }
        }
    }
    return 0;
}
