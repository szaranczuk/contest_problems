//log(n^k) = k * log(n)
//log is strictly increasing function, so log(y) > log(x) implies y > x

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main()
{
	int base, exp;
	int line = 0;
	double global_max = 0.0;
	int result_line = 0;
	while(scanf("%d,%d", &base, &exp) == 2)
	{
		line++;
		double local_max = static_cast<double>(exp) * std::log2(base);
		if (local_max > global_max)
		{
			result_line = line;
			global_max = local_max;
		}
	}
	std::cout << result_line << '\n';
}