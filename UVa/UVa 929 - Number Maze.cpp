#include <iostream>
#include <queue>
#include <vector>

const int INF = 1000000001;
int N, M;

std::vector<int> dy = {1, 0, -1, 0};
std::vector<int> dx = {0, 1, 0, -1};

std::vector<std::vector<int>> maze;
std::vector<std::vector<int>> distance;

void Dijkstra(int y_source, int x_source)
{
	distance[y_source][x_source] = maze[y_source][x_source];
	std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> dijkstra_queue;
	dijkstra_queue.push({maze[y_source][x_source], {y_source, x_source}});
	while (!dijkstra_queue.empty())
	{
		auto vertex = dijkstra_queue.top();
		dijkstra_queue.pop();
		if (vertex.first > distance[vertex.second.first][vertex.second.second])
		{
			continue;
		}
		for (int i = 0; i < 4; i++)
		{
			int new_y = vertex.second.first + dy[i];
			int new_x = vertex.second.second + dx[i];
			if (new_y < N && new_y >= 0 && new_x < M && new_x >= 0)
			{
				if (distance[new_y][new_x] > distance[vertex.second.first][vertex.second.second] + maze[new_y][new_x])
				{
					distance[new_y][new_x] = distance[vertex.second.first][vertex.second.second] + maze[new_y][new_x];
					dijkstra_queue.push({distance[new_y][new_x], {new_y, new_x}});
				}
			}
		}
	}
}

int main()
{
	int number_of_test_cases;
	scanf("%d", &number_of_test_cases);
	for (int i = 0; i < number_of_test_cases; i++)
	{
		scanf("%d %d", &N, &M);
		maze.clear();
		maze.resize(N);
		distance.clear();
		distance.resize(N);
		for (int i = 0; i < N; i++)
		{
			distance[i].assign(M, INF);
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int value;
				scanf("%d", &value);
				maze[i].push_back(value);
			}
		}
		Dijkstra(0, 0);
		int result = distance[N - 1][M - 1];
		printf("%d\n", result);
	}
}