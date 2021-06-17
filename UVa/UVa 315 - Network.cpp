#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> Adj;
std::vector<int> dfs_num;
std::vector<int> dfs_low;
std::vector<int> dfs_parent;
std::vector<bool> wasVertexVisited;
std::vector<bool> isVertexArtPoint;
std::vector<int> connected_components;

int dfs_index;
int rootChildren;
int N;
int dfsRoot;

void DFS(int vertex)
{
    wasVertexVisited[vertex] = true;
    for (int adjacent : Adj[vertex])
    {
        if (!wasVertexVisited[adjacent])
        {
            DFS(adjacent);
        }
    }
}

void findConnectedComponents()
{
    for (int i = 0; i < N; i++)
    {
        if (!wasVertexVisited[i])
        {
            connected_components.push_back(i);
            DFS(i);
        }
    }
}

void findArticulationPoints(int vertex)
{
    wasVertexVisited[vertex] = true;
    dfs_num[vertex] = dfs_low[vertex] = dfs_index;
    dfs_index++;
    for (int adjacent : Adj[vertex])
    {
        if (wasVertexVisited[adjacent])
        {
            if (dfs_parent[adjacent] != vertex)
            {
                dfs_low[vertex] = std::min(dfs_num[adjacent], dfs_low[vertex]);
            }
        }
        else
        {
            dfs_parent[adjacent] = vertex;
            if (vertex == dfsRoot)
            {
                rootChildren++;
            }
            findArticulationPoints(adjacent);
            if (dfs_low[adjacent] >= dfs_num[vertex] && (vertex != dfsRoot || rootChildren >= 2))
            {
                isVertexArtPoint[vertex] = true;
            }
            dfs_low[vertex] = std::min(dfs_low[adjacent], dfs_low[vertex]);
        }
    }
}

int main()
{
    scanf("%d", &N);
    while (N != 0)
    {
        dfs_index = 0;
        rootChildren = 0;
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(N);
        dfs_low.erase(dfs_low.begin(), dfs_low.end());
        dfs_low.resize(N);
        dfs_num.erase(dfs_num.begin(), dfs_num.end());
        dfs_num.resize(N);
        dfs_parent.erase(dfs_parent.begin(), dfs_parent.end());
        dfs_parent.resize(N);
        wasVertexVisited.resize(N);
        isVertexArtPoint.resize(N);
        connected_components.erase(connected_components.begin(), connected_components.end());
        for (int i = 0; i < N; i++)
        {
            wasVertexVisited[i] = false;
            isVertexArtPoint[i] = false;
        }
        std::string edges;
        while (std::getline(std::cin, edges) && edges != "0")
        {
            std::stringstream ss(edges);
            int a;
            ss >> a;
            int b;
            while (ss >> b)
            {
                Adj[a - 1].push_back(b - 1);
                Adj[b - 1].push_back(a - 1);
            }
        }
        findConnectedComponents();
        for (int i = 0; i < N; i++)
        {
            wasVertexVisited[i] = false;
        }
        for (int vertex : connected_components)
        {
            dfsRoot = vertex;
            rootChildren = 0;
            findArticulationPoints(dfsRoot);
        }
        int result = 0;
        for (int i = 0; i < N; i++)
        {
            if (isVertexArtPoint[i])
            {
                result++;
            }
        }
        printf("%d\n", result);
        scanf("%d", &N);
    }
}