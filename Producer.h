#pragma once
#include "BufferUser.h"
#include <functional>

template<class T>
class Producer : public BufferUser<T>
{
	using tell = BufferUser<T>;

	int id_;
	int k_;
	
	virtual void work() override;

public:
	explicit Producer(int id, int k) : BufferUser<T>("PRODUCER"), id_(id), k_(k) { };
	static std::function<T()> Function;

};

template <class T>
void Producer<T>::work()
{
	T item;
	tell::that("Entering work()");
	
	while(--k_ >= 0)
	{
		item = Function();
		tell::that("Producing...");
		std::this_thread::sleep_for(std::chrono::seconds(1));

		tell::that("Finished producing(" + BufferUser<T>::Descriptor(item) +  ") - pushing into buffer");
		BufferUser<T>::Buffer_->push(item);
		
		tell::that("Item pushed!");
	}

	tell::that("Exiting work()");
}


template<class T>
std::function<T()> Producer<T>::Function = std::function<T()>();