#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
	int source;
	int destination;
	int weight;
};
struct Vertex
{
	int parent;
	int rank;
};

int m, n;
int MST_weight, total_weight;

std::vector<Vertex> vertices;
std::vector<Edge> edges;

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

void Kruskhal()
{
	for (Edge edge : edges)
	{
		if (findRoot(edge.source) != findRoot(edge.destination))
		{
			MST_weight += edge.weight;
			UnionSets(edge.source, edge.destination);
		}
	}
}

int main()
{
	scanf("%d %d", &m, &n);
	while (n != 0 || m != 0)
	{
		vertices.resize(m);
		edges.clear();
		MST_weight = total_weight = 0;
		for (int i = 0; i < m; i++)
		{
			makeset(i);
		}
		for (int i = 0; i < n; i++)
		{
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			edges.push_back({x, y, z});
			total_weight += z;
		}
		std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
			  { return a.weight < b.weight; });
		Kruskhal();
		printf("%d\n", total_weight - MST_weight);
		scanf("%d %d", &m, &n);
	}
}