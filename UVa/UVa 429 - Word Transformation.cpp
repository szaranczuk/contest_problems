#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

std::vector<std::vector<int>> distance;
std::vector<std::vector<int>> Adj;
std::vector<bool> wasVertexVisited;

bool stringsDifferInOnlyOnePosition(const std::string &a, const std::string &b)
{
	bool stringsDiffer = false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
		{
			if (stringsDiffer)
			{
				return false;
			}
			else
			{
				stringsDiffer = true;
			}
		}
	}
	return stringsDiffer;
}

void BFS(int source)
{
	std::queue<int> BFS_queue;
	BFS_queue.push(source);
	distance[source][source] = 0;
	wasVertexVisited[source] = true;
	while (!BFS_queue.empty())
	{
		int vertex = BFS_queue.front();
		BFS_queue.pop();
		for (int adjacent : Adj[vertex])
		{
			if (!wasVertexVisited[adjacent])
			{
				BFS_queue.push(adjacent);
				distance[source][adjacent] = distance[source][vertex] + 1;
				wasVertexVisited[adjacent] = true;
			}
		}
	}
}

int main()
{
	int test_cases;
	std::cin >> test_cases;
	for (int i = 0; i < test_cases; i++)
	{
		if (i != 0)
		{
			std::cout << "\n";
		}
		std::map<std::string, int> words;
		std::vector<std::string> s_words;
		std::string word;
		std::cin >> word;
		int word_counter = 0;
		while (word != "*")
		{
			s_words.push_back(word);
			words.insert({word, word_counter});
			word_counter++;
			std::cin >> word;
		}
		Adj.clear();
		Adj.resize(words.size());
		distance.clear();
		distance.resize(words.size());
		wasVertexVisited.clear();
		wasVertexVisited.assign(words.size(), false);
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i].assign(distance.size(), -1);
		}
		for (int i = 0; i < s_words.size() - 1; i++)
		{
			for (int j = i + 1; j < s_words.size(); j++)
			{
				if (s_words[i].size() == s_words[j].size() && stringsDifferInOnlyOnePosition(s_words[i], s_words[j]))
				{
					Adj[i].push_back(j);
					Adj[j].push_back(i);
				}
			}
		}
		std::ws(std::cin);
		std::string query;
		std::getline(std::cin, query);
		while (!query.empty())
		{
			std::string a, b;
			int i = 0;
			while (query[i] != ' ')
			{
				a.push_back(query[i]);
				i++;
			}
			i++;
			while (i < query.size())
			{
				b.push_back(query[i]);
				i++;
			}
			int a_int = words[a];
			int b_int = words[b];
			if (distance[a_int][b_int] == -1)
			{
				BFS(a_int);
				wasVertexVisited.clear();
				wasVertexVisited.assign(words.size(), false);
			}
			std::cout << query << " " << distance[a_int][b_int] << '\n';
			std::getline(std::cin, query);
		}
	}
}