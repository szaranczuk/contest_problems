#include <iostream>
#include <vector>
#include <deque>
#include <queue>

int number_of_variables;

enum vertex_state
{
    UNVISITED,
    VISITED,
    COMPLETED
};

std::vector<std::vector<int>> Adj;
std::vector<bool> wasVariable;
std::vector<std::string> results;
std::vector<vertex_state> vertices_states;
std::vector<int> indegree;

bool isGraphDAG = true;

void DFS(int vertex)
{
    if (vertices_states[vertex] == COMPLETED)
    {
        return;
    }
    if (vertices_states[vertex] == VISITED)
    {
        isGraphDAG = false;
        return;
    }
    vertices_states[vertex] = VISITED;
    for (int child : Adj[vertex])
    {
        indegree[child]++;
        DFS(child);
        if (!isGraphDAG)
        {
            return;
        }
    }
    vertices_states[vertex] = COMPLETED;
}

void checkIfGraphIsDag()
{
    for (int i = 0; i < 26; i++)
    {
        if (wasVariable[i] && vertices_states[i] == UNVISITED)
        {
            DFS(i);
        }
        if (!isGraphDAG)
        {
            return;
        }
    }
}

void printPath(std::deque<int> path)
{
    printf("%c", path.front() + 'A');
    path.pop_front();
    while (!path.empty())
    {
        printf(" %c", path.front() + 'A');
        path.pop_front();
    }
    printf("\n");
}

void findAllTopologicalSorts(std::deque<int> &path)
{
    for (int i = 0; i < 26; i++)
    {
        if (wasVariable[i] && indegree[i] == 0 && vertices_states[i] == UNVISITED)
        {
            for (int j = 0; j < Adj[i].size(); j++)
            {
                indegree[Adj[i][j]]--;
            }
            path.push_back(i);
            vertices_states[i] = VISITED;
            if (path.size() == number_of_variables)
            {
                printPath(path);
            }
            else
            {
                findAllTopologicalSorts(path);
            }
            path.pop_back();
            for (int j = 0; j < Adj[i].size(); j++)
            {
                indegree[Adj[i][j]]++;
            }
            vertices_states[i] = UNVISITED;
        }
    }
}

int main()
{
    int test_cases;
    scanf("%d\n", &test_cases);
    Adj.resize(26);
    wasVariable.resize(26);
    vertices_states.resize(26);
    indegree.resize(26);
    for (int i = 0; i < test_cases; i++)
    {
        number_of_variables = 0;
        isGraphDAG = true;
        for (int i = 0; i < 26; i++)
        {
            Adj[i] = {};
            wasVariable[i] = false;
            vertices_states[i] = UNVISITED;
            indegree[i] = 0;
        }
        scanf("\n");
        char variable;
        scanf("%c", &variable);
        while (variable != '\n')
        {
            if (variable != ' ')
            {
                wasVariable[variable - 'A'] = true;
                number_of_variables++;
            }
            scanf("%c", &variable);
        }
        char A, B;
        scanf("%c", &A);
        while (A != '\n')
        {
            if (A != ' ')
            {
                scanf("<%c", &B);
                Adj[A - 'A'].push_back(B - 'A');
            }
            scanf("%c", &A);
        }
        checkIfGraphIsDag();
        if (!isGraphDAG)
        {
            printf("NO\n");
        }
        else
        {
            for (int i = 0; i < vertices_states.size(); i++)
            {
                vertices_states[i] = UNVISITED;
            }
            std::deque<int> path;
            findAllTopologicalSorts(path);
        }
        if (i != test_cases - 1)
            printf("\n");
    }
}