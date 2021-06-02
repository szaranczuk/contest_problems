#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

int N;

std::vector<std::vector<int>> Adj;

std::vector<int> inDegree;

int main()
{
    int case_counter = 0;
    while (std::cin >> N)
    {
        case_counter++;
        Adj.erase(Adj.begin(), Adj.end());
        Adj.resize(N);
        inDegree.resize(N);
        for (int i = 0; i < N; i++)
        {
            inDegree[i] = 0;
        }
        std::map<std::string, int> beverages;
        std::vector<std::string> beverages_in_integer_representation;
        for (int i = 0; i < N; i++)
        {
            std::string beverage;
            std::cin >> beverage;
            beverages.insert({beverage, i});
            beverages_in_integer_representation.push_back(beverage);
        }
        int M;
        std::cin >> M;
        for (int i = 0; i < M; i++)
        {
            std::string a, b;
            std::cin >> a >> b;
            Adj[beverages[a]].push_back(beverages[b]);
            inDegree[beverages[b]]++;
        }
        std::priority_queue<int, std::vector<int>, std::greater<int>> result;
        for (int i = 0; i < N; i++)
        {
            if (inDegree[i] == 0)
            {
                result.push(i);
            }
        }
        std::cout << "Case #" << case_counter << ": Dilbert should drink beverages in this order: ";
        int printed_vertices_counter = 0;
        while (printed_vertices_counter != N - 1)
        {
            int vertex = result.top();
            result.pop();
            for (int child : Adj[vertex])
            {
                inDegree[child]--;
                if (inDegree[child] == 0)
                {
                    result.push(child);
                }
            }
            std::cout << beverages_in_integer_representation[vertex] << " ";
            printed_vertices_counter++;
        }
        std::cout << beverages_in_integer_representation[result.top()] << ".\n\n";
    }
}