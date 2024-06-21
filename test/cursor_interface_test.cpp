#define BOOST_TEST_MODULE CURSOR_INTERFACE

#include <boost/test/unit_test.hpp>

#include "terminal/cursor_interface.hpp"

BOOST_AUTO_TEST_SUITE(public_cursor_functions);
BOOST_AUTO_TEST_CASE(success)
{
    terminal::dec_sequence_cursor dec_cursor;

    BOOST_CHECK_EQUAL(dec_cursor.erase_after_cursor(),      "\033[0K");
    BOOST_CHECK_EQUAL(dec_cursor.erase_before_cursor(),     "\033[1K");
    BOOST_CHECK_EQUAL(dec_cursor.make_cursor_invisible(),   "\033[?25l");
    BOOST_CHECK_EQUAL(dec_cursor.make_cursor_visible(),     "\033[?25h");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_beg_nl(),      "\033[E");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_beg_pl(),      "\033[F");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_down(),        "\033[B");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_home(),        "\033[H");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_left(),        "\033[D");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_right(),       "\033[C");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_to(300, 3),    "\033[{300};{3}H");
    BOOST_CHECK_EQUAL(dec_cursor.move_cursor_up(),          "\033[A");
    BOOST_CHECK_EQUAL(dec_cursor.restore_cursor_position(), "\033 8");
    BOOST_CHECK_EQUAL(dec_cursor.save_cursor_position(),    "\033 7");

    terminal::sco_sequence_cursor sco_cursor;

    BOOST_CHECK_EQUAL(sco_cursor.erase_after_cursor(),      "\033[0K");
    BOOST_CHECK_EQUAL(sco_cursor.erase_before_cursor(),     "\033[1K");
    BOOST_CHECK_EQUAL(sco_cursor.make_cursor_invisible(),   "\033[?25l");
    BOOST_CHECK_EQUAL(sco_cursor.make_cursor_visible(),     "\033[?25h");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_beg_nl(),      "\033[E");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_beg_pl(),      "\033[F");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_down(),        "\033[B");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_home(),        "\033[H");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_left(),        "\033[D");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_right(),       "\033[C");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_to(20, 20),    "\033[{20};{20}H");
    BOOST_CHECK_EQUAL(sco_cursor.move_cursor_up(),          "\033[A");
    BOOST_CHECK_EQUAL(sco_cursor.restore_cursor_position(), "\033[u");
    BOOST_CHECK_EQUAL(sco_cursor.save_cursor_position(),    "\033[s");
}
BOOST_AUTO_TEST_SUITE_END();
