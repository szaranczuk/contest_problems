#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Edge
{
	int source;
	int destination;
	double weight;
};
struct Vertex
{
	int parent;
	int rank;
};

int S, P;
int number_of_connected_components;
double result;

std::vector<Vertex> vertices;
std::vector<Edge> edges;
std::vector<std::pair<int, int>> coordinates;

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
	vertices[vertex].parent = findRoot(vertices[vertex].parent);
	return vertices[vertex].parent;
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
			UnionSets(edge.source, edge.destination);
			number_of_connected_components--;
			result = edge.weight;
			if (number_of_connected_components == S)
			{
				return;
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
		scanf("%d %d", &S, &P);
		vertices.resize(P);
		edges.clear();
		coordinates.clear();
		number_of_connected_components = P;
		result = 0.0;
		for (int i = 0; i < P; i++)
		{
			makeset(i);
			int x, y;
			scanf("%d %d", &x, &y);
			coordinates.push_back({x, y});
		}
		for (int i = 0; i < P - 1; i++)
		{
			for (int j = i + 1; j < P; j++)
			{
				double x_difference = static_cast<double>(coordinates[i].first) - static_cast<double>(coordinates[j].first);
				double y_difference = static_cast<double>(coordinates[i].second) - static_cast<double>(coordinates[j].second);
				double distance = std::sqrt(x_difference * x_difference + y_difference * y_difference);
				edges.push_back({i, j, distance});
			}
		}
		std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
			  {
				  return a.weight < b.weight;
			  });
		Kruskhal();
		printf("%.2lf\n", result);
	}
}