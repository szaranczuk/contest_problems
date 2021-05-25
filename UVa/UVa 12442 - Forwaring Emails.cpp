#include <iostream>
#include <vector>

std::vector<std::vector<int>> Adj;
enum vertex_state
{
    UNVISITED,
    VISITED,
    COMPLETED
};
std::vector<vertex_state> vertices_states;
std::vector<int> memotable;
std::vector<int> loop_parent;
int N;

int DFS(int vertex)
{
    vertices_states[vertex] = VISITED;
    int result = 1;
    for (int child : Adj[vertex])
    {
        if (vertices_states[child] == COMPLETED)
        {
            result += memotable[loop_parent[child]];
        }
        else if (vertices_states[child] == UNVISITED)
        {
            result += DFS(child);
            if (loop_parent[child] != child)
            {
                loop_parent[vertex] = loop_parent[child];
            }
        }
        else
        {
            loop_parent[vertex] = child;
        }
    }
    memotable[vertex] = result;
    vertices_states[vertex] = COMPLETED;
    return result;
}

int getResult()
{
    int result_index = 0;
    int result = 0;
    for (int i = 0; i < N; i++)
    {
        if (vertices_states[i] == UNVISITED)
        {
            int local_result = DFS(i);
            if (local_result > result)
            {
                result = local_result;
                result_index = i;
            }
        }
    }
    return result_index;
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        scanf("%d", &N);
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(N);
        vertices_states.resize(N);
        memotable.resize(N);
        loop_parent.resize(N);
        for (int i = 0; i < N; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            Adj[u - 1].push_back(v - 1);
            vertices_states[i] = UNVISITED;
            loop_parent[i] = i;
        }
        int result = getResult();
        printf("Case %d: %d\n", i + 1, result + 1);
    }
}