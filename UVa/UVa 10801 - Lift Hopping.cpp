#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cmath>

int n, k;

typedef std::pair<int, std::pair<int, int>> iii;

const int INF = 1000000001;

std::vector<std::vector<int>> elevators_on_floor;
std::vector<std::vector<int>> distance;
std::vector<std::vector<std::vector<iii>>> Adj;

void Dijkstra(int source)
{
	std::priority_queue<iii, std::vector<iii>, std::greater<iii>> dijkstra_queue;
	for (int elevator : elevators_on_floor[0])
	{
		dijkstra_queue.push({0, {elevator, 0}});
		distance[elevator][0] = 0;
	}
	while (!dijkstra_queue.empty())
	{
		iii vertex = dijkstra_queue.top();
		dijkstra_queue.pop();
		if (distance[vertex.second.first][vertex.second.second] < vertex.first)
		{
			continue;
		}
		for (iii adjacent : Adj[vertex.second.first][vertex.second.second])
		{
			if (distance[adjacent.second.first][adjacent.second.second] > distance[vertex.second.first][vertex.second.second] + adjacent.first)
			{
				distance[adjacent.second.first][adjacent.second.second] = distance[vertex.second.first][vertex.second.second] + adjacent.first;
				dijkstra_queue.push({distance[adjacent.second.first][adjacent.second.second], {adjacent.second.first, adjacent.second.second}});
			}
		}
	}
}

int main()
{
	while (std::cin >> n >> k)
	{
		Adj.clear();
		Adj.resize(n);
		distance.clear();
		distance.resize(n);
		elevators_on_floor.clear();
		elevators_on_floor.resize(100);
		for (int i = 0; i < n; i++)
		{
			Adj[i].resize(100);
			distance[i].assign(100, INF);
		}
		std::vector<int> lifting_times;
		std::string times;
		std::ws(std::cin);
		std::getline(std::cin, times);
		std::stringstream ss(times);
		std::vector<std::vector<int>> floors_visited_by_elevator(n);
		int time;
		while (ss >> time)
		{
			lifting_times.push_back(time);
		}
		for (int i = 0; i < n; i++)
		{
			std::string elevator;
			std::ws(std::cin);
			std::getline(std::cin, elevator);
			std::stringstream ss(elevator);
			int floor;
			while (ss >> floor)
			{
				floors_visited_by_elevator[i].push_back(floor);
				elevators_on_floor[floor].push_back(i);
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < static_cast<int>(floors_visited_by_elevator[i].size()) - 1; j++)
			{
				for (int k = j + 1; k < floors_visited_by_elevator[i].size(); k++)
				{
					int a = floors_visited_by_elevator[i][j];
					int b = floors_visited_by_elevator[i][k];
					Adj[i][a].push_back({(std::abs(b - a)) * lifting_times[i], {i, b}});
					Adj[i][b].push_back({std::abs(b - a) * lifting_times[i], {i, a}});
				}
			}
		}
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < static_cast<int>(elevators_on_floor[i].size()) - 1; j++)
			{
				for (int k = j + 1; k < elevators_on_floor[i].size(); k++)
				{
					Adj[elevators_on_floor[i][j]][i].push_back({60, {elevators_on_floor[i][k], i}});
					Adj[elevators_on_floor[i][k]][i].push_back({60, {elevators_on_floor[i][j], i}});
				}
			}
		}
		Dijkstra(0);
		int result = INF;
		for (int i = 0; i < n; i++)
		{
			result = std::min(result, distance[i][k]);
		}
		if (result == INF)
		{
			printf("IMPOSSIBLE\n");
		}
		else
		{
			printf("%d\n", result);
		}
	}
}