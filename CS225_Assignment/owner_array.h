//Taeju Kwon
//CS225
//owner_array assignment
//2021 fall

#pragma once
#include  <iostream>
#include <gsl/gsl>

template<typename T>
class owner_array
{

public:
	typedef T element_type;
	typedef std::remove_cv_t<T> value_type;
	typedef int size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

private:
	size_type size_ = 0;
	gsl::owner<value_type*> data_ = nullptr;

public:
	owner_array()
	{
		size_ = 0;
		data_ = nullptr;
	}
	
	explicit owner_array(int count, const T& value = T())
	{
		if (count < 0)
		{
			throw std::invalid_argument("Invalid syntax : count < 0");
		}

		size_ = count;
		data_ = new value_type[size_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = value;
		}
	}

	template< class InputIt >
	owner_array(InputIt first, InputIt last) //?
	{
		size_ = last - first;
		data_ = new value_type[size_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = *(first + i);
		}

	}

	owner_array(const owner_array& other) //copy constructor
	{
		size_ = other.size_;
		data_ = new value_type[other.size_];

		std::copy(other.data_, other.data_ + size_, data_);
	}

	owner_array(owner_array&& other) noexcept //move constructor
	{
		size_ = 0;
		delete[]data();

		size_ = other.size_;
		data_ = new value_type[other.size_];
		data_ = other.data_;

		other.size_ = 0;
		other.data_ = nullptr;
	}

	owner_array(std::initializer_list<T> init)
	{
		size_ = init.size();
		data_ = new value_type[init.size()];
		
		for (int i = 0; i < size_; i++)
		{
			data_[i] = *(init.begin() + i);
		}
	}

	//constructor
	~owner_array()
	{
		if (data() != nullptr)
		{
			delete[] data();
		}
	}
	//destructor

	owner_array& operator=(const owner_array& other) //copy assignment operator
	{
		if (this != &other)
		{
			delete[] data_;

			size_ = other.size_;
			data_ = new value_type[size_];
			std::copy(other.data_, other.data_ + size_, data_);
		}
		return *this;
	};
	owner_array& operator=(owner_array&& other) //move assignment operator
	{
		if (this != &other)
		{
			size_ = 0;
			delete[] data_;

			//data = new T[other.size];
			data_ = other.data_;
			size_ = other.size_;

			other.data_ = nullptr;
			other.size_ = 0;
		}
		return *this;
	}

	iterator begin() const noexcept
	{
		return data();
	}
	iterator end() const noexcept
	{
		return data() + size();
	}

	reverse_iterator rbegin() const noexcept
	{
		if( size_== 0)
		{
			return rend();
		}else
		{
			return reverse_iterator(end());	
		}
	}

	reverse_iterator rend() const noexcept
	{
		return reverse_iterator(begin());
	}

	reference  front() const
	{
		if (size_ == 0)
		{
			throw std::exception("out of range");
		}else
		{
			return data_[0];
		}
	}

	reference back() const 
	{
		if (size_ == 0)
		{
			throw std::exception("out of range");
		} else
		{
			return data_[size_-1];
		}
	}

	reference  operator[](size_type idx) const
	{
		if (idx < -size_ || idx >= size_)
		{
			throw std::out_of_range("Out of range");
		}else if(idx <= -1 && idx > -size_)
		{
			return data_[size_+ idx];
		}
		else
		{
			return data_[idx];
		}
	}

	pointer data() const noexcept
	{
		return data_;
	}

	size_type  size() const noexcept
	{
		return size_;
	}
	
	size_type  size_bytes() const noexcept
	{
		return size_ * sizeof(T);
	}
	
	[[nodiscard]] bool empty() const noexcept
	{
		if (/*data_ == nullptr &&*/ size_ == 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

};
template<typename T>
gsl::span<const unsigned char, gsl::dynamic_extent> as_bytes(const owner_array<T>& array) noexcept
{
	return { reinterpret_cast<const unsigned char*>(array.data()), gsl::narrow_cast<gsl::span<unsigned char, gsl::dynamic_extent>::size_type>(array.size_bytes()) };
}

template<typename T>
gsl::span<unsigned char, gsl::dynamic_extent> as_writable_bytes(owner_array<T>& array) noexcept
{
	return{ reinterpret_cast<unsigned char*>(array.data()), gsl::narrow_cast<gsl::span<unsigned char, gsl::dynamic_extent>::size_type>(array.size_bytes()) };
}
