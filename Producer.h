#pragma once
#include "BufferUser.h"
#include <functional>

template<class T>
class Producer : public BufferUser<T>
{
private:
	int id_;
	int k_;
	std::function<T()> produce_;

	virtual void work() override;
public:
	explicit Producer(int id, int k, std::function<T()> produce)
		: id_(id), k_(k), produce_(produce)
	{
	}

	 
};

template <class T>
void Producer<T>::work()
{
	while(--k_ >= 0)
	{
		std::cout << id_ << ", "<< std::this_thread::get_id() << "] Producing..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));

		BufferUser<T>::Buffer_->push(produce_());

		std::cout << id_ << ", " << std::this_thread::get_id() << "] Produced!" << std::endl;
	}
}
