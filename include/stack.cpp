#ifndef stack_cpp
#define stack_cpp
#pragma once
#include <iostream>

template <typename T>
class allocator
{
protected:
	allocator(size_t size = 0);
	~allocator();
	auto swap(allocator & other) -> void;
	allocator(allocator const &) = delete;
	auto operator =(allocator const &)->allocator & = delete;
	T * ptr_;
	size_t size_;
	size_t count_;
};

template <typename T>
allocator<T>::allocator(size_t size) : ptr_((T*)(operator new(size*sizeof(T)))), size_(size), count_(0){};

template<typename T>
allocator<T>::~allocator()
{ 
	delete ptr_; 
}

template<typename T>
auto allocator<T>::swap(allocator & other)->void
{
	swap(ptr_, other.ptr_);
	swap(size_, other.size_);
	swao(count_, other.count_);
}

template <typename T>
class stack: protected allocator <T>
{
public:
	stack(); /* noexcept */
	stack(const stack&); /* strong */
	size_t count() const; /* noexcept */
	void push(T const &); /* strong */
	void pop(); /* strong */
	const T& top(); /* strong */
	~stack(); /* noexcept */
	stack& operator=(const stack&); /* strong */
	bool empty(); /* noexcept */
};

template<typename T>
T* copy_mas(const T *p1, size_t sizeLeft, size_t sizeRight)
{
	T *m_array = (T*)(operator new(sizeRight*sizeof(T)));
	try
	{ 
		std::copy(p1, p1 + sizeLeft, m_array); 
	}
	catch (...)
	{ 
		delete m_array; 
		throw; 
	}
	return m_array;
}

template <typename T>
stack<T>::stack() : allocator<T>(){};

template <typename T>
stack<T>::stack(const stack& x) : allocator<T>(x.size_)
{
	allocator<T>::ptr_ = copy_mas(x.allocator<T>::ptr_, x.allocator<T>::count_, x.allocator<T>::size_);
	allocator<T>::count_ = x.allocator<T>::count_;
};

template<typename T>
stack<T>& stack<T>::operator=(const stack& b)
{
	if (this != &b)
	{
		T *p = allocator<T>::ptr_;
		allocator<T>::ptr_ = copy_mas(b.allocator<T>::ptr_, b.allocator<T>::count_, b.allocator<T>::size_);
		delete p;
		allocator<T>::count_ = b.allocator<T>::count_;
		allocator<T>::size_ = b.allocator<T>::size_;
	}
	return *this;
}

template <typename T>
stack<T>::~stack(){}

template <typename T>
size_t stack<T>::count() const
{ 
	return allocator<T>::count_; 
}

template <typename T>
void stack<T>::push(T const &a)
{
	if (allocator<T>::count_ == allocator<T>::size_){
		T *p = copy_mas(allocator<T>::ptr_, allocator<T>::count_, allocator<T>::size_ * 2 + (allocator<T>::count_ == 0));
		delete allocator<T>::ptr_;
		allocator<T>::ptr_ = p;
		allocator<T>::size_ = allocator<T>::size_ * 2 + (allocator<T>::count_ == 0);
	}
	allocator<T>::ptr_[allocator<T>::count_] = a;
	++allocator<T>::count_;
}

template <typename T>
const T& stack<T>::top()
{
	if (allocator<T>::count_ > 0) return allocator<T>::ptr_[allocator<T>::count_ - 1];
	else throw("Stack is empty");
}

template <typename T>
void stack<T>::pop()
{
	if (allocator<T>::count_> 0) --allocator<T>::count_;
	else throw ("Stack is empty");
}

template<typename T>
bool stack<T>::empty()
{ 
	return(allocator<T>::count_ == 0); 
} 

#endif
