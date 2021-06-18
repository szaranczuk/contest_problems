//sorry for poor code quality, something was not working, and I spent about 3 hours to find out that I didnt update fucking visit state in findSCC do while
//so meanwhile when I was trying to fix things that worked properly, I broke code readability
//but concept is simple, find strongly connected components, make DAG(s) out of it, sort this topologically, and then just do DFS, to check
//how many disjoint DAGs are here

#include <iostream>
#include <vector>
#include <stack>
#include <set>

int n, m;
int dfsIndex;
int SCCIndex;

std::vector<std::vector<int>> Adj;
std::vector<int> visit_state;
std::vector<int> dfs_num;
std::vector<int> dfs_low;
std::vector<int> top_sorted_SCC;
std::vector<std::set<int>> SCC_Adj;
std::vector<int> root;

std::stack<int> dfs_stack;

void findSCC(int vertex)
{
	visit_state[vertex] = 2;
	dfs_num[vertex] = dfs_low[vertex] = dfsIndex;
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
	if (dfs_num[vertex] == dfs_low[vertex])
	{
		int SCC_vetex;
		do
		{
			SCC_vetex = dfs_stack.top();
			dfs_stack.pop();
			root[SCC_vetex] = SCCIndex;
			visit_state[SCC_vetex] = 1;
		} while (SCC_vetex != vertex);
		SCCIndex++;
	}
}

void SCC_DFS(int vertex)
{
	visit_state[vertex] = 1;
	for (int adjacent : SCC_Adj[vertex])
	{
		if (visit_state[adjacent] == 0)
		{
			SCC_DFS(adjacent);
		}
	}
}

void topSort(int vertex)
{
	visit_state[vertex] = 1;
	for (int adjacent : SCC_Adj[vertex])
	{
		if (visit_state[adjacent] == 0)
		{
			topSort(adjacent);
		}
	}
	top_sorted_SCC.push_back(vertex);
}

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	for (int i = 0; i < test_cases; i++)
	{
		scanf("%d %d", &n, &m);
		SCCIndex = 0;
		dfsIndex = 0;
		dfs_stack = std::stack<int>();
		Adj.erase(Adj.begin(), Adj.end());
		Adj.resize(n);
		top_sorted_SCC.erase(top_sorted_SCC.begin(), top_sorted_SCC.end());
		visit_state.resize(n);
		dfs_num.resize(n);
		dfs_low.resize(n);
		root.resize(n);
		for (int i = 0; i < n; i++)
		{
			visit_state[i] = 0;
		}
		for (int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			Adj[a - 1].push_back(b - 1);
		}
		for (int i = 0; i < n; i++)
		{
			if (visit_state[i] == 0)
			{
				findSCC(i);
			}
		}
		SCC_Adj.clear();
		SCC_Adj.resize(SCCIndex);
		for (int i = 0; i < n; i++)
		{
			for (int adjacent : Adj[i])
			{
				if (root[i] != root[adjacent])
				{
					SCC_Adj[root[i]].insert(root[adjacent]);
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			visit_state[i] = 0;
		}
		for (int i = 0; i < SCCIndex; i++)
		{
			if (visit_state[i] == 0)
			{
				topSort(i);
			}
		}
		int result = 0;
		for (int i = 0; i < n; i++)
		{
			visit_state[i] = 0;
		}
		for (int i = top_sorted_SCC.size() - 1; i >= 0; i--)
		{
			if (visit_state[top_sorted_SCC[i]] == 0)
			{
				result++;
				SCC_DFS(top_sorted_SCC[i]);
			}
		}
		printf("%d\n", result);
	}
}