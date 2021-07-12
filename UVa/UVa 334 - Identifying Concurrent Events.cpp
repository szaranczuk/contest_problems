#include <iostream>
#include <vector>
#include <map>
#include <string>

int main()
{
	int NE;
	std::cin >> NE;
	int test_counter = 0;
	while (NE != 0)
	{
		test_counter++;
		std::map<std::string, int> computation_indicies;
		std::vector<std::string> computation_names;
		std::vector<std::vector<int>> AdjMatrix;
		AdjMatrix.resize(201);
		for (int i = 0; i < 201; i++)
		{
			AdjMatrix[i].assign(201, 0);
		}
		int free_index = 0;
		for (int i = 0; i < NE; i++)
		{
			int NE_i;
			std::cin >> NE_i;
			std::vector<int> vertices;
			//read all computations in one sequence
			for (int i = 0; i < NE_i; i++)
			{
				std::string a;
				std::cin >> a;
				if (computation_indicies.find(a) == computation_indicies.end())
				{
					computation_indicies.insert({a, free_index});
					computation_names.push_back(a);
					vertices.push_back(free_index);
					free_index++;
				}
				else
				{
					int index = computation_indicies[a];
					vertices.push_back(index);
				}
			}
			//ith computation in sequence is predecessor to the ith + 1
			for (int i = 0; i < NE_i - 1; i++)
			{
				AdjMatrix[vertices[i]][vertices[i + 1]] = 1;
			}
		}
		int NM;
		std::cin >> NM;
		for (int i = 0; i < NM; i++)
		{
			std::string a, b;
			std::cin >> a >> b;
			int a_index, b_index;
			if (computation_indicies.find(a) == computation_indicies.end())
			{
				computation_indicies.insert({a, free_index});
				computation_names.push_back(a);
				a_index = free_index;
				free_index++;
			}
			else
			{
				a_index = computation_indicies[a];
			}
			if (computation_indicies.find(b) == computation_indicies.end())
			{
				computation_indicies.insert({b, free_index});
				computation_names.push_back(b);
				b_index = free_index;
				free_index++;
			}
			else
			{
				b_index = computation_indicies[b];
			}
			AdjMatrix[a_index][b_index] = 1;
		}
		//Just Floyd-Warshall to check if paths between all vertices exists (find transitive closure)
		for (int k = 0; k < free_index; k++)
		{
			for (int i = 0; i < free_index; i++)
			{
				for (int j = 0; j < free_index; j++)
				{
					AdjMatrix[i][j] |= (AdjMatrix[i][k] & AdjMatrix[k][j]);
				}
			}
		}
		//Check for all pairs of vertices if path exists (from i to j to check if i is precedessor of j, and vice versa)
		std::vector<std::pair<int, int>> concurrent_events;
		for (int i = 0; i < free_index - 1; i++)
		{
			for (int j = i + 1; j < free_index; j++)
			{
				if (AdjMatrix[i][j] == 0 && AdjMatrix[j][i] == 0)
				{
					concurrent_events.push_back({i, j});
				}
			}
		}
		std::cout << "Case " << test_counter << ", ";
		if (concurrent_events.size() == 0)
		{
			std::cout << "no concurrent events.\n";
		}
		else
		{
			std::cout << concurrent_events.size() << " concurrent events:\n";
			std::cout << "(" << computation_names[concurrent_events[0].first] << "," << computation_names[concurrent_events[0].second] << ") ";
			if (concurrent_events.size() > 1)
			{
				std::cout << "(" << computation_names[concurrent_events[1].first] << "," << computation_names[concurrent_events[1].second] << ") ";
			}
			std::cout << "\n";
		}
		std::cin >> NE;
	}
}