#include <iostream>
#include <vector>
#include <algorithm>

int n, m;
int dfsIndex;
int rootChildren;
int dfsRoot;
struct station
{
	int index;
	int pigeon_value;
};
std::vector<std::vector<int>> Adj;
std::vector<int> dfs_num;
std::vector<int> dfs_low;
std::vector<int> dfs_parent;
std::vector<station> pigeon_value;
std::vector<bool> wasVectorVisited;

void findPigeonValues(int vertex)
{
	wasVectorVisited[vertex] = true;
	dfs_num[vertex] = dfs_low[vertex] = dfsIndex;
	dfsIndex++;
	for (int adjacent : Adj[vertex])
	{
		if (wasVectorVisited[adjacent])
		{
			if (dfs_parent[adjacent] != vertex)
			{
				dfs_low[vertex] = std::min(dfs_low[vertex], dfs_num[adjacent]);
			}
		}
		else
		{
			if (vertex == dfsRoot)
			{
				rootChildren++;
			}
			dfs_parent[adjacent] = vertex;
			findPigeonValues(adjacent);
			if (dfs_low[adjacent] >= dfs_num[vertex])
			{
				pigeon_value[vertex].pigeon_value++;
			}
			dfs_low[vertex] = std::min(dfs_low[vertex], dfs_low[adjacent]);
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	while (n != 0 || m != 0)
	{
		dfsIndex = 0;
		Adj.erase(Adj.begin(), Adj.end());
		Adj.resize(n);
		dfs_num.resize(n);
		dfs_low.resize(n);
		pigeon_value.resize(n);
		wasVectorVisited.resize(n);
		dfs_parent.resize(n);
		for (int i = 0; i < n; i++)
		{
			pigeon_value[i] = {i, 1};
			wasVectorVisited[i] = false;
		}
		int a, b;
		scanf("%d %d", &a, &b);
		while (a != -1 || b != -1)
		{
			Adj[a].push_back(b);
			Adj[b].push_back(a);
			scanf("%d %d", &a, &b);
		}
		dfsRoot = 0;
		rootChildren = 0;
		findPigeonValues(dfsRoot);
		pigeon_value[dfsRoot].pigeon_value = rootChildren;
		std::sort(pigeon_value.begin(), pigeon_value.end(), [](const station &a, const station &b)
			  {
				  if (a.pigeon_value == b.pigeon_value)
				  {
					  return a.index < b.index;
				  }
				  else
				  {
					  return a.pigeon_value > b.pigeon_value;
				  }
			  });
		for (int i = 0; i < m; i++)
		{
			printf("%d %d\n", pigeon_value[i].index, pigeon_value[i].pigeon_value);
		}
		printf("\n");
		scanf("%d %d", &n, &m);
	}
}