#pragma once
#include <utility>
#include <cstddef>

namespace my_pointers
{
	template <class T>
	class MyShared_ptr
	{
		T* raw_pointer_;
		size_t* ref_counter_;
	public:
		MyShared_ptr()noexcept : raw_pointer_(nullptr), ref_counter_(nullptr)
		{

		}
		explicit MyShared_ptr(T* ptr)noexcept : raw_pointer_(ptr)
		{
			if (ptr != nullptr)
			{
				ref_counter_ = new size_t(1);
			}
		}
		MyShared_ptr(const MyShared_ptr& other)noexcept : raw_pointer_(other.raw_pointer_), ref_counter_(other.ref_counter_)
		{
			if (raw_pointer_ != nullptr)
			{
				++* ref_counter_;
			}
		}
		MyShared_ptr(MyShared_ptr&& other)noexcept : raw_pointer_(other.raw_pointer_), ref_counter_(other.ref_counter_)
		{
			other.raw_pointer_ = other.ref_counter_ = nullptr;
		}
		~MyShared_ptr()noexcept
		{
			delete_ptr();
		}
		MyShared_ptr& operator=(const MyShared_ptr& other)noexcept
		{
			if (this != &other)
			{
				delete_ptr();
				if (other.raw_pointer_ != nullptr)
				{
					raw_pointer_ = other.raw_pointer_;
					ref_counter_ = other.ref_counter_;
					++* ref_counter_;
				}
			}
			return this;
		}
		MyShared_ptr& operator=(MyShared_ptr&& other)noexcept
		{
			delete_ptr();

			if (other.raw_pointer_ != nullptr)
			{
				raw_pointer_ = other.raw_pointer_;
				other.raw_pointer_ = nullptr;
				ref_counter_ = other.ref_counter_;
				other.ref_counter_ = nullptr;
			}
			return this;
		}
		void reset(T* ptr = nullptr)noexcept
		{
			delete_ptr();
			if (ptr != nullptr)
			{
				raw_pointer_ = ptr;
				ref_counter_ = new size_t(1);
			}
		}
		void swap(MyShared_ptr<T>& other)noexcept
		{
			std::swap(raw_pointer_, other.raw_pointer_);
			std::swap(ref_counter_, other.ref_counter_);
		}
		T* get()const noexcept
		{
			return raw_pointer_;
		}
		T& operator* ()const noexcept
		{
			return *raw_pointer_;
		}
		T* operator->()const noexcept
		{
			return raw_pointer_;
		}
		size_t use_count()const noexcept
		{
			if (raw_pointer_ == nullptr)
			{
				return 0;
			}
			return *ref_counter_;
		}
		bool unique() const noexcept
		{
			return use_count() == 1;
		}
		explicit operator bool() const noexcept
		{
			return raw_pointer_;
		}
		bool operator==(const MyShared_ptr& other)
		{
			return other.raw_pointer_ == this->raw_pointer_;
		}
		bool operator!=(const MyShared_ptr& other)
		{
			return other.raw_pointer_ != this->raw_pointer_;
		}
	private:
		void delete_ptr()
		{
			if (raw_pointer_ != nullptr)
			{
				if (-- * ref_counter_ == 0)
				{
					delete ref_counter_, raw_pointer_;
				}
			}
			raw_pointer_ = nullptr;
            ref_counter_ = nullptr;
		}
	};


}

