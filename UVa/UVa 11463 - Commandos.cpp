#include <iostream>
#include <vector>

const int INF = 100000001;

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	for (int i = 0; i < test_cases; i++)
	{
		int N;
		scanf("%d", &N);
		int R;
		scanf("%d", &R);
		std::vector<std::vector<int>> AdjMatrix;
		AdjMatrix.resize(N);
		for (int i = 0; i < N; i++)
		{
			AdjMatrix[i].assign(N, INF);
			AdjMatrix[i][i] = 0;
		}
		for (int i = 0; i < R; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			AdjMatrix[a][b] = 1;
			AdjMatrix[b][a] = 1;
		}
		int start, end;
		scanf("%d %d", &start, &end);
		//Floyd-Warshall, since graph size is small and its significantly easier to implement FW than Dijkstra or Bellman-Ford
		for (int k = 0; k < N; k++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					AdjMatrix[i][j] = std::min(AdjMatrix[i][j], AdjMatrix[i][k] + AdjMatrix[k][j]);
				}
			}
		}
		int result = -1;
		for (int k = 0; k < N; k++)
		{
			result = std::max(result, AdjMatrix[start][k] + AdjMatrix[k][end]);
		}
		printf("Case %d: %d\n", i + 1, result);
	}
}