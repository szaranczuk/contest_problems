#include <iostream>

using namespace std;

int main()
{
    int N;
    scanf("%d", &N);
    while (N != 0)
    {
        bool isItFirst = true;
        bool isSequenceEmpty = true;
        for (int i = 0; i < N; i++)
        {
            int number;
            scanf("%d", &number);
            if (number != 0)
            {
                isSequenceEmpty = false;
                if (isItFirst)
                {
                    printf("%d", number);
                    isItFirst = false;
                }
                else
                    printf(" %d", number);
            }
        }
        if (isSequenceEmpty)
            printf("0");
        printf("\n");
        scanf("%d", &N);
    }
    return 0;
}
