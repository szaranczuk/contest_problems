#include <iostream>
#include <vector>
#include <algorithm>

int number_of_servers_in_network;
int dfsIndex;

std::vector<std::vector<int>> Adj;
std::vector<int> wasVertexVisited;
std::vector<int> connected_components;
std::vector<std::pair<int, int>> bridges;
std::vector<int> dfs_num;
std::vector<int> dfs_low;
std::vector<int> dfs_parent;

void DFS(int vertex)
{
	wasVertexVisited[vertex] = true;
	for (int adjacent : Adj[vertex])
	{
		if (!wasVertexVisited[adjacent])
		{
			DFS(adjacent);
		}
	}
}
void findConnectedComponents()
{
	for (int i = 0; i < number_of_servers_in_network; i++)
	{
		if (!wasVertexVisited[i])
		{
			connected_components.push_back(i);
			DFS(i);
		}
	}
}
void findBridges(int vertex)
{
	wasVertexVisited[vertex] = true;
	dfs_num[vertex] = dfs_low[vertex] = dfsIndex;
	dfsIndex++;
	for (int adjacent : Adj[vertex])
	{
		if (wasVertexVisited[adjacent])
		{
			if (dfs_parent[vertex] != adjacent)
			{
				dfs_low[vertex] = std::min(dfs_low[vertex], dfs_num[adjacent]);
			}
		}
		else
		{
			dfs_parent[adjacent] = vertex;
			findBridges(adjacent);
			if (dfs_low[adjacent] > dfs_num[vertex])
			{
				bridges.push_back({std::min(vertex, adjacent), std::max(vertex,  adjacent)});
			}
			dfs_low[vertex] = std::min(dfs_low[vertex], dfs_low[adjacent]);
		}
	}
}

int main()
{
	while (scanf("%d", &number_of_servers_in_network) == 1)
	{
		Adj.erase(Adj.begin(), Adj.end());
		Adj.resize(number_of_servers_in_network);
		wasVertexVisited.resize(number_of_servers_in_network);
		connected_components.erase(connected_components.begin(),connected_components.end());
		bridges.erase(bridges.begin(), bridges.end());
		dfs_parent.resize(number_of_servers_in_network);
		dfs_num.resize(number_of_servers_in_network);
		dfs_low.resize(number_of_servers_in_network);
		dfsIndex = 0;
		for (int i = 0; i < number_of_servers_in_network; i++)
		{
			int server_index, number_of_connected_servers;
			scanf("%d (%d)", &server_index, &number_of_connected_servers);
			for (int j = 0; j < number_of_connected_servers; j++)
			{
				int connected_server;
				scanf("%d", &connected_server);
				Adj[server_index].push_back(connected_server);
			}
		}
		for (int i = 0; i < number_of_servers_in_network; i++)
		{
			wasVertexVisited[i] = false;
		}
		findConnectedComponents();
		for (int i = 0; i < number_of_servers_in_network; i++)
		{
			wasVertexVisited[i] = false;
		}
		for (int vertex : connected_components)
		{
			findBridges(vertex);
		}
		printf("%d critical links\n", bridges.size());
		std::sort(bridges.begin(), bridges.end(), [](std::pair<int, int> a, std::pair<int, int> b){
			if(a.first == b.first) {return a.second < b.second;}
			else {return a.first < b.first;}
		});
		for (auto bridge : bridges)
		{
			printf("%d - %d\n", bridge.first, bridge.second);
		}
		printf("\n");
	}
}