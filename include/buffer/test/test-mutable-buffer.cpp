#define BOOST_TEST_MODULE MUTABLE_BUFFER

#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <iostream>

#include "mutable_buffer.hpp"

BOOST_AUTO_TEST_SUITE(mutable_buffer);

BOOST_AUTO_TEST_SUITE(default_constructor);
BOOST_AUTO_TEST_CASE(success)
{
    constexpr terminal::mutable_buffer<char, 5> c_empty;

    BOOST_CHECK_EQUAL(c_empty.cbegin(), c_empty.cend());
    // BOOST_CHECK_EQUAL(c_empty.crbegin(), c_empty.crend());
    BOOST_CHECK_EQUAL(c_empty.data(),     nullptr);
    BOOST_CHECK_EQUAL(c_empty.empty(),    true);
    BOOST_CHECK_EQUAL(c_empty.max_size(), 5);
    BOOST_CHECK_EQUAL(c_empty.size(),     0);

    terminal::mutable_buffer<char, 5> empty;

    BOOST_CHECK_EQUAL(empty.cbegin(), empty.cend());
    BOOST_CHECK_EQUAL(empty.begin(),  empty.end());
    // BOOST_CHECK_EQUAL(empty.crbegin(), empty.crbegin());
    // BOOST_CHECK_EQUAL(empty.rbegin(),  empty.rend());
    BOOST_CHECK_EQUAL(empty.data(),     nullptr);
    BOOST_CHECK_EQUAL(empty.empty(),    true);
    BOOST_CHECK_EQUAL(empty.max_size(), 5);
    BOOST_CHECK_EQUAL(empty.size(),     0);
}

BOOST_AUTO_TEST_CASE(failure)
{
    constexpr terminal::mutable_buffer<char, 5> c_empty;

    BOOST_REQUIRE_THROW(c_empty.at(0),   std::out_of_range);
    BOOST_REQUIRE_THROW(c_empty.back(),  std::out_of_range);
    BOOST_REQUIRE_THROW(c_empty.front(), std::out_of_range);
    BOOST_REQUIRE_THROW(c_empty[0],      std::out_of_range);

    terminal::mutable_buffer<char, 5> empty;

    BOOST_REQUIRE_THROW(empty.at(0),      std::out_of_range);
    BOOST_REQUIRE_THROW(empty.back(),     std::out_of_range);
    BOOST_REQUIRE_THROW(empty.front(),    std::out_of_range);
    BOOST_REQUIRE_THROW(empty[0],         std::out_of_range);
    BOOST_REQUIRE_THROW(empty.pop_back(), std::out_of_range);
}	
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(parameterized_constructor);
BOOST_AUTO_TEST_CASE(success)
{
    const terminal::mutable_buffer<int, 5> cfbuf {1, 2, 3, 4, 5};

    BOOST_CHECK_EQUAL(cfbuf.at(0),  1);
    BOOST_CHECK_EQUAL(cfbuf.at(4),  5);
    BOOST_CHECK_EQUAL(cfbuf.back(), 5);

    /* //
    for (const auto& cb : cfbuf)
	std::cout << cb << std::endl;

    std::for_each(cfbuf.cbegin(), cfbuf.cend(), [](auto n) {
	std::cout << n << std::endl;
    });

    std::for_each(cfbuf.begin(), cfbuf.cend(), [](auto n) {
	std::cout << n << std::endl;
    });

    std::for_each(cfbuf.crbegin(), cfbuf.crend(), [](auto n) {
	std::cout << n << std::endl;
    });

    std::for_each(cfbuf.rbegin(), cfbuf.rend(), [](auto n) {
	std::cout << n << std::endl;
    });
    */ //

    BOOST_CHECK_NE(cfbuf.data(),  nullptr);
    BOOST_CHECK_NE(cfbuf.empty(), true);
    BOOST_CHECK_EQUAL(cfbuf.front(), 1);
    BOOST_CHECK_EQUAL(cfbuf.max_size(), 5);
    BOOST_CHECK_EQUAL(cfbuf[0],         1);
    BOOST_CHECK_EQUAL(cfbuf[4],         5);
    BOOST_CHECK_EQUAL(cfbuf.size(),     5);

    terminal::mutable_buffer<int, 5> fbuf {1, 2, 3, 4, 5};

    BOOST_CHECK_EQUAL(fbuf.at(0), 1);
    fbuf.at(0) = 10;
    BOOST_CHECK_EQUAL(fbuf.at(0), 10);
    fbuf.at(0) = 1;

    BOOST_CHECK_EQUAL(fbuf.back(), 5);
    fbuf.back() = 50;
    BOOST_CHECK_EQUAL(fbuf.back(), 50);
    fbuf.back() = 5;

    /* //
    for (const auto& n : fbuf)
	std::cout << n << std::endl;

    std::for_each(fbuf.cbegin(), fbuf.cend(), [](auto n) {
	std::cout << n << std::endl;
    });

    std::for_each(fbuf.begin(), fbuf.end(), [](auto n) {
	std::cout << n << std::endl;
    });

    std::for_each(fbuf.crbegin(), fbuf.crend(), [](auto n) {
	std::cout << n << std::endl;
    });

    std::for_each(fbuf.rbegin(), fbuf.rend(), [](auto n) {
	std::cout << n << std::endl;
    });
    */ //

    BOOST_CHECK_EQUAL(*fbuf.begin(), 1);
    *fbuf.begin() = 10;
    BOOST_CHECK_EQUAL(*fbuf.begin(), 10);
    BOOST_CHECK_EQUAL(fbuf.front(),  10);
    *fbuf.begin() = 1;

    BOOST_CHECK_EQUAL(*fbuf.rbegin(), 5);
    *fbuf.rbegin() = 50;
    BOOST_CHECK_EQUAL(*fbuf.rbegin(), 50);
    BOOST_CHECK_EQUAL(fbuf.back(),    50);    
    *fbuf.rbegin() = 5;

    BOOST_CHECK_NE(fbuf.data(),  nullptr);
    BOOST_CHECK_NE(fbuf.empty(), true);

    BOOST_CHECK_EQUAL(fbuf.front(), 1);
    fbuf.front() = 10;
    BOOST_CHECK_EQUAL(fbuf.front(), 10);
    fbuf.front() = 1;

    BOOST_CHECK_EQUAL(fbuf.max_size(), 5);
    BOOST_CHECK_EQUAL(fbuf.size(),     5);
}

BOOST_AUTO_TEST_CASE(failure)
{
    terminal::mutable_buffer<int, 5> fbuf {1, 2, 3, 4, 5};

    BOOST_REQUIRE_THROW(fbuf.push_back(6), std::out_of_range);
}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(range_constructor);
BOOST_AUTO_TEST_CASE(success)
{
    const terminal::mutable_buffer<int, 3> mbuffer {1, 2, 3};

    const terminal::mutable_buffer<int, 5> cnfbuf {
	mbuffer.cbegin(),
	mbuffer.cend()
    };

    BOOST_TEST(std::equal(mbuffer.cbegin(), mbuffer.cend(), cnfbuf.cbegin()));

    BOOST_CHECK_EQUAL(cnfbuf.back(), *mbuffer.crbegin());
    BOOST_CHECK_EQUAL(cnfbuf.front(), *mbuffer.cbegin());
    BOOST_CHECK_EQUAL(cnfbuf.max_size(), 5);
    BOOST_CHECK_EQUAL(cnfbuf.size(), mbuffer.size());

    terminal::mutable_buffer<int, 5> nfbuf {
	mbuffer.cbegin(),
	mbuffer.cend()
    };

    BOOST_TEST(std::equal(mbuffer.cbegin(), mbuffer.cend(), nfbuf.cbegin()));

    BOOST_CHECK_EQUAL(nfbuf.back(), *mbuffer.crbegin());
    BOOST_CHECK_EQUAL(nfbuf.front(), *mbuffer.cbegin());
    BOOST_CHECK_EQUAL(nfbuf.max_size(), 5);
    BOOST_CHECK_EQUAL(nfbuf.size(), mbuffer.size());

    nfbuf.clear();

    BOOST_CHECK_EQUAL(nfbuf.empty(), true);
    BOOST_CHECK_EQUAL(nfbuf.size(),  0);
}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(move_constructor);
BOOST_AUTO_TEST_CASE(success)
{
    terminal::mutable_buffer<int, 5> lhs {1, 2, 3, 4, 5};
    terminal::mutable_buffer<int, 5> rhs {1, 2, 3};

    std::swap(lhs, rhs);

    BOOST_TEST(((lhs.front() == 1) && (lhs.back() == 3) && (lhs.size() == 3)));
    BOOST_TEST(((rhs.front() == 1) && (rhs.back() == 5) && (rhs.size() == 5)));

    terminal::mutable_buffer<int, 5> empty;
    terminal::mutable_buffer<int, 5> full {1, 2, 3, 4, 5};

    std::swap(empty, full);

    BOOST_TEST(((empty.front() == 1) && (empty.back() == 5) && empty.size() == 5));

    BOOST_REQUIRE_THROW(full.back(),  std::out_of_range);
    BOOST_REQUIRE_THROW(full.front(), std::out_of_range);
    
    BOOST_TEST(full.empty());
}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();
