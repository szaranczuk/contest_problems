#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

#define INF 1000000007

typedef std::pair<int, int> ii;

int n, m;

std::vector<std::vector<bool>> grid;
std::vector<int> dy = {1, 0, -1, 0};
std::vector<int> dx = {0, 1, 0, -1};
std::vector<std::vector<std::vector<int>>> distance;
std::vector<std::vector<int>> memotable;
std::vector<std::vector<bool>> visited;

void bfs(int y_s, int x_s, int d_index)
{
	distance[d_index][y_s][x_s] = 0;
	std::queue<ii> bfs_queue;
	bfs_queue.push({y_s, x_s});
	visited.clear();
	visited.resize(n);
	for (int i = 0; i < n; i++)
	{
		visited[i].assign(m, false);
	}
	visited[y_s][x_s] = true;
	while (!bfs_queue.empty())
	{
		ii vertex = bfs_queue.front();
		bfs_queue.pop();
		for (int i = 0; i < 4; i++)
		{
			int y = vertex.first + dy[i];
			int x = vertex.second + dx[i];
			if (y >= 0 && y < n && x >= 0 && x < m && !visited[y][x] && !grid[y][x])
			{
				distance[d_index][y][x] = distance[d_index][vertex.first][vertex.second] + 1;
				bfs_queue.push({y, x});
				visited[y][x] = true;
			}
		}
	}
	return;
}

int dp(int y, int x)
{
	if (y == n - 1 && x == m - 1)
	{
		return 1;
	}
	if (memotable[y][x] != -1)
	{
		return memotable[y][x];
	}
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		int n_y = y + dy[i];
		int n_x = x + dx[i];
		if (n_y >= 0 && n_y < n && n_x >= 0 && n_x < m && !grid[n_y][n_x])
		{
			if (distance[0][y][x] + distance[1][n_y][n_x] + 1 == distance[0][n - 1][m - 1])
			{
				result += dp(n_y, n_x);
				result %= INF;
			}
		}
	}
	memotable[y][x] = result;
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cin >> n >> m;
	grid.resize(n);
	distance.resize(2);
	distance[0].resize(n);
	distance[1].resize(n);
	memotable.resize(n);
	for (int i = 0; i < n; i++)
	{
		grid[i].resize(m);
		distance[0][i].assign(m, INF);
		distance[1][i].assign(m, INF);
		memotable[i].assign(m, -1);
		for (int j = 0; j < m; j++)
		{
			bool state;
			std::cin >> state;
			grid[i][j] = state;
		}
	}
	if (grid[0][0])
	{
		std::cout << "0\n";
		return 0;
	}
	bfs(0, 0, 0);
	bfs(n - 1, m - 1, 1);
	if (distance[0][n - 1][m - 1] == INF)
	{
		std::cout << "0\n";
	}
	else
	{
		int result = dp(0, 0);
		std::cout << result << '\n';
	}
	return 0;
}