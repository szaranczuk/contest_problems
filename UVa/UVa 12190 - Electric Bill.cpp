#include <iostream>
#include <algorithm>

int main()
{
    long long A, B;
    std::cin >> A >> B;
    while (A != 0 || B != 0)
    {
        int total_consumption = 0;
        if (A - 200 < 0)
            total_consumption += A / 2;
        else
        {
            total_consumption += 100;
            A -= 200;
            if (A - 29700 < 0)
                total_consumption += A / 3;
            else
            {
                total_consumption += 9900;
                A -= 29700;
                if (A - 4950000 < 0)
                    total_consumption += A / 5;
                else
                {
                    total_consumption += 990000;
                    A -= 4950000;
                    total_consumption += A / 7;
                }
            }
        }
        long long low = 0;
        long long high = total_consumption / 2;
        long long mid = (low + high + 1) / 2;
        for (int i = 0; i < 50; i++) //because greatest total_consumption value is less than 7 * 10 ^ 9, and lg(7 * 10 ^ 9) is approximately 33
        {
            long long my_consumption = mid;
            long long neighboor_consumption = total_consumption - mid;
            long long my_bill = 0;
            long long neighboor_bill = 0;
            if (my_consumption - 100 < 0)
                my_bill += my_consumption * 2;
            else
            {
                my_bill += 200;
                my_consumption -= 100;
                if (my_consumption - 9900 < 0)
                    my_bill += my_consumption * 3;
                else
                {
                    my_bill += 29700;
                    my_consumption -= 9900;
                    if (my_consumption - 990000 < 0)
                        my_bill += my_consumption * 5;
                    else
                    {
                        my_bill += 4950000;
                        my_consumption -= 990000;
                        my_bill += my_consumption * 7;
                    }
                }
            }
            if (neighboor_consumption - 100 < 0)
                neighboor_bill += neighboor_consumption * 2;
            else
            {
                neighboor_bill += 200;
                neighboor_consumption -= 100;
                if (neighboor_consumption - 9900 < 0)
                    neighboor_bill += neighboor_consumption * 3;
                else
                {
                    neighboor_bill += 29700;
                    neighboor_consumption -= 9900;
                    if (neighboor_consumption - 990000 < 0)
                        neighboor_bill += neighboor_consumption * 5;
                    else
                    {
                        neighboor_bill += 4950000;
                        neighboor_consumption -= 990000;
                        neighboor_bill += neighboor_consumption * 7;
                    }
                }
            }
            if (neighboor_bill - my_bill == B)
            {
                std::cout << my_bill << '\n';
                break;
            }
            if (neighboor_bill - my_bill > B)
            {
                low = mid;
                mid = (low + high + 1) / 2;
            }
            else
            {
                high = mid;
                mid = (low + high + 1) / 2;
            }
        }
        std::cin >> A >> B;
    }
    return 0;
}
