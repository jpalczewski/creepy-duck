#pragma once
#include <exception>
#include <string>
struct Values
{
	int n, m, k;

	Values(int argc, char** argv)
	{
		if (argc != 4)
			throw std::exception();
		n = std::stoi(argv[1]);
		m = std::stoi(argv[2]);
		k = std::stoi(argv[3]);

		if (n < 1 || m < 1 || k < 1)
			throw std::exception();
	}
};