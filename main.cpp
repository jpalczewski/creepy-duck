#include "Client.h"
#include "Producer.h"
#include "Values.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <sstream>
#include <mutex>
std::mutex desc_mutex;

std::string desc(int j)
{
	std::lock_guard<std::mutex> guard(desc_mutex);

	std::stringstream ss;
	ss << j;
	return ss.str();
}

int main(int argc, char **argv)
{
	std::cout << "Client & producers problem, monitor version" << std::endl;

	try
	{
		//simple parser n: number of producers, m: buffer size, k: number which producers will produce.
		Values val(argc, argv);

		//Variables related with thread-managing. 
		std::vector<std::thread> tab;
		std::vector< std::shared_ptr< BufferUser<int>>> pool;

		//Variables realted with generating random numbers.
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 10);

		//Lets make a bind to ease our lives:
		auto magic = std::bind(distribution, generator);


		//Setting environment - shared buffer and function which generate numbers.
		BufferUser<int>::Buffer_ = std::make_shared<Buffer<int>>(val.m);
		BufferUser<int>::Descriptor = desc;
		Producer<int>::Function = magic;

		//Simplifying time.
		pool.push_back(std::make_shared<Client<int>>(val.n, val.k));

		for (auto i = 0; i < val.n; ++i)
			pool.push_back(std::make_shared<Producer<int>>(i, val.k));


		auto Spawner = [&](auto i) { tab.push_back(i->Spawn()); };
		auto Waiter = std::bind(&std::thread::join, std::placeholders::_1);
		
		std::for_each(pool.begin(), pool.end(), Spawner);
		std::for_each(tab.begin(), tab.end(), Waiter);

	}
	catch(...)
	{
		std::cout << "exception catch, exiting..." << std::endl;
		return 1;
	}

	return 0;
}
