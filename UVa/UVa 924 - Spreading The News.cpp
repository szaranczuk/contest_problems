#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> Adj;
std::vector<int> distance;
std::vector<bool> wasVertexVisited;
std::vector<int> number_of_vertices_in_distance;

void BFS(int source)
{
	distance[source] = 0;
	wasVertexVisited[source] = true;
	std::queue<int> BFS_queue;
	BFS_queue.push(source);
	while (!BFS_queue.empty())
	{
		int local_boom = 0;
		int vertex = BFS_queue.front();
		BFS_queue.pop();
		for (int adjacent : Adj[vertex])
		{
			if (!wasVertexVisited[adjacent])
			{
				wasVertexVisited[adjacent] = true;
				distance[adjacent] = distance[vertex] + 1;
				number_of_vertices_in_distance[distance[adjacent]]++;
				BFS_queue.push(adjacent);
			}
		}
	}
}

int main()
{
	int number_of_employees;
	scanf("%d", &number_of_employees);
	Adj.resize(number_of_employees);
	distance.resize(number_of_employees);
	for (int i = 0; i < number_of_employees; i++)
	{
		int number_of_edges;
		scanf("%d", &number_of_edges);
		for (int j = 0; j < number_of_edges; j++)
		{
			int adjacent;
			scanf("%d", &adjacent);
			Adj[i].push_back(adjacent);
		}
	}
	int number_of_test_cases;
	scanf("%d", &number_of_test_cases);
	for (int i = 0; i < number_of_test_cases; i++)
	{
		wasVertexVisited.clear();
		wasVertexVisited.assign(number_of_employees, false);
		number_of_vertices_in_distance.clear();
		number_of_vertices_in_distance.assign(number_of_employees, 0);
		int source;
		scanf("%d", &source);
		BFS(source);
		int result_boom = 0;
		int result_boom_day;
		for (int i = 0; i < number_of_employees; i++)
		{
			if (number_of_vertices_in_distance[i] > result_boom)
			{
				result_boom = number_of_vertices_in_distance[i];
				result_boom_day = i;
			}
		}
		if (result_boom == 0)
		{
			printf("0\n");
		}
		else
		{
			printf("%d %d\n", result_boom, result_boom_day);
		}
	}
}