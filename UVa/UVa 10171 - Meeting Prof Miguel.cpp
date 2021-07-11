#include <iostream>
#include <vector>

const int INF = 1000000001;

int main()
{
	int N;
	scanf("%d", &N);
	while (N != 0)
	{
		std::vector<std::vector<int>> Young_AdjMatrix;
		std::vector<std::vector<int>> Mature_AdjMatrix;
		Young_AdjMatrix.resize(26);
		Mature_AdjMatrix.resize(26);
		for (int i = 0; i < 26; i++)
		{
			Young_AdjMatrix[i].assign(26, INF);
			Young_AdjMatrix[i][i] = 0;
			Mature_AdjMatrix[i].assign(26, INF);
			Mature_AdjMatrix[i][i] = 0;
		}
		for (int i = 0; i < N; i++)
		{
			char age, bidirectionalness, source, destination;
			int weight;
			scanf("\n%c %c %c %c %d", &age, &bidirectionalness, &source, &destination, &weight);
			if (age == 'Y')
			{
				Young_AdjMatrix[source - 'A'][destination - 'A'] = std::min(Young_AdjMatrix[source - 'A'][destination - 'A'], weight);
				if (bidirectionalness == 'B')
					Young_AdjMatrix[destination - 'A'][source - 'A'] = std::min(Young_AdjMatrix[destination - 'A'][source - 'A'], weight);
			}
			else
			{
				Mature_AdjMatrix[source - 'A'][destination - 'A'] = std::min(Mature_AdjMatrix[source - 'A'][destination - 'A'], weight);
				if (bidirectionalness == 'B')
					Mature_AdjMatrix[destination - 'A'][source - 'A'] = std::min(Mature_AdjMatrix[destination - 'A'][source - 'A'], weight);
			}
		}
		char me_starting_position, prof_miguel_starting_position;
		scanf("\n%c %c", &me_starting_position, &prof_miguel_starting_position);
		//Floyd-Warshall, since graph size is small, and its significantly easier to implement FW, than Dijkstra or Bellman-Ford
		for (int k = 0; k < 26; k++)
		{
			for (int i = 0; i < 26; i++)
			{
				for (int j = 0; j < 26; j++)
				{
					Young_AdjMatrix[i][j] = std::min(Young_AdjMatrix[i][j], Young_AdjMatrix[i][k] + Young_AdjMatrix[k][j]);
					Mature_AdjMatrix[i][j] = std::min(Mature_AdjMatrix[i][j], Mature_AdjMatrix[i][k] + Mature_AdjMatrix[k][j]);
				}
			}
		}
		//check for all vertices
		int result_weight = INF;
		std::vector<char> result_vertex;
		for (int i = 0; i < 26; i++)
		{
			if (result_weight > Young_AdjMatrix[me_starting_position - 'A'][i] + Mature_AdjMatrix[prof_miguel_starting_position - 'A'][i])
			{
				result_weight = Young_AdjMatrix[me_starting_position - 'A'][i] + Mature_AdjMatrix[prof_miguel_starting_position - 'A'][i];
				result_vertex = {static_cast<char>(i + 'A')};
			}
			else if (result_weight == Young_AdjMatrix[me_starting_position - 'A'][i] + Mature_AdjMatrix[prof_miguel_starting_position - 'A'][i])
			{
				result_vertex.push_back(static_cast<char>(i + 'A'));
			}
		}
		if (result_weight == INF)
		{
			printf("You will never meet.\n");
		}
		else
		{
			printf("%d", result_weight);
			for (char vertex : result_vertex)
			{
				printf(" %c", vertex);
			}
			printf("\n");
		}
		scanf("%d", &N);
	}
}