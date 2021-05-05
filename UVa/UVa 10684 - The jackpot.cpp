#include <iostream>
#include <vector>

int main()
{
    int N;
    scanf("%d", &N);
    while (N != 0)
    {
        int sum = 0;
        int answer = 0;
        for (int i = 0; i < N; i++)
        {
            int bet;
            scanf("%d", &bet);
            sum += bet;
            answer = std::max(answer, sum);
            if (sum < 0)
                sum = 0;
        }
        if (answer == 0)
            printf("Losing streak.\n");
        else
            printf("The maximum winning streak is %d.\n", answer);
        scanf("%d", &N);
    }
}