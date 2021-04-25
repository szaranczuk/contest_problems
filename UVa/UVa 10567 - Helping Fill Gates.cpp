#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int INF = 1000000001;

int main()
{
    std::string candidates;
    std::cin >> candidates;
    std::vector<std::vector<int>> indices_of_char(52);
    for (int i = 0; i < candidates.size(); i++)
    {
        char candidate = candidates[i];
        if (candidate > 'Z')
            indices_of_char[candidate - 'a' + 26].push_back(i);
        else
            indices_of_char[candidate - 'A'].push_back(i);
    }
    int number_of_queries;
    std::cin >> number_of_queries;
    for (int i = 0; i < number_of_queries; i++)
    {
        std::string query;
        std::cin >> query;
        int min_index = INF;
        int max_index = -1;
        int prev_query = -1;
        for (int j = 0; j < query.size(); j++)
        {
            char candidate = query[j];
            int numeric_candiate = candidate > 'Z' ? candidate - 'a' + 26 : candidate - 'A';
            auto search_result = std::lower_bound(indices_of_char[numeric_candiate].begin(), indices_of_char[numeric_candiate].end(), prev_query + 1);
            if(search_result == indices_of_char[numeric_candiate].end())
            {
                std::cout << "Not matched\n";
                goto not_matched;
            }
            else
            {
                min_index = std::min(min_index, *search_result);
                max_index = std::max(max_index, *search_result);
                prev_query = *search_result;
            }
        }
        std::cout << "Matched " << min_index << ' ' << max_index << '\n';
        not_matched:
            continue;
    }
    return 0;
}
