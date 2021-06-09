#include <iostream>
#include <vector>
#include <queue>

std::vector<bool> wasVertexVisited;
std::vector<std::vector<int>> Adj;

void DFS(int vertex, std::vector<int> &connected_component)
{
    wasVertexVisited[vertex] = true;
    connected_component.push_back(vertex);
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
    int v;
    scanf("%d", &v);
    while (v != 0)
    {
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(v);
        int a, b;
        scanf("%d %d", &a, &b);
        while (a != 0 || b != 0)
        {
            Adj[a - 1].push_back(b - 1);
            Adj[b - 1].push_back(a - 1);
            scanf("%d %d", &a, &b);
        }
        std::vector<int> coloring(v);
        wasVertexVisited.resize(v);
        for (int i = 0; i < v; i++)
        {
            coloring[i] = -1;
            wasVertexVisited[i] = false;
        }
        bool isGraphBipartite = true;
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
        for (auto connected_component : connected_components)
        {
            std::queue<int> BFS_queue;
            BFS_queue.push(connected_component[0]);
            coloring[connected_component[0]] = 0;
            while (!BFS_queue.empty() && isGraphBipartite)
            {
                int vertex = BFS_queue.front();
                BFS_queue.pop();
                for (int adjacent : Adj[vertex])
                {
                    if (coloring[adjacent] == coloring[vertex])
                    {
                        isGraphBipartite = false;
                        break;
                    }
                    else if (coloring[adjacent] == -1)
                    {
                        coloring[adjacent] = 1 - coloring[vertex];
                        BFS_queue.push(adjacent);
                    }
                }
            }
        }
        if (isGraphBipartite)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
        scanf("%d", &v);
    }
}