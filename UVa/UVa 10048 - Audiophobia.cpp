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

int C, S, Q;

std::vector<Vertex> vertices;
std::vector<Edge> edges;
std::vector<std::vector<std::pair<int, int>>> Adj;
std::vector<bool> wasVertexVisited;

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

void UnionSet(int a, int b)
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
			Adj[edge.source].push_back({edge.destination, edge.weight});
			Adj[edge.destination].push_back({edge.source, edge.weight});
			UnionSet(edge.source, edge.destination);
		}
	}
}

int maximumSound(int vertex, int destination, int max_sound)
{
	wasVertexVisited[vertex] = true;
	if (vertex == destination)
	{
		return max_sound;
	}
	int actual_max = -1;
	for (auto adjacent : Adj[vertex])
	{
		if (!wasVertexVisited[adjacent.first])
		{
			actual_max = std::max(actual_max, maximumSound(adjacent.first, destination, std::max(max_sound, adjacent.second)));
		}
	}
	return actual_max;
}

int main()
{
	scanf("%d %d %d", &C, &S, &Q);
	int test_case_counter = 0;
	while (C != 0 || S != 0 || Q != 0)
	{
		if (test_case_counter != 0)
		{
			printf("\n");
		}
		test_case_counter++;
		vertices.resize(C);
		edges.clear();
		Adj.clear();
		Adj.resize(C);
		for (int i = 0; i < C; i++)
		{
			makeset(i);
		}
		for (int i = 0; i < S; i++)
		{
			int a, b, weight;
			scanf("%d %d %d", &a, &b, &weight);
			edges.push_back({a - 1, b - 1, weight});
		}
		std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
			  { return a.weight < b.weight; });
		Kruskhal();
		printf("Case #%d\n", test_case_counter);
		for (int i = 0; i < Q; i++)
		{
			wasVertexVisited.clear();
			wasVertexVisited.assign(C + 1, false);
			int c1, c2;
			scanf("%d %d", &c1, &c2);
			int max_sound = maximumSound(c1 - 1, c2 - 1, -1);
			if (max_sound == -1)
			{
				printf("no path\n");
			}
			else
			{
				printf("%d\n", max_sound);
			}
		}
		scanf("%d %d %d", &C, &S, &Q);
	}
}