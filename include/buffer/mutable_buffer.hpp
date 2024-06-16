#pragma once

#include <initializer_list>
#include <system_error>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <compare>
#include <istream>
#include <string>
#include <array>

#include <cerrno>

extern "C"
{

#include <unistd.h>

}

namespace terminal
{
    template<typename T, std::size_t N>
    class mutable_buffer;

    template<typename T, std::size_t N>
    std::basic_istream<T>& operator>>(std::basic_istream<T>&, mutable_buffer<T, N>&);

    template<typename T, std::size_t N>
    std::size_t read(int, mutable_buffer<T, N>&, std::error_code&) noexcept;

    template<typename T, std::size_t N>
    std::size_t read(int, mutable_buffer<T, N>&);
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

    explicit mutable_buffer(const mutable_buffer& other)
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

    std::strong_ordering operator<=>(const mutable_buffer& rhs) const
    {
	return std::lexicographical_compare_three_way(cbegin(), cend(),
						      rhs.cbegin(), rhs.cend());
    }

    constexpr bool operator==(const mutable_buffer& rhs) const noexcept
    {
	return std::equal(cbegin(), cend(), rhs.cbegin(), rhs.end());
    }

    constexpr bool operator!=(const mutable_buffer& rhs) const noexcept
    {
	return (not this->operator==(rhs));
    }

    friend std::basic_istream<T>& operator>><>(std::basic_istream<T>&, mutable_buffer&);

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

    const_iterator cbegin() const noexcept
    {
	return buffer.cbegin();
    }

    const_iterator begin() const noexcept
    {
	return buffer.begin();
    }
    
    iterator begin() noexcept
    {
	return const_cast<iterator>(const_cast<const_this>(this)->begin());
    }

    const_iterator cend() const noexcept
    {
	return std::next(cbegin(), size());
    }

    const_iterator end() const noexcept
    {
	return cend();
    }

    iterator end() noexcept
    {
	return const_cast<iterator>(const_cast<const_this>(this)->end());
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

    const_reverse_iterator rbegin() const noexcept
    {
	return crbegin();
    }

    reverse_iterator rbegin() noexcept
    {
	return std::make_reverse_iterator(end());
    }

    const_reverse_iterator crend() const noexcept
    {
	return std::make_reverse_iterator(cbegin());
    }

    const_reverse_iterator rend() const noexcept
    {
	return crend();
    }

    reverse_iterator rend() noexcept
    {
	return std::make_reverse_iterator(begin());
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

    friend std::size_t read<>(int, mutable_buffer&, std::error_code&) noexcept;

    constexpr size_type size() const noexcept
    {
	return sz;
    }

    void swap(mutable_buffer& rhs) noexcept
    {
	std::swap(*this, rhs);
    }

private:
    std::array<value_type, N> buffer;

    size_type sz;
};

template<typename T, std::size_t N>
std::basic_istream<T>&
terminal::operator>>(std::basic_istream<T>& input, mutable_buffer<T, N>& mbuf)
{
    std::basic_string<T> string;

    input >> string;

    if (not (input.bad() || input.fail()))
    {
	auto length = std::min(string.size(), mbuf.max_size());

	std::copy_n(string.cbegin(), length, mbuf.buffer.data());

	mbuf.sz = string.size();
    }

    return input;
}

template<typename T, std::size_t N>
std::size_t
terminal::read(int fd, mutable_buffer<T, N>& mbuf, std::error_code& error) noexcept
{
    mutable_buffer<T, N> tmp_mbuf;

    std::size_t count = ::read(fd, tmp_mbuf.buffer.data(), tmp_mbuf.max_size());

    if (count == -1)
	error = std::error_code {errno, std::system_category()};

    else
    {
	tmp_mbuf.sz = count;

	mbuf.swap(tmp_mbuf);
    }

    return count;
}

template<typename T, std::size_t N>
std::size_t terminal::read(int fd, mutable_buffer<T, N>& mbuf)
{
    std::error_code error;

    if (read(fd, mbuf, error); error)
	throw std::system_error {error, __func__};

    return mbuf.size();
}
