#include "Client.h"
#include "Producer.h"
#include <vector>
#include <string>
#include <iostream>


int simple_random()
{
	return 42;
}

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
int main(int argc, char **argv)
{
	std::cout << "Client & producers problem, monitor version" << std::endl;

	try
	{
		Values val(argc, argv);
		std::vector<std::thread> tab;
		std::vector <std::auto_ptr<Producer<int> > > producers;
		std::shared_ptr<Buffer<int> > buf = std::make_shared<Buffer<int> >(val.m);

		BufferUser<int>::Buffer_ = buf;
		
		tab.push_back(Client<int>(val.n, val.k).Spawn());

		for (auto i = 0; i < val.n; ++i)
			tab.push_back(Producer<int>(i, val.k, simple_random).Spawn());

		for (auto &j : tab)
			j.join();
	}
	catch(...)
	{
		std::cout << "exception catch, exiting..." << std::endl;
		return 1;
	}


	return 0;
}
