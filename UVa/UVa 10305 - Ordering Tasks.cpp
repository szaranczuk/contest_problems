#include <iostream>
#include <vector>

int n, m;

std::vector<std::vector<int>> Adj;

std::vector<bool> wasVertexVisited;

std::vector<int> result;

void DFS(int vertex)
{
    wasVertexVisited[vertex] = true;
    for (int child : Adj[vertex])
    {
        if (!wasVertexVisited[child])
        {
            DFS(child);
        }
    }
    result.push_back(vertex + 1);
}

void getResult()
{
    for (int i = 0; i < n; i++)
    {
        if (!wasVertexVisited[i])
        {
            DFS(i);
        }
    }
}


int main()
{
    scanf("%d %d", &n, &m);
    while (n != 0 || m != 0)
    {
        result.erase(result.begin(), result.end());
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(n);
        wasVertexVisited.resize(n);
        for (int i = 0; i < n; i++)
        {
            wasVertexVisited[i] = false;
        }
        for (int i = 0; i < m; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            Adj[a - 1].push_back(b - 1);
        }
        getResult();
        for (int i = n - 1; i > 0; i--)
        {
            printf("%d ", result[i]);
        }
        printf("%d\n", result[0]);
        scanf("%d %d", &n, &m);
    }
}