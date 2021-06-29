#include <iostream>
#include <vector>

struct Edge
{
	int source;
	int destination;
	int weight;
};

const int INF = 1000000001;
int V, E;

std::vector<Edge> edges;
std::vector<int> distance;

bool BellmanFord(int source)
{
	distance[source] = 0;
	for (int i = 0; i < V; i++)
	{
		for (Edge edge : edges)
		{
			if (distance[edge.destination] > distance[edge.source] + edge.weight)
			{
				distance[edge.destination] = distance[edge.source] + edge.weight;
			}
		}
	}
	for (Edge edge : edges)
	{
		if (distance[edge.destination] > distance[edge.source] + edge.weight)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	for (int i = 0; i < test_cases; i++)
	{
		scanf("%d %d", &V, &E);
		edges.clear();
		for (int i = 0; i < E; i++)
		{
			int source, destination, weight;
			scanf("%d %d %d", &source, &destination, &weight);
			edges.push_back({source, destination, weight});
		}
		distance.clear();
		distance.assign(V, INF);
		bool isThereAnyNegativeCycle = !BellmanFord(0);
		if (isThereAnyNegativeCycle)
		{
			printf("possible\n");
		}
		else
		{
			printf("not possible\n");
		}
	}
}