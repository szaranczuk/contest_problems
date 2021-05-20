#include <iostream>
#include <vector>
#include <cmath>

const double EPSILON = 0.000000001;

const int MAX_INT = 1000000001;

struct eCoin
{
    int convenctional_value;
    int IT_value;
};

std::vector<eCoin> nominals;
std::vector<std::vector<std::vector<long long>>> memotable;

int m, S;

long long findResult(int index, int conventional_value_sum, int IT_value_sum)
{
    if (index == nominals.size())
    {
        return MAX_INT;
    }
    double emodulus = std::sqrt(conventional_value_sum * conventional_value_sum + IT_value_sum * IT_value_sum);
    if (S - emodulus < -EPSILON)
        return MAX_INT;
    int ronunded_modulus = std::round(emodulus);
    if (std::abs(static_cast<double>(ronunded_modulus) - emodulus) < EPSILON)
    {
        if (ronunded_modulus == S)
        {
            return 0;
        }
    }
    if (memotable[index][conventional_value_sum][IT_value_sum] != -1)
    {
        return memotable[index][conventional_value_sum][IT_value_sum];
    }
    int result = std::min(1 + findResult(index, conventional_value_sum + nominals[index].convenctional_value, IT_value_sum + nominals[index].IT_value), findResult(index + 1, conventional_value_sum, IT_value_sum));
    memotable[index][conventional_value_sum][IT_value_sum] = result;
    return result;

}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    for (int i = 0; i < test_cases; i++)
    {
        scanf("%d %d", &m, &S);
        for (int i = 0; i < m; i++)
        {
            int conventional_value, IT_value;
            scanf("%d %d", &conventional_value, &IT_value);
            nominals.push_back({conventional_value, IT_value});
        }
        memotable.resize(m);
        for (int i = 0; i < m; i++)
        {
            memotable[i].resize(400);
            for (int j = 0; j < 400; j++)
            {
                memotable[i][j].resize(400);
                for (int k = 0; k < 400; k++)
                {
                    memotable[i][j][k] = -1;
                }
            }
        }
        int result = findResult(0, 0, 0);
        if (result >= MAX_INT)
            printf("not possible\n");
        else
            printf("%d\n", result);
        nominals.erase(nominals.begin(), nominals.end());
    }
}