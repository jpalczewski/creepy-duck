#include "Client.h"
#include "Producer.h"
#include "Values.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>



int main(int argc, char **argv)
{
	std::cout << "Client & producers problem, monitor version" << std::endl;

	try
	{
		//simple parser n: number of producers, m: buffer size, k: number which producers will produce.
		Values val(argc, argv);

		//Variables related with thread-managing. 
		std::vector<std::thread> tab;
		std::vector< std::unique_ptr< BufferUser<int>>> pool;

		//Variables realted with generating random numbers.
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 10);

		//Lets make a bind to ease our lives:
		auto magic = std::bind(distribution, generator);


		//Setting environment - shared buffer and function which generate numbers.
		BufferUser<int>::Buffer_ = std::make_shared<Buffer<int> >(val.m);
		Producer<int>::Function = magic;


		pool.push_back(std::make_unique<Client<int>>(val.n, val.k));

		for (auto i = 0; i < val.n; ++i)
			pool.push_back(std::make_unique<Producer<int>>(i, val.k));

		for (auto &bu : pool) tab.push_back(bu->Spawn());	//from objects to thread
		for (auto &j : tab) j.join();						//waiting whether objects compile.
	}
	catch(...)
	{
		std::cout << "exception catch, exiting..." << std::endl;
		return 1;
	}


	return 0;
}
