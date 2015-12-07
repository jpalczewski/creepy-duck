#pragma once
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
std::mutex mtx;



class LoggingUtility
{
	std::string whoami;
	std::thread::id thread_id;

	public:
		explicit LoggingUtility(std::string who) : whoami(who), thread_id() { };
		void update(std::thread::id tid) { thread_id = tid;  }
		void operator() (std::string str) const
		{
			std::lock_guard<std::mutex> guard(mtx);

			std::cout << "[" << whoami << " @ " << thread_id << " ] " << str << std::endl;
		}
};
