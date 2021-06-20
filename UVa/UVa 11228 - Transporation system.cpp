#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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

struct Coordinates
{
	int x;
	int y;
};

int n, r;
int road_connections;
double road_length, rail_length;
std::vector<Coordinates> coord_vector;
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
		return vertex;
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
			UnionSets(edge.source, edge.destination);
			if (edge.weight <= r)
			{
				road_connections++;
				road_length += edge.weight;
			}
			else
			{
				rail_length += edge.weight;
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
		scanf("%d %d", &n, &r);
		road_length = rail_length = 0.0;
		road_connections = 0;
		coord_vector.clear();
		vertices.clear();
		edges.clear();
		vertices.resize(n);
		for (int i = 0; i < n; i++)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			coord_vector.push_back({x, y});
		}
		for (int i = 0; i < n; i++)
		{
			makeset(i);
			for (int j = 0; j < n; j++)
			{
				double x_difference = static_cast<double>(coord_vector[i].x) - static_cast<double>(coord_vector[j].x);
				double y_difference = static_cast<double>(coord_vector[i].y) - static_cast<double>(coord_vector[j].y);
				double distance = std::sqrt(x_difference * x_difference + y_difference * y_difference);
				edges.push_back({i, j, distance});
			}
		}
		std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
			  { return a.weight < b.weight; });
		Kruskhal();
		int rounded_rail_length = std::round(rail_length);
		int rounded_road_length = std::round(road_length);
		printf("Case #%d: %d %d %d\n", i + 1, n - road_connections, rounded_road_length, rounded_rail_length);
	}
}