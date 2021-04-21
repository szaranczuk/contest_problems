#include <iostream>
#include <vector>
#include <algorithm>

//this function is hack to check all possible (towers_to_build)-combinations, passing through all bit combination,
//we can pass through all towers combination (considering 1 as "is", and 0 as "is not"), all we need is just check if number of "1" bits
//is equal to towers_to_build
int count_bits(int number)
{
    int number_of_1_bits = 0;
    while (number != 0)
    {
        number_of_1_bits++;
        number -= number & (-number); //subtracting most significant bit, beacause -n is ~n + 1
    }
    return number_of_1_bits;
}

int main()
{
    int n;
    std::cin >> n;
    int test_case = 1;
    while (n > 0)
    {
        //data declaration and initialization
        int towers_to_build;
        std::cin >> towers_to_build;
        std::vector<int> tower_coverage_list;
        for (int i = 0; i < n; i++)
        {
            int number_of_cusotmers;
            std::cin >> number_of_cusotmers;
            tower_coverage_list.push_back(number_of_cusotmers);
        }
        int m;
        std::cin >> m;
        std::vector<std::vector<int>> intersection_list;
        for (int i = 0; i < m; i++)
        {
            int t;
            std::cin >> t;
            std::vector<int> intersecting_towers;
            for (int j = 0; j < t + 1; j++)
            {
                int value;
                std::cin >> value;
                intersecting_towers.push_back(value);
            }
            intersection_list.push_back(intersecting_towers);
        }

        //the main part
        int max_result = 0;
        std::vector<int> result_combination;
        for (int i = 0; i < (1 << n); i++)
        {
            if (count_bits(i) == towers_to_build) //ad. begin of file
            {
                int combination_bitmask = i;
                std::vector<int> combination_of_towers;
                int index_of_tower = 0;
                while (combination_bitmask > 0)
                {
                    if (combination_bitmask & 1 == 1)
                        combination_of_towers.push_back(index_of_tower);
                    combination_bitmask = combination_bitmask >> 1;
                    index_of_tower++;
                }
                int result = 0;
                for (int tower : combination_of_towers)
                    result += tower_coverage_list[tower];
                for (auto intersection : intersection_list)
                {
                    int counter = 0;
                    for (int tower = 0; tower < intersection.size() - 1; tower++) //last value is number of occupants in region
                    {
                        if (std::binary_search(combination_of_towers.begin(), combination_of_towers.end(), intersection[tower] - 1))
                        {
                            counter++;
                        }
                    }
                    if (counter >= 2)
                    {
                        result -= (intersection[intersection.size() - 1]) * (counter - 1); //if intersects more than once, we must subtract value multiple times
                    }
                }
                if (result > max_result)
                {
                    max_result = result;
                    result_combination = combination_of_towers;
                }
            }
        }
        std::cout << "Case Number  " << test_case << "\nNumber of Customers: " << max_result << "\nLocations recommended: ";
        for (int i = 0; i < towers_to_build - 1; i++)
        {
            std::cout << result_combination[i] + 1 << " ";
        }
        std::cout << result_combination[towers_to_build - 1] + 1 << "\n\n";
        test_case++;
        std::cin >> n;
    }
    return 0;
}
