#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <queue>
#include <set>

std::vector<std::list<int>> Adj;
std::vector<bool> visited;
std::vector<int> dp;
int k;

void dfs(int vertex)
{
	visited[vertex] = true;
	int degree = Adj[vertex].size();
	for (int adjacent : Adj[vertex])
	{
		if (!visited[adjacent])
		{
			dfs(adjacent);
			dp[vertex] += dp[adjacent] + 1;
		}
	}
	dp[vertex] = std::max(0, dp[vertex] - k);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	std::cin >> n;
	Adj.resize(n);
	visited.assign(n, false);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		std::cin >> a >> b;
		a--;
		b--;
		Adj[a].push_back(b);
		Adj[b].push_back(a);
	}
	int l = 0;
	int r = 0;
	for (int i = 0; i < n - 1; i++)
	{
		r = std::max(r, (int) Adj[i].size());
	}
	while (r > l)
	{
		visited.clear();
		visited.assign(n, false);
		dp.clear();
		dp.assign(n, 0);
		int s = (l + r) / 2;
		k = s;
		dfs(0);
		if (dp[0] == 0)
		{
			r = s;
		}
		else
		{
			l = s + 1;
		}
	}
	std::cout << r << '\n';
}