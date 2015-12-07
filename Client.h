#pragma once
#include "BufferUser.h"

template<class T>
class Client : public BufferUser<T>
{
private:
	using tell = BufferUser<T>;

	int n_;
	int k_;

	virtual void work() override;
	
public:
	explicit Client(int n, int k) : BufferUser<T>("CLIENT"), n_(n), k_(k) { }
};

template <class T>
void Client<T>::work()
{
	tell::that("Entering work()");
	int numOfElem = n_*k_;
	T ret;

	while(--numOfElem>=0)
	{
		tell::that("Waiting for an object");
		ret = BufferUser<T>::Buffer_->pop();
		tell::that("Got " + BufferUser<T>::Descriptor(ret));
	}
	tell::that("All items received, exiting.");
}

