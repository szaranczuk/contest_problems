//based on https://en.wikipedia.org/wiki/Legendre%27s_formula
//since floor(51/29) = 1, the largest power of prime that is equal or exceeds 29, and divides 51!, must have exponent not greater than 1
//and for sure, if something doesnt divide n!, it doesnt divide binomial(n, k) as well (cause its n! div by some integer)
//so we need to check only primes up to 23

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>


const int N = 51;

std::vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};
std::set<long long> distinct_squarefree_numbers;

bool isSquareFree(long long number)
{
	for (long long prime : primes)
	{
		if (number % (prime * prime) == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	std::vector<std::vector<long long>> binomial;
	binomial.resize(N);
	for (int i = 0; i < N; i++)
	{
		binomial[i].resize(N);
	}
	long long result = 0;
	for (int i = 0; i < N; i++)
	{
		binomial[i][0] = 1;
		for (int j = 1; j <= i; j++)
		{
			binomial[i][j] = binomial[i - 1][j] + binomial[i - 1][j - 1];
			if (isSquareFree(binomial[i][j]) && distinct_squarefree_numbers.find(binomial[i][j]) == distinct_squarefree_numbers.end())
			{
				result += binomial[i][j];
				distinct_squarefree_numbers.insert(binomial[i][j]);
			}
		}
	}
	std::cout << result << '\n';
}