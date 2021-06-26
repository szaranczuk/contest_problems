#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> ii;

const int INF = 1000000001;

int N, E, T, M;

std::vector<std::vector<ii>> Adj;
std::vector<int> distance;

void Dijkstra(int source)
{
	std::priority_queue<ii, std::vector<ii>, std::greater<ii>> dijkstra_queue;
	distance[source] = 0;
	dijkstra_queue.push({0, source});
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
		if (i != 0)
		{
			printf("\n");
		}
		scanf("%d", &N);
		scanf("%d", &E);
		scanf("%d", &T);
		scanf("%d", &M);
		Adj.clear();
		Adj.resize(N);
		for (int i = 0; i < M; i++)
		{
			int a, b, weight;
			scanf("%d %d %d", &a, &b, &weight);
			Adj[b - 1].push_back({weight, a - 1}); //since we need to know the way to source, not from source
		}
		distance.clear();
		distance.assign(N, INF);
		Dijkstra(E - 1);
		int result = 0;
		for (int time : distance)
		{
			if (time <= T)
			{
				result++;
			}
		}
		printf("%d\n", result);
	}
}