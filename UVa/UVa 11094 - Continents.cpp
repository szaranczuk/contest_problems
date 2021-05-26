#include <iostream>
#include <vector>

std::vector<int> delta_y = {1, -1, 0, 0};
std::vector<int> delta_x = {0, 0, 1, -1};

int M, N;

enum field_state
{
    UNVISITED,
    VISITED
};

std::vector<std::vector<char>> world_map;
std::vector<std::vector<field_state>> fields_states;

char land_char;

int DFS(int y, int x)
{
    if (y < 0 || y >= M)
        return 0;
    if (x == -1)
        x = N - 1;
    if (x < 0 || x > N)
        return 0;
    if (x == N)
        x = 0;
    if (world_map[y][x] != land_char || fields_states[y][x] == VISITED)
        return 0;
    int result = 1;
    fields_states[y][x] = VISITED;
    for (int i = 0; i < delta_y.size(); i++)
    {
        result += DFS(y + delta_y[i], x + delta_x[i]);
    }
    return result;
}

int findResult()
{
    int result = 0;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result = std::max(result, DFS(i, j));
        }
    }
    return result;
}

int main()
{
    while(scanf("%d %d", &M, &N) == 2)
    {
        world_map.resize(M);
        fields_states.resize(M);
        for (int i = 0; i < M; i++)
        {
            world_map[i].resize(N);
            fields_states[i].resize(N);
            scanf("\n");
            for (int j = 0; j < N; j++)
            {
                fields_states[i][j] = UNVISITED;
                char field;
                scanf("%c", &field);
                world_map[i][j] = field;
            }
        }
        int Y, X;
        scanf("%d %d", &Y, &X);
        land_char = world_map[Y][X];
        DFS(Y, X);
        int result = findResult();
        printf("%d\n", result);
    }
}