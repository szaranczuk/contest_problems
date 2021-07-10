#include <iostream>
#include <vector>

const int INF = 100000001;

std::vector<std::vector<int>> AdjMatrix;

int main()
{
	AdjMatrix.resize(100);
	int a, b;
	scanf("%d %d", &a, &b);
	int case_counter = 0;
	while (a != 0 || b != 0)
	{
		case_counter++;
		for (int i = 0; i < 100; i++)
		{
			AdjMatrix[i].clear();
			AdjMatrix[i].assign(100, INF);
		}
		AdjMatrix[a - 1][b - 1] = 1;
		scanf("%d %d", &a, &b);
		while (a != 0 || b != 0)
		{
			AdjMatrix[a - 1][b - 1] = 1;
			AdjMatrix[a - 1][a - 1] = 0;
			AdjMatrix[b - 1][b - 1] = 0;
			scanf("%d %d", &a, &b);
		}
		//Floyd-Warshall
		for (int k = 0; k < 100; k++)
		{
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					AdjMatrix[i][j] = std::min(AdjMatrix[i][j], AdjMatrix[i][k] + AdjMatrix[k][j]);
				}
			}
		}
		int total_weights = 0;
		int total_nodes = 0;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (AdjMatrix[i][j] != INF && i != j)
				{
					total_weights += AdjMatrix[i][j];
					total_nodes++;
				}
			}
		}
		double result = static_cast<double>(total_weights) / static_cast<double>(total_nodes);
		printf("Case %d: average length between pages = %.3lf clicks\n", case_counter, result);
		scanf("%d %d", &a, &b);
	}
}