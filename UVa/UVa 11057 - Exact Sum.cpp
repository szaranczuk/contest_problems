#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int INF = 1000000001;

int main()
{
    int N;
    while (scanf("%d", &N) == 1)
    {
        std::vector<int> books_prices;
        for (int i = 0; i < N; i++)
        {
            int price;
            scanf("%d", &price);
            books_prices.push_back(price);
        }
        std::sort(books_prices.begin(), books_prices.end());
        int budget;
        scanf("%d", &budget);
        int first_result = INF;
        int second_result = -INF;
        for (int i = 0; i < books_prices.size(); i++)
        {
            int first_book_price = books_prices[i];
            int second_book_price = budget - first_book_price;
            if (std::abs(first_book_price - second_book_price) < std::abs(first_result - second_result))
            {
                if (first_book_price == second_book_price)
                {
                    auto search_result = std::equal_range(books_prices.begin(), books_prices.end(), second_book_price);
                    if (search_result.second - search_result.first >= 2)
                    {
                        first_result = first_book_price;
                        second_result = second_book_price;
                    }
                }
                else if (std::binary_search(books_prices.begin(), books_prices.end(), second_book_price))
                {
                    first_result = first_book_price;
                    second_result = second_book_price;
                }
            }
        }
        int final_first_result = std::min(first_result, second_result);
        int final_second_result = std::max(first_result, second_result);
        printf("Peter should buy books whose prices are %d and %d.\n\n", final_first_result, final_second_result);
    }
    return 0;
}
