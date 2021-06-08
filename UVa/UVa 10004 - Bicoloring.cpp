#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> Adj;

enum colors
{
    NULLCOLOR,
    FIRST,
    SECOND };
std::vector<colors> coloring;


int main()
{
    int n;
    scanf("%d", &n);
    while (n != 0)
    {
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(n);
        coloring.resize(n);
        for (int i = 0; i < n; i++)
        {
            coloring[i] = NULLCOLOR;
        }
        int number_of_edges;
        scanf("%d", &number_of_edges);
        for (int i = 0; i < number_of_edges; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            Adj[a].push_back(b);
            Adj[b].push_back(a);
        }
        std::queue<int> BFS_queue;
        BFS_queue.push(0);
        coloring[0] = FIRST;
        bool isItPossible = true; 
        while (!BFS_queue.empty() && isItPossible)
        {
            int node = BFS_queue.front();
            BFS_queue.pop();
            for (int adjacent_node : Adj[node])
            {
                if (coloring[adjacent_node] == coloring[node])
                {
                    isItPossible = false;
                    break;
                }
                if (coloring[adjacent_node] != NULLCOLOR)
                {
                    continue;
                }
                if (coloring[node] == FIRST)
                {
                    coloring[adjacent_node] = SECOND;
                }
                else
                {
                    coloring[adjacent_node] = FIRST;
                }
                BFS_queue.push(adjacent_node);
            }
        }
        if (isItPossible)
        {
            printf("BICOLORABLE.\n");
        }
        else
        {
            printf("NOT BICOLORABLE.\n");
        }
        scanf("%d", &n);
    }
}