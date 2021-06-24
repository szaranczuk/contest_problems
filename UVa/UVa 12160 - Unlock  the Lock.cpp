#include <iostream>
#include <vector>
#include <queue>

int L, U, R;

const int INF = 1000000001;

std::vector<std::vector<int>> Adj;
std::vector<int> buttons;
std::vector<int> distance;
std::vector<bool> wasVertexVisited;


void BFS(int source)
{
	std::queue<int> BFS_queue;
	BFS_queue.push(source);
	distance[source] = 0;
	wasVertexVisited[source] = true;
	while (!BFS_queue.empty())
	{
		int vertex = BFS_queue.front();
		BFS_queue.pop();
		for (int adjacent : Adj[vertex])
		{
			if (!wasVertexVisited[adjacent])
			{
				wasVertexVisited[adjacent] = true;
				distance[adjacent] = distance[vertex] + 1;
				BFS_queue.push(adjacent);
			}
		}
	}
}

int main()
{
	scanf("%d %d %d", &L, &U, &R);
	int test_couter = 0;
	while (L != 0 || U != 0 || R != 0)
	{
		test_couter++;
		buttons.clear();
		Adj.clear();
		Adj.resize(10000);
		distance.clear();
		distance.assign(10000, INF);
		wasVertexVisited.clear();
		wasVertexVisited.assign(10000, false);
		for (int i = 0; i < R; i++)
		{
			int button;
			scanf("%d", &button);
			buttons.push_back(button);
		}
		for (int i = 0; i < 10000; i++)
		{
			for (int button : buttons)
			{
				Adj[i].push_back((i + button) % 10000);
			}
		}
		BFS(L);
		int result = distance[U];
		printf("Case %d: ", test_couter);
		if (result >= INF)
		{
			printf("Permanently Locked\n");
		}
		else
		{
			printf("%d\n", result);
		}
		scanf("%d %d %d", &L, &U, &R);
	}
}