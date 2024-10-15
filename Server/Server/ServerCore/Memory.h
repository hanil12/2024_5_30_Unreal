#pragma once
#include "Allocator.h"

template<typename T, typename... Args>
T* xnew(Args... args)
{
	T* memory = static_cast<T*>(xalloc(sizeof(T)));

	new(memory)T(std::forward<Args>(args)...);

	return memory;
}

template<typename T>
void xdelete(T* obj)
{
	obj->~T();
	xrelease(obj);
}