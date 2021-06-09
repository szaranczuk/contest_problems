#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> Adj;
std::vector<int> wasVertexVisited;

const int INF = 1000000001;

void DFS(int vertex, std::vector<int>& connected_component)
{
    connected_component.push_back(vertex);
    wasVertexVisited[vertex] = true;
    for (int adjacent : Adj[vertex])
    {
        if (!wasVertexVisited[adjacent])
        {
            DFS(adjacent, connected_component);
        }
    }
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int v, e;
        scanf("%d %d", &v, &e);
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(v);
        for (int i = 0; i < e; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            Adj[a].push_back(b);
            Adj[b].push_back(a);
        }
        //divide graph into connected components
        wasVertexVisited.resize(v);
        for (int i = 0; i < v; i++)
        {
            wasVertexVisited[i] = false;
        }
        std::vector<std::vector<int>> connected_components;
        for (int i = 0; i < v; i++)
        {
            if (!wasVertexVisited[i])
            {
                std::vector<int> connected_component;
                DFS(i, connected_component);
                connected_components.push_back(connected_component);
            }
        }
        bool isGraphBipartite = true;
        int result = 0;
        std::vector<int> colors(v);
        for (int i = 0; i < v; i++)
        {
            colors[i] = -1;
        }
        for (auto connected_component : connected_components)
        {
            std::vector<int> numbers_of_colors(2);
            numbers_of_colors[0] = numbers_of_colors[1] = 0;
            std::queue<int> BFS_queue;
            BFS_queue.push(connected_component[0]);
            colors[connected_component[0]] = 0;
            numbers_of_colors[0]++;
            while(!BFS_queue.empty() && isGraphBipartite)
            {
                int vertex = BFS_queue.front();
                BFS_queue.pop();
                for (int adjacent : Adj[vertex])
                {
                    if (colors[adjacent] == colors[vertex])
                    {
                        isGraphBipartite = false;
                        break;
                    }
                    else if (colors[adjacent] == -1)
                    {
                        colors[adjacent] = 1 - colors[vertex];
                        BFS_queue.push(adjacent);
                        numbers_of_colors[colors[adjacent]]++;
                    }
                }
            }
            result += std::max(1, std::min(numbers_of_colors[0], numbers_of_colors[1])); //since every connected component needs at least one guard
        }
        if (isGraphBipartite)
        {
            printf("%d\n", result);
        }
        else
        {
            printf("-1\n");
        }
    }
}