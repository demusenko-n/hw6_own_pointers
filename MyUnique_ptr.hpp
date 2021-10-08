#pragma once
#include <utility>
namespace my_pointers
{
	template<class T>
	class MyUnique_ptr
	{
		T* raw_pointer_;
	public:
		MyUnique_ptr()noexcept : MyUnique_ptr(nullptr)
		{

		}
		explicit MyUnique_ptr(T* ptr)noexcept : raw_pointer_(ptr) {}
		MyUnique_ptr(const MyUnique_ptr& ptr) = delete;
		MyUnique_ptr& operator=(const MyUnique_ptr& ptr) = delete;
		MyUnique_ptr& operator=(std::nullptr_t)
		{
			delete_ptr();
			return *this;
		}
		MyUnique_ptr(MyUnique_ptr&& ptr)noexcept : MyUnique_ptr(ptr.raw_pointer_)
		{
			ptr.raw_pointer_ = nullptr;
		}
		MyUnique_ptr& operator=(MyUnique_ptr&& ptr) noexcept
		{
			delete_ptr();

			raw_pointer_ = ptr.raw_pointer_;
			ptr.raw_pointer_ = nullptr;
			return this;
		}
		~MyUnique_ptr()noexcept
		{
			delete_ptr();
		}
		T& operator* ()const noexcept
		{
			return *raw_pointer_;
		}
		T* operator->()const noexcept
		{
			return raw_pointer_;
		}
		explicit operator bool()const noexcept
		{
			return raw_pointer_;
		}
		T* get()const noexcept
		{
			return raw_pointer_;
		}
		void swap(MyUnique_ptr<T>& other)noexcept
		{
			std::swap(raw_pointer_, other.raw_pointer_);
		}
		void reset(T* ptr = nullptr)noexcept
		{
			delete_ptr();
			raw_pointer_ = ptr;
		}
		T* release()noexcept
		{
			T* ptr = raw_pointer_;
			raw_pointer_ = nullptr;
			return ptr;
		}
	private:
		void delete_ptr()
		{
			delete raw_pointer_;
			raw_pointer_ = nullptr;
		}
	};
}