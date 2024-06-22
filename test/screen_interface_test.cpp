#define BOOST_TEST_MODULE SCREEN_INTERFACE

#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <string>

#include "terminal/screen_interface.hpp"

constexpr int COLOR_8BIT_MAX = 255;

template<typename T>
T operator+(const T& lhs, const T& rhs) noexcept
{
    return static_cast<T>(static_cast<int>(lhs) + static_cast<int>(rhs));
}

template<typename T>
T operator-(const T& lhs, const T& rhs) noexcept
{
    return static_cast<T>(static_cast<int>(lhs) - static_cast<int>(rhs));
}

constexpr auto min_color = terminal::color::black;
constexpr auto max_color = terminal::color::bright_white;

constexpr auto min_graphic = terminal::graphic::bold;
constexpr auto max_graphic = terminal::graphic::strikethrough;

BOOST_AUTO_TEST_SUITE(public_screen_functions);
BOOST_AUTO_TEST_CASE(success)
{
    terminal::screen_interface screen;

    BOOST_CHECK_EQUAL(screen.erase_screen(),               "\033[2J");
    BOOST_CHECK_EQUAL(screen.erase_screen_after_cursor(),  "\033[0J");
    BOOST_CHECK_EQUAL(screen.erase_screen_before_cursor(), "\033[1J");
    BOOST_CHECK_EQUAL(screen.restore_screen(),             "\033[?47l");
    BOOST_CHECK_EQUAL(screen.save_screen(),                "\033[?47h");

    std::string color_buffer;

    color_buffer.reserve(30);

    for (int i = 0; i < COLOR_8BIT_MAX; ++i)
    {
	std::snprintf(color_buffer.data(),
		      color_buffer.capacity(),
		      "\033[48;5;%dm", i);

	BOOST_REQUIRE_EQUAL(screen.set_background_256color(i),
			    std::string_view(color_buffer.data()));
    }

    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::black),
		      "\033[40m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::red),
		      "\033[41m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::green),
		      "\033[42m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::yellow),
		      "\033[43m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::blue),
		      "\033[44m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::magenta),
		      "\033[45m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::cyan),
		      "\033[46m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::white),
		      "\033[47m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::system),
		      "\033[49m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_black),
		      "\033[100m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_red),
		      "\033[101m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_green),
		      "\033[102m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_yellow),
		      "\033[103m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_blue),
		      "\033[104m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_magenta),
		      "\033[105m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_cyan),
		      "\033[106m");
    BOOST_CHECK_EQUAL(screen.set_background_color(terminal::color::bright_white),
		      "\033[107m");

    for (int i = 0; i < COLOR_8BIT_MAX; ++i)
    {
	for (int j = 0; j < COLOR_8BIT_MAX; ++j)
	{
	    for (int k = 0; k < COLOR_8BIT_MAX; ++k)
	    {
		std::snprintf(color_buffer.data(),
			      color_buffer.capacity(),
			      "\033[48;2;%d;%d;%dm", i, j, k);

		BOOST_REQUIRE_EQUAL(screen.set_background_rgb_color(i, j, k),
				    std::string_view(color_buffer.data()));
	    }
	}
    }

    for (int i = 0; i < COLOR_8BIT_MAX; ++i)
    {
	std::snprintf(color_buffer.data(),
		      color_buffer.capacity(),
		      "\033[38;5;%dm", i);

	BOOST_REQUIRE_EQUAL(screen.set_foreground_256color(i),
			    std::string_view(color_buffer.data()));
    }

    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::black),
		      "\033[30m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::red),
		      "\033[31m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::green),
		      "\033[32m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::yellow),
		      "\033[33m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::blue),
		      "\033[34m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::magenta),
		      "\033[35m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::cyan),
		      "\033[36m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::white),
		      "\033[37m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::system),
		      "\033[39m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_black),
		      "\033[90m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_red),
		      "\033[91m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_green),
		      "\033[92m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_yellow),
		      "\033[93m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_blue),
		      "\033[94m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_magenta),
		      "\033[95m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_cyan),
		      "\033[96m");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(terminal::color::bright_white),
		      "\033[97m");

    for (int i = 0; i < COLOR_8BIT_MAX; ++i)
    {
	for (int j = 0; j < COLOR_8BIT_MAX; ++j)
	{
	    for (int k = 0; k < COLOR_8BIT_MAX; ++k)
	    {
		std::snprintf(color_buffer.data(),
			      color_buffer.capacity(),
			      "\033[38;2;%d;%d;%dm", i, j, k);

		BOOST_REQUIRE_EQUAL(screen.set_foreground_rgb_color(i, j, k),
				    std::string_view(color_buffer.data()));
	    }
	}
    }

    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::bold),
		      "\033[1m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::dim),
		      "\033[2m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::italic),
		      "\033[3m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::underline),
		      "\033[4m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::blinking),
		      "\033[5m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::inverse),
		      "\033[7m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::hidden),
		      "\033[8m");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(terminal::graphic::strikethrough),
		      "\033[9m");

    BOOST_REQUIRE_EQUAL(screen.unset_background_color(),
			screen.set_background_color(terminal::color::system));
    BOOST_REQUIRE_EQUAL(screen.unset_foreground_color(),
			screen.set_foreground_color(terminal::color::system));

    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::bold),
		      "\033[22m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::dim),
		      "\033[22m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::italic),
		      "\033[23m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::underline),
		      "\033[24m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::blinking),
		      "\033[25m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::inverse),
		      "\033[27m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::hidden),
		      "\033[28m");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(terminal::graphic::strikethrough),
		      "\033[29m");
}

BOOST_AUTO_TEST_CASE(failure)
{
    constexpr auto color_enumerator   = static_cast<terminal::color>(1);
    constexpr auto graphic_enumerator = static_cast<terminal::graphic>(1);
    
    terminal::screen_interface screen;

    BOOST_CHECK_EQUAL(screen.set_background_256color(-1),  "");
    BOOST_CHECK_EQUAL(screen.set_background_256color(256), "");

    BOOST_CHECK_EQUAL(screen.set_background_color(min_color - color_enumerator), "");
    BOOST_CHECK_EQUAL(screen.set_background_color(max_color + color_enumerator), "");

    BOOST_CHECK_EQUAL(screen.set_background_rgb_color(-1, 255, 255),  "");
    BOOST_CHECK_EQUAL(screen.set_background_rgb_color(255, -1, 255),  "");
    BOOST_CHECK_EQUAL(screen.set_background_rgb_color(255, 255, -1),  "");
    BOOST_CHECK_EQUAL(screen.set_background_rgb_color(256, 255, 255), "");
    BOOST_CHECK_EQUAL(screen.set_background_rgb_color(255, 256, 255), "");
    BOOST_CHECK_EQUAL(screen.set_background_rgb_color(255, 255, 256), "");

    BOOST_CHECK_EQUAL(screen.set_foreground_256color(-1),  "");
    BOOST_CHECK_EQUAL(screen.set_foreground_256color(256), "");

    BOOST_CHECK_EQUAL(screen.set_foreground_color(min_color - color_enumerator), "");
    BOOST_CHECK_EQUAL(screen.set_foreground_color(max_color + color_enumerator), "");

    BOOST_CHECK_EQUAL(screen.set_foreground_rgb_color(-1, 255, 255),  "");
    BOOST_CHECK_EQUAL(screen.set_foreground_rgb_color(255, -1, 255),  "");
    BOOST_CHECK_EQUAL(screen.set_foreground_rgb_color(255, 255, -1),  "");
    BOOST_CHECK_EQUAL(screen.set_foreground_rgb_color(256, 255, 255), "");
    BOOST_CHECK_EQUAL(screen.set_foreground_rgb_color(255, 256, 255), "");
    BOOST_CHECK_EQUAL(screen.set_foreground_rgb_color(255, 255, 256), "");

    BOOST_CHECK_EQUAL(screen.set_graphic_mode(min_graphic - graphic_enumerator), "");
    BOOST_CHECK_EQUAL(screen.set_graphic_mode(max_graphic + graphic_enumerator), "");

    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(min_graphic - graphic_enumerator), "");
    BOOST_CHECK_EQUAL(screen.unset_graphic_mode(max_graphic + graphic_enumerator), "");
}
BOOST_AUTO_TEST_SUITE_END();
