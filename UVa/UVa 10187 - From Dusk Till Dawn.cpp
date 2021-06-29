#include <iostream>
#include <vector>
#include <queue>
#include <map>

typedef std::pair<int, int> ii;
typedef std::pair<int, ii> iii;

const int INF = 1000000001;

std::vector<std::vector<std::vector<iii>>> Adj;
std::vector<std::vector<int>> distance;
std::vector<std::vector<ii>> parent;

void Dijkstra(int source)
{
	std::priority_queue<iii, std::vector<iii>, std::greater<iii>> pq;
	for (int i = 0; i < 24; i++)
	{
		pq.push({0, {source, i}});
		distance[source][i] = 0;
		parent[source][i] = {-1, -1};
	}
	while (!pq.empty())
	{
		iii vertex = pq.top();
		pq.pop();
		if (vertex.first > distance[vertex.second.first][vertex.second.second])
		{
			continue;
		}
		for (iii adjacent : Adj[vertex.second.first][vertex.second.second])
		{
			if (distance[adjacent.second.first][adjacent.second.second] > distance[vertex.second.first][vertex.second.second] + adjacent.first)
			{
				distance[adjacent.second.first][adjacent.second.second] = distance[vertex.second.first][vertex.second.second] + adjacent.first;
				pq.push({distance[adjacent.second.first][adjacent.second.second], {adjacent.second.first, adjacent.second.second}});
				parent[adjacent.second.first][adjacent.second.second] = vertex.second;
			}
		}
	}
}

int main()
{
	int test_cases;
	std::cin >> test_cases;
	for (int i = 0; i < test_cases; i++)
	{
		printf("Test Case %d.\n", i + 1);
		int E;
		if (i == 33)
		{
			E = 2 + 2;
		}
		std::cin >> E;
		Adj.clear();
		Adj.resize(E * 2);
		for (int i = 0; i < Adj.size(); i++)
		{
			Adj[i].resize(24);
			for (int j = 0; j < 24; j++)
			{
				if (j == 11)
				{
					Adj[i][j].push_back({1, {i, (j + 1) % 24}});
				}
				else
				{
					Adj[i][j].push_back({0, {i, (j + 1) % 24}});
				}
			}
		}
		std::map<std::string, int> stations;
		int free_index = 0;
		for (int i = 0; i < E; i++)
		{
			std::string source, destination;
			std::cin >> source >> destination;
			if (stations.find(source) == stations.end())
			{
				stations.insert({source, free_index});
				free_index++;
			}
			if (stations.find(destination) == stations.end())
			{
				stations.insert({destination, free_index});
				free_index++;
			}
			int departure, travel_time;
			std::cin >> departure >> travel_time;
			if ((departure % 24 >= 18 || departure % 24 <= 6) && travel_time <= 12 && ((departure + travel_time) % 24 >= 18 || (departure + travel_time) % 24 <= 6))
				Adj[stations[source]][departure % 24].push_back({0, {stations[destination], (departure + travel_time) % 24}});
		}
		distance.clear();
		distance.resize(stations.size());
		parent.clear();
		parent.resize(stations.size());
		for (int i = 0; i < stations.size(); i++)
		{
			distance[i].assign(24, INF);
			parent[i].resize(24);
		}
		std::string source, destination;
		std::cin >> source >> destination;
		if (source != destination)
		{
			if (stations.find(source) == stations.end() || stations.find(destination) == stations.end())
			{
				printf("There is no route Vladimir can take.\n");
			}
			else
			{
				Dijkstra(stations[source]);
				int minimum = INF;
				int integer_destination = stations[destination];
				for (int i = 0; i < 24; i++)
				{
					minimum = std::min(minimum, distance[integer_destination][i]);
				}
				if (minimum == INF)
					printf("There is no route Vladimir can take.\n");
				else
				{
					printf("Vladimir needs %d litre(s) of blood.\n", minimum);
				}
			}
		}
		else
		{

			printf("Vladimir needs 0 litre(s) of blood.\n");
		}
	}
}