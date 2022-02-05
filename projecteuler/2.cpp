#include <iostream>

const int limit = 4000000;

int main()
{
	int fib1 = 1;
	int fib2 = 1;
	int result = 0;
	while (fib1 + fib2 < limit)
	{
		int tmp = fib1 + fib2;
		if (tmp % 2 == 0)
			result += tmp;
		fib1 = fib2;
		fib2 = tmp;
	}
	std::cout << result << '\n';
}