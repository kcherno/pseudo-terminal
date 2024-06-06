#pragma once

#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <array>

namespace terminal
{
    template<typename T, std::size_t N>
    class mutable_buffer;
}

template<typename T, std::size_t N>
class terminal::mutable_buffer final {
public:
    using value_type =
	typename std::array<T, N>::value_type;

    using size_type =
	typename std::array<T, N>::size_type;

    using difference_type =
	typename std::array<T, N>::difference_type;

    using reference =
	typename std::array<T, N>::reference;

    using const_reference =
	typename std::array<T, N>::const_reference;

    using pointer =
	typename std::array<T, N>::pointer;

    using const_pointer =
	typename std::array<T, N>::const_pointer;

    using iterator =
	typename std::array<T, N>::iterator;

    using const_iterator =
	typename std::array<T, N>::const_iterator;

    using reverse_iterator =
	typename std::array<T, N>::reverse_iterator;

    using const_reverse_iterator =
	typename std::array<T, N>::const_reverse_iterator;

private:
    using const_this = const mutable_buffer*;

public:
    constexpr mutable_buffer()
        noexcept(std::is_nothrow_default_constructible_v<value_type>) :

	buffer {},
	sz     {0}
    {}

    template<std::forward_iterator Iterator>
    requires std::same_as<value_type, std::iter_value_t<Iterator>>
    mutable_buffer(Iterator first, Iterator last) :
	mutable_buffer {}
    {
	if (max_size() < static_cast<size_t>(std::distance(first, last)))
	    throw std::out_of_range {__func__};

	for (; first != last; ++first)
	    push_back(*first);
    }

    mutable_buffer(std::initializer_list<value_type> ilist) :
	mutable_buffer {}
    {
	this->operator=(mutable_buffer {ilist.begin(), ilist.end()});
    }

    mutable_buffer(const mutable_buffer& other)
	noexcept(std::is_nothrow_copy_constructible_v<value_type>) :

	mutable_buffer{}
    {
	this->operator=(other);
    }

    mutable_buffer(mutable_buffer&& other) noexcept :
	mutable_buffer {}
    {
	this->operator=(std::move(other));
    }

    mutable_buffer& operator=(const mutable_buffer& other)
    {
	if (this != &other)
	    this->operator=(mutable_buffer {other.begin(), other.end()});

	return *this;
    }

    mutable_buffer& operator=(mutable_buffer&& other) noexcept
    {
	static_assert(std::is_nothrow_move_assignable_v<value_type>);

	if (this != &other)
	{
	    if (size() < other.size())
		std::swap_ranges(other.begin(), other.end(), begin());

	    else
		std::swap_ranges(begin(), end(), other.begin());

	    std::swap(sz, other.sz);
	}

	return *this;
    }

    const_reference at(size_type n) const
    {
	if (empty() || n > size())
	    throw std::out_of_range {__func__};

	return buffer[n];
    }

    reference at(size_type n)
    {
	return const_cast<reference>(const_cast<const_this>(this)->at(n));
    }	

    const_reference back() const
    {
	return at(size() - 1);
    }

    reference back()
    {
	return const_cast<reference>(const_cast<const_this>(this)->back());
    }

    const_iterator begin() const noexcept
    {
	return buffer.begin();
    }
    
    iterator begin() noexcept
    {
	return const_cast<iterator>(const_cast<const_this>(this)->begin());
    }

    const_iterator cbegin() const noexcept
    {
	return buffer.cbegin();
    }

    const_iterator cend() const noexcept
    {
	return std::next(cbegin(), size());
    }

    void clear() noexcept
    {
	for (auto first = begin(), last = end(); first != last; ++first)
	    pop_back();

	sz = 0;
    }
    
    const_reverse_iterator crbegin() const noexcept
    {
	return std::make_reverse_iterator(cend());
    }

    const_reverse_iterator crend() const noexcept
    {
	return std::make_reverse_iterator(cbegin());
    }

    const_pointer data() const noexcept
    {
	return empty() ? nullptr : buffer.data();
    }

    pointer data() noexcept
    {
	return const_cast<pointer>(const_cast<const_this>(this)->data());
    }
    
    bool empty() const noexcept
    {
	return size() == 0;
    }

    const_iterator end() const noexcept
    {
	return std::next(begin(), size());
    }

    iterator end() noexcept
    {
	return const_cast<iterator>(const_cast<const_this>(this)->end());
    }

    const_reference front() const
    {
	return at(0);
    }

    reference front()
    {
	return const_cast<reference>(const_cast<const_this>(this)->front());
    }

    constexpr size_t max_size() const noexcept
    {
	return buffer.max_size();
    }

    const_reference operator[](std::size_t n) const
    {
	return at(n);
    }
    
    reference operator[](std::size_t n)
    {
	return const_cast<reference>(const_cast<const_this>(this)->operator[](n));
    }

    void pop_back()
    {
	if (empty())
	    throw std::out_of_range {__func__};

	buffer[--sz] = value_type {};
    }

    template<typename U>
    void push_back(U&& value)
    {
	if (size() == max_size())
	    throw std::out_of_range {__func__};

	buffer[sz++] = std::forward<U>(value);
    }

    const_reverse_iterator rbegin() const noexcept
    {
	return std::make_reverse_iterator(end());
    }

    reverse_iterator rbegin() noexcept
    {
	return std::make_reverse_iterator(end());
    }

    const_reverse_iterator rend() const noexcept
    {
	return std::make_reverse_iterator(begin());
    }

    reverse_iterator rend() noexcept
    {
	return std::make_reverse_iterator(begin());
    }
    
    constexpr size_type size() const noexcept
    {
	return sz;
    }

private:
    std::array<value_type, N> buffer;

    size_type sz;
};
