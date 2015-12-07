#pragma once
#include "monitor.h"
#include <queue>
template<class T>
class Buffer
{
	Monitor m_;
	std::queue<T> buf;
	Condition full_, empty_;
	int size_;

public:
	explicit Buffer(int size);
	void push(T e);
	T pop();
	~Buffer();
};

template <class T>
Buffer<T>::Buffer(int size) : size_(size)
{
}

template <class T>
void Buffer<T>::push(T e)
{
	m_.enter();
	if (buf.size() == size_)
		m_.wait(full_);

	buf.push(e);
	
	if (!buf.empty())
		m_.signal(empty_);

	m_.leave();
}

template <class T>
T Buffer<T>::pop()
{
	T elem;

	m_.enter();
	if (buf.empty())
		m_.wait(empty_);

	elem = buf.front();
	buf.pop();

	if (buf.size() == size_ - 1)
		m_.signal(full_);

	m_.leave();
	
	return elem;
}

template <class T>
Buffer<T>::~Buffer()
{
}
