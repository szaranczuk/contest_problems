#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1000000001;

struct Vertex
{
	int parent;
	int rank;
};
struct Edge
{
	int source;
	int destination;
	int weight;
	bool canBeUsedInMST;
};

int N, M;

std::vector<Edge> edges;
std::vector<Edge *> MST_edges;
std::vector<Vertex> vertices;

void makeset(int vertex)
{
	vertices[vertex].parent = -1;
	vertices[vertex].rank = 0;
}

int findRoot(int vertex)
{
	if (vertices[vertex].parent == -1)
	{
		return vertex;
	}
	else
	{
		vertices[vertex].parent = findRoot(vertices[vertex].parent);
		return vertices[vertex].parent;
	}
}
void UnionSets(int a, int b)
{
	int a_root = findRoot(a);
	int b_root = findRoot(b);
	if (vertices[a_root].rank > vertices[b_root].rank)
	{
		vertices[b_root].parent = a_root;
	}
	else if (vertices[a_root].rank < vertices[b_root].rank)
	{
		vertices[a_root].parent = b_root;
	}
	else if (a_root != b_root)
	{
		vertices[b_root].parent = a_root;
		vertices[a_root].rank++;
	}
}

int Kruskhal(bool firstMST)
{
	int MST_weight = 0;
	int number_of_edges = 0;
	for (Edge &edge : edges)
	{
		if (edge.canBeUsedInMST && (findRoot(edge.source) != findRoot(edge.destination)))
		{
			UnionSets(edge.source, edge.destination);
			MST_weight += edge.weight;
			number_of_edges++;
			if (firstMST)
				MST_edges.push_back(&edge);
		}
	}
	if (number_of_edges < N - 1)
		return INF;
	else
		return MST_weight;
}

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	for (int i = 0; i < test_cases; i++)
	{
		scanf("%d %d", &N, &M);
		vertices.resize(N);
		edges.clear();
		MST_edges.clear();
		for (int i = 0; i < N; i++)
		{
			makeset(i);
		}
		for (int i = 0; i < M; i++)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			edges.push_back({a - 1, b - 1, c, true});
		}
		std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
			  { return a.weight < b.weight; });
		int first_cost = Kruskhal(true);
		int second_cost = INF;
		for (int i = 0; i < MST_edges.size(); i++)
		{
			for (int j = 0; j < N; j++)
			{
				makeset(j);
			}
			MST_edges[i]->canBeUsedInMST = false;
			second_cost = std::min(second_cost, Kruskhal(false));
			MST_edges[i]->canBeUsedInMST = true;
		}
		printf("%d %d\n", first_cost, second_cost);
	}
}