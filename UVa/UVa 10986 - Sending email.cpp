#include <iostream>
#include <queue>
#include <vector>

typedef std::pair<int, int> ii;

const int INF = 1000000001;

std::vector<std::vector<ii>> Adj;
std::vector<int> distance;

void Dijkstra(int source)
{
	std::priority_queue<ii, std::vector<ii>, std::greater<ii>> dijkstra_queue;
	dijkstra_queue.push({0, source});
	distance[source] = 0;
	while (!dijkstra_queue.empty())
	{
		ii vertex = dijkstra_queue.top();
		dijkstra_queue.pop();
		if (distance[vertex.second] < vertex.first)
		{
			continue;
		}
		for (ii adjacent : Adj[vertex.second])
		{
			if (distance[adjacent.second] > distance[vertex.second] + adjacent.first)
			{
				distance[adjacent.second] = distance[vertex.second] + adjacent.first;
				dijkstra_queue.push({distance[adjacent.second], adjacent.second});
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
		int n, m, S, T;
		scanf("%d %d %d %d", &n, &m, &S, &T);
		Adj.clear();
		Adj.resize(n);
		for (int i = 0; i < m; i++)
		{
			int a, b, weight;
			scanf("%d %d %d", &a, &b, &weight);
			Adj[a].push_back({weight, b});
			Adj[b].push_back({weight, a});
		}
		distance.clear();
		distance.assign(n, INF);
		Dijkstra(S);
		printf("Case #%d: ", i + 1);
		if (distance[T] == INF)
		{
			printf("unreachable\n");
		}
		else
		{
			printf("%d\n", distance[T]);
		}
	}
}