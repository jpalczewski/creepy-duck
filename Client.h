#pragma once
#include "BufferUser.h"

template<class T>
class Client : public BufferUser<T>
{
private:
	int n_;
	int k_;

	virtual void work() override;

public:
	explicit Client(int n, int k)
		:  n_(n), k_(k)
	{
	}
};

template <class T>
void Client<T>::work()
{
	int numOfElem = n_*k_;
	T ret;

	while(--numOfElem>=0)
	{
		ret = BufferUser<T>::Buffer_->pop();
		std::cout << "[Client] got " << ret << std::endl;
	}
}
