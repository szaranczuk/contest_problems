#include <iostream>
#include <string>
#include <vector>

struct pos
{
    int y;
    int x;
};

const std::vector<pos> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

inline void updateDirection(int& direction, int angle)
{
    direction += angle;
    if (direction < 0)
    {
        direction = 3;
    }
    else if (direction > 3)
    {
        direction = 0;
    }
};

int main()
{
    int N, M, S;
    std::cin >> N >> M >> S;
    while (N != 0 || M != 0 || S != 0)
    {
        std::vector<std::vector<char>> arena_map;
        arena_map.resize(N);
        pos current_pos;
        int current_direction;
        for (int i = 0; i < N; i++)
        {
            arena_map[i].resize(M);
            for (int j = 0; j < M; j++)
            {
                char field;
                std::cin >> field;
                if (field == 'N')
                {
                    current_pos = {i, j};
                    current_direction = 0;
                    arena_map[i][j] = '.';
                }
                else if (field == 'S')
                {
                    current_pos = {i, j};
                    current_direction = 2;
                    arena_map[i][j] = '.';
                }
                else if (field == 'L')
                {
                    current_pos = {i, j};
                    current_direction = 1;
                    arena_map[i][j] = '.';
                }
                else if (field == 'O')
                {
                    current_pos = {i, j};
                    current_direction = 3;
                    arena_map[i][j] = '.';
                }
                else
                {
                    arena_map[i][j] = field;
                }
            }
        }
        std::string orders;
        std::cin >> orders;
        int result = 0;
        for (int i = 0; i < orders.size(); i++)
        {
            if (orders[i] == 'F')
            {
                pos next_pos = {current_pos.y + directions[current_direction].y, current_pos.x + directions[current_direction].x};
                if (next_pos.x < 0 || next_pos.y < 0)
                    continue;
                if (next_pos.y >= N || next_pos.x >= M)
                    continue;
                if (arena_map[next_pos.y][next_pos.x] == '#')
                    continue;
                current_pos = next_pos;
                if (arena_map[current_pos.y][current_pos.x] == '*')
                {
                    result++;
                    arena_map[current_pos.y][current_pos.x] = '.';
                }
            }
            else if (orders[i] == 'D')
                updateDirection(current_direction, 1);
            else
                updateDirection(current_direction, -1);
        }
        std::cout << result << '\n';
        std::cin >> N >> M >> S;
    }
}