#include <iostream>
#include <vector>
#include <stack>

int dfsIndex;
int number_of_SCC;

std::vector<std::vector<int>> Adj;
std::vector<int> dfs_num;
std::vector<int> dfs_low;
std::vector<int> visit_state;
std::stack<int> dfs_stack;

void findSCC(int vertex)
{
	visit_state[vertex] = 2;
	dfs_low[vertex] = dfs_num[vertex] = dfsIndex;
	dfsIndex++;
	dfs_stack.push(vertex);
	for (int adjacent : Adj[vertex])
	{
		if (visit_state[adjacent] == 0)
		{
			findSCC(adjacent);
		}
		if (visit_state[adjacent] == 2)
		{
			dfs_low[vertex] = std::min(dfs_low[vertex], dfs_low[adjacent]);
		}
	}
	if (dfs_low[vertex] == dfs_num[vertex])
	{
		number_of_SCC++;
		int SCC_vertex;
		do
		{
			SCC_vertex = dfs_stack.top();
			dfs_stack.pop();
			visit_state[SCC_vertex] = 1;
		} while (SCC_vertex != vertex);
	}
}
int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	while (n != 0 || m != 0)
	{
		dfsIndex = 0;
		number_of_SCC = 0;
		Adj.clear();
		Adj.resize(n);
		dfs_low.resize(n);
		dfs_num.resize(n);
		visit_state.resize(n);
		for (int i = 0; i < n; i++)
		{
			visit_state[i] = 0;
		}
		for (int i = 0; i < m; i++)
		{
			int V, W, P;
			scanf("%d %d %d", &V, &W, &P);
			Adj[V - 1].push_back(W - 1);
			if (P == 2)
			{
				Adj[W - 1].push_back(V - 1);
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (visit_state[i] == 0)
			{
				findSCC(i);
			}
		}
		if (number_of_SCC <= 1)
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
		scanf("%d %d", &n, &m);
	}
}