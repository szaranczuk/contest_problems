#include <iostream>
#include <vector>

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        int N, M, K;
        scanf("%d %d %d", &N, &M, &K);
        std::vector<std::vector<int>> plot_prices(N);
        std::vector<std::vector<int>> sum_of_prices(N);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                int price;
                scanf("%d", &price);
                plot_prices[i].push_back(price);
                sum_of_prices[i].push_back(price);
                if (i - 1 >= 0)
                    sum_of_prices[i][j] += sum_of_prices[i - 1][j];
                if (j - 1 >= 0)
                    sum_of_prices[i][j] += sum_of_prices[i][j - 1];
                if (i - 1 >= 0 && j - 1 >= 0)
                    sum_of_prices[i][j] -= sum_of_prices[i - 1][j - 1];
            }
        }
        int max_plot_size = 0;
        int max_plot_size_price = 0;
        for (int left = 0; left < N; left++)
        {
            for (int right = left; right < N; right++)
            {
                int local_max_plot_price = 0;
                int local_max_plot_size = 0;
                int upper_k = 0;
                for (int k = 0; k < M; k++)
                {
                    local_max_plot_price += sum_of_prices[right][k];
                    if (left - 1 >= 0)
                    {
                        local_max_plot_price -= sum_of_prices[left - 1][k];
                    }
                    if (k - 1 >= 0)
                    {
                        local_max_plot_price -= sum_of_prices[right][k - 1];
                    }
                    if (left - 1 >= 0 && k - 1 >= 0)
                    {
                        local_max_plot_price += sum_of_prices[left - 1][k - 1];
                    }
                    local_max_plot_size += right - left + 1;
                    while (local_max_plot_price > K)
                    {
                        if (upper_k > k)
                            goto chuj_z_makiem; //break outer loop when John can't buy just 1D strip of plots
                        local_max_plot_size -= right - left + 1;
                        local_max_plot_price -= sum_of_prices[right][upper_k];
                        if (left - 1 >= 0)
                            local_max_plot_price += sum_of_prices[left - 1][upper_k];
                        if (upper_k - 1 >= 0)
                            local_max_plot_price += sum_of_prices[right][upper_k - 1];
                        if (left - 1 >= 0 && upper_k - 1 >= 0)
                            local_max_plot_price -= sum_of_prices[left - 1][upper_k - 1];
                        upper_k++;
                    }
                    if (local_max_plot_size > max_plot_size)
                    {
                        max_plot_size = local_max_plot_size;
                        max_plot_size_price = local_max_plot_price;
                    }
                    else if (local_max_plot_size == max_plot_size)
                    {
                        max_plot_size_price = std::min(max_plot_size_price, local_max_plot_price);
                    }
                    if (false)
                    {
                        chuj_z_makiem:
                            break;
                    }
                }
            }
        }
        printf("Case #%d: %d %d\n", i + 1, max_plot_size, max_plot_size_price);
    }
    return 0;
}