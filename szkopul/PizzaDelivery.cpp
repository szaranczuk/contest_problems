#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

typedef long long ll;
typedef std::pair<ll, int> lii;

int n, k;

std::vector<std::vector<lii>> Adj;

std::vector<ll> distance_to_root;
std::vector<lii> longest_path_to_leaf;
std::vector<int> parent;
std::vector<bool> visited;

void dfs(int vertex, ll distance)
{
	visited[vertex] = true;
	distance_to_root[vertex] = distance;
	for (lii adjacent : Adj[vertex])
	{
		if (!visited[adjacent.second])
		{
			parent[adjacent.second] = vertex;
			dfs(adjacent.second, distance + adjacent.first);
			if (longest_path_to_leaf[adjacent.second].first + adjacent.first > longest_path_to_leaf[vertex].first)
			{
				longest_path_to_leaf[vertex].first = longest_path_to_leaf[adjacent.second].first + adjacent.first;
				longest_path_to_leaf[vertex].second = adjacent.second;
			}
		}
	}
}

void preprocess()
{
	distance_to_root.resize(n);
	longest_path_to_leaf.assign(n, {0, -1});
	visited.assign(n, false);
	parent.resize(n);
	parent[0] = -1;
	dfs(0, 0);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cin >> n >> k;
	Adj.resize(n);
	ll total_weight = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		a--;
		b--;
		Adj[a].push_back({c, b});
		Adj[b].push_back({c, a});
		total_weight += c;
	}
	preprocess();
	std::set<lii> next_path;
	next_path.insert({longest_path_to_leaf[0].first, 0});
	long long result = 0ll;
	int number_of_paths = 0;
	std::vector<bool> dupa(n, false);
	while (number_of_paths != k && !next_path.empty())
	{
		lii path = *(next_path.rbegin());
		next_path.erase(path);
		if (dupa[path.second])
			continue;
		number_of_paths++;
		if (path.first <= 0)
		{
			break;
		}
		result += path.first;
		int next_vertex = path.second;
		while (next_vertex != -1)
		{
			dupa[next_vertex] = true;
			for (auto adjacent : Adj[next_vertex])
			{
				if (adjacent.second != parent[next_vertex])
				{
					ll new_distance = longest_path_to_leaf[adjacent.second].first + adjacent.first - distance_to_root[next_vertex];
					next_path.insert({new_distance, adjacent.second});
				}
			}
			next_vertex = longest_path_to_leaf[next_vertex].second;
		}
	}
	std::cout << (2 * total_weight) - result << '\n';
}