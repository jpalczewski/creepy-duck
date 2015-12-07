#pragma once
#include "Buffer.h"
#include "LogggingUtility.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>



template <class T>
class BufferUser
{
protected:
	using bufptr = std::shared_ptr<Buffer<T> >;
	
	LoggingUtility that;

	virtual void work() = 0;
	void work_wrapper();

public:
	explicit BufferUser(std::string who);
	std::thread Spawn();
	virtual ~BufferUser();

	static bufptr Buffer_;
	static std::function<std::string(T)> Descriptor;
};

template <class T>
void BufferUser<T>::work_wrapper()
{
	that.update(std::this_thread::get_id());
	work();
}

template <class T>
BufferUser<T>::BufferUser(std::string who) : that(who)
{

}

template <class T>
std::thread BufferUser<T>::Spawn()
{
	return std::thread([=] { work_wrapper(); });
}

template <class T>
BufferUser<T>::~BufferUser()
{

}

template<class T>
std::shared_ptr<Buffer<T> > BufferUser<T>::Buffer_ = nullptr;

template<class T>
std::function<std::string(T)> BufferUser<T>::Descriptor = std::function<std::string(T)>();