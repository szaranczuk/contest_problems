#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> ii;

const int INF = 1000000001;

struct Edge
{
	int source;
	int destination;
	int weight;
};

std::vector<std::vector<std::vector<ii>>> Adj;
std::vector<std::vector<int>> distance;

void Dijkstra(int source, int index)
{
	distance[index][source] = 0;
	std::priority_queue<ii, std::vector<ii>, std::greater<ii>> dijkstra_queue;
	dijkstra_queue.push({0, source});
	while (!dijkstra_queue.empty())
	{
		ii vertex = dijkstra_queue.top();
		dijkstra_queue.pop();
		if (distance[index][vertex.second] < vertex.first)
		{
			continue;
		}
		for (ii adjacent : Adj[index][vertex.second])
		{
			if (distance[index][adjacent.second] > distance[index][vertex.second] + adjacent.first)
			{
				distance[index][adjacent.second] = distance[index][vertex.second] + adjacent.first;
				dijkstra_queue.push({distance[index][adjacent.second], adjacent.second});
			}
		}
	}
}

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	for (int i = 0; i < test_cases; i++)
	{
		int n, m, s, t, p;
		scanf("%d %d %d %d %d", &n,  &m, &s, &t, &p);
		Adj.clear();
		Adj.resize(2);
		Adj[0].resize(n);
		Adj[1].resize(n);
		distance.resize(2);
		distance[0].assign(n, INF);
		distance[1].assign(n, INF);
		std::vector<Edge> edges;
		for (int i = 0; i < m; i++)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			Adj[0][a - 1].push_back({c, b - 1});
			Adj[1][b - 1].push_back({c, a - 1});
			edges.push_back({a - 1, b - 1, c});
		}
		Dijkstra(s - 1, 0);
		Dijkstra(t - 1, 1);
		int max_edge = -1;
		for (Edge edge : edges)
		{
			if (distance[0][edge.source] + edge.weight + distance[1][edge.destination] <= p)
			{
				max_edge = std::max(max_edge, edge.weight);
			}
		}
		printf("%d\n", max_edge);
	}
}