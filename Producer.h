#pragma once
#include "BufferUser.h"
#include <functional>

template<class T>
class Producer : public BufferUser<T>
{
private:
	int id_;
	int k_;
	
	virtual void work() override;
public:
	explicit Producer(int id, int k)
	: id_(id), k_(k)
	{
		
	}

	static std::function<T()> Function;

};

template <class T>
void Producer<T>::work()
{
	L("Producer::work()");
	while(--k_ >= 0)
	{
		std::cout << id_ << ", "<< std::this_thread::get_id() << "] Producing..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));

		BufferUser<T>::Buffer_->push(Function());

		std::cout << id_ << ", " << std::this_thread::get_id() << "] Produced!" << std::endl;
	}
}

template<class T>
std::function<T()> Producer<T>::Function = std::function<T()>();