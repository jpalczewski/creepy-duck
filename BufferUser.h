#pragma once
#include "Buffer.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>



template <class T>
class BufferUser
{
protected:
	using bufptr = std::shared_ptr<Buffer<T> >;
	
	


	virtual void work() = 0;
public:
	explicit BufferUser();
	std::thread Spawn();
	virtual ~BufferUser();

	static bufptr Buffer;
};

template <class T>
BufferUser<T>::BufferUser()
{
}

template <class T>
std::thread BufferUser<T>::Spawn()
{
	return std::thread(&BufferUser::Spawn, this);
}

template <class T>
BufferUser<T>::~BufferUser()
{

}

template<class T>
std::shared_ptr<Buffer<T> > BufferUser<T>::Buffer = nullptr;