#include <iostream>
#include <vector>
#include <stack>
#include <iostream>

typedef std::pair<int, int> ii;

const int INF = 1000000001;


std::vector<std::vector<int>> memotable;
std::vector<std::vector<int>> grid;

int n, k;

//Because of field value condition (prev must be smaller than next) graph is DAG, therefore O(n) DP can be used
int findMaxResultStartingFromCoordinates(int y, int x)
{
	if (memotable[y][x] != -1)
	{
		return memotable[y][x];
	}
	int result = grid[y][x];
	for (int i = 1; i <= k; i++)
	{
		if (y + i < n && grid[y + i][x] > grid[y][x])
		{
			result = std::max(result, grid[y][x] + findMaxResultStartingFromCoordinates(y + i, x));
		}
		if (y - i >= 0 && grid[y - i][x] > grid[y][x])
		{
			result = std::max(result, grid[y][x] + findMaxResultStartingFromCoordinates(y - i, x));
		}
		if (x + i < n && grid[y][x + i] > grid[y][x])
		{
			result = std::max(result, grid[y][x] + findMaxResultStartingFromCoordinates(y, x + i));
		}
		if (x - i >= 0 && grid[y][x - i] > grid[y][x])
		{
			result = std::max(result, grid[y][x] + findMaxResultStartingFromCoordinates(y, x - i));
		}
	}
	memotable[y][x] = result;
	return result;
}
int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	for (int i = 0; i < test_cases; i++)
	{
		if (i != 0)
		{
			printf("\n");
		}
		scanf("%d %d", &n, &k);
		memotable.clear();
		memotable.resize(n);
		grid.resize(n);
		for (int i = 0; i < n; i++)
		{
			memotable[i].assign(n, -1);
			grid[i].resize(n);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int value;
				scanf("%d", &value);
				grid[i][j] = value;
			}
		}
		int result = findMaxResultStartingFromCoordinates(0, 0);
		printf("%d\n", result);
	}
}