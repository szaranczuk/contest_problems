#include <iostream>
#include <vector>

int N;

std::vector<int> delta_y = {1, -1, 0, 0};
std::vector<int> delta_x = {0, 0, 1, -1};

std::vector<std::vector<char>> gameboard;

std::vector<std::vector<bool>> isFieldVisited;

void DFS(int y, int x)
{
    if (y < 0 || y >= N)
        return;
    if (x < 0 || x >= N)
        return;
    if (gameboard[y][x] == '.')
        return;
    if (isFieldVisited[y][x])
        return;
    isFieldVisited[y][x] = true;
    for (int i = 0; i < delta_y.size(); i++)
    {
        DFS(y + delta_y[i], x + delta_x[i]);
    }
}

int findResult()
{
    int result = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (gameboard[i][j] == 'x' && !isFieldVisited[i][j])
            {
                result++;
                DFS(i, j);
            }
        }
    }
    return result;
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        scanf("%d", &N);
        gameboard.resize(N);
        isFieldVisited.resize(N);
        for (int i = 0; i < N; i++)
        {
            gameboard[i].resize(N);
            isFieldVisited[i].resize(N);
            scanf("\n");
            for (int j = 0; j < N; j++)
            {
                isFieldVisited[i][j] = false;
                char field;
                scanf("%c", &field);
                gameboard[i][j] = field;
            }
        }
        int result = findResult();
        printf("Case %d: %d\n", i + 1, result);
    }
}