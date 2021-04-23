#include <iostream>
#include <vector>

const int YEAR_DURATION_IN_MONTHS = 12;

bool isSolved = false;

int s, d;

std::vector<int> month_report(YEAR_DURATION_IN_MONTHS);
std::vector<int> res;

void backtrack(int report_value, int index)
{
    if (isSolved)
        return;
    if (index >= 5 && month_report[index - 1] + month_report[index - 2] + month_report[index - 3] + month_report[index - 4] + month_report[index - 5] > 0)
        return;
    if (index == 12)
    {
        isSolved = true;
        return;
    }
    month_report[index] = report_value;
    backtrack(s, index + 1);
    backtrack(-d, index + 1);
}

int main()
{
    while(scanf("%d %d", &s, &d) == 2)
    {
        isSolved = false;
        backtrack(s, 0);
        int result = 0;
        for (int value : month_report)
            result += value;
        if (!isSolved || result <= 0)
            printf("Deficit\n");
        else
            printf("%d\n", result);
    }
    return 0;
}
