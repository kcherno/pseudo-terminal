#pragma once

#include <string>

#include "feature_macros.hpp"

namespace terminal
{
    enum class color;
    enum class graphic;
    
    class screen_interface;
}

enum class terminal::color {
    black = 0,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    system,
    bright_black,
    bright_red,
    bright_green,
    bright_yellow,
    bright_blue,
    bright_magenta,
    bright_cyan,
    bright_white
};

enum class terminal::graphic {
    bold = 0,
    dim,
    italic,
    underline,
    blinking,
    inverse,
    hidden,
    strikethrough
};

class terminal::screen_interface {
public:
    virtual ~screen_interface() = default;

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view erase_screen() const noexcept
    {
	return "\033[2J";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view erase_screen_after_cursor() const noexcept
    {
	return "\033[0J";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view erase_screen_before_cursor() const noexcept
    {
	return "\033[1J";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view restore_screen() const noexcept
    {
	return "\033[?47l";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view save_screen() const noexcept
    {
	return "\033[?47h";
    }

    std::string set_background_256color(int color) const
    {
	return rgb_color(color_format::background_256, color);
    }

    constexpr std::string_view set_background_color(color) const noexcept;

    std::string set_background_rgb_color(int r, int g, int b) const
    {
	return rgb_color(color_format::background_rgb, r, g, b);
    }

    std::string set_foreground_256color(int color) const
    {
	return rgb_color(color_format::foreground_256, color);
    }

    constexpr std::string_view set_foreground_color(color) const noexcept;

    std::string set_foreground_rgb_color(int r, int g, int b) const
    {
	return rgb_color(color_format::foreground_rgb, r, g, b);
    }

    constexpr std::string_view set_graphic_mode(graphic) const noexcept;

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view unset_background_color() const noexcept
    {
	return set_background_color(color::system);
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view unset_foreground_color() const noexcept
    {
	return set_foreground_color(color::system);
    }
    
    constexpr std::string_view unset_graphic_mode(graphic) const noexcept;

private:
    constexpr bool color_control(color enumerator) const noexcept
    {
	constexpr auto min_color = color::black;
	constexpr auto max_color = color::bright_white;

	return (enumerator >= min_color &&
		enumerator <= max_color);
    }

    constexpr bool graphic_control(graphic enumerator) const noexcept
    {
	constexpr auto min_graphic = graphic::bold;
	constexpr auto max_graphic = graphic::strikethrough;

	return (enumerator >= min_graphic &&
		enumerator <= max_graphic);
    }

    constexpr bool rgb_color_control(int color) const noexcept
    {
	constexpr int color_8bit_min = 0;
	constexpr int color_8bit_max = 255;

	return (color_8bit_min <= color && color <= color_8bit_max);
    }

private:
    enum class color_format {
	background_256 = 0,
	background_rgb,
	foreground_256,
	foreground_rgb
    };

    std::string rgb_color(color_format, int, int = -1, int = -1) const;
};

constexpr std::string_view
terminal::screen_interface::set_background_color(color enumerator) const noexcept
{
    constexpr std::string_view mode[] = {
	"\033[40m",
	"\033[41m",
	"\033[42m",
	"\033[43m",
	"\033[44m",
	"\033[45m",
	"\033[46m",
	"\033[47m",
	"\033[49m",
	"\033[100m",
	"\033[101m",
	"\033[102m",
	"\033[103m",
	"\033[104m",
	"\033[105m",
	"\033[106m",
	"\033[107m"
    };

    if (color_control(enumerator))
	return mode[static_cast<int>(enumerator)];

    else
	return std::string_view {};
}

constexpr std::string_view
terminal::screen_interface::set_foreground_color(color enumerator) const noexcept
{
    constexpr std::string_view mode[] = {
	"\033[30m",
	"\033[31m",
	"\033[32m",
	"\033[33m",
	"\033[34m",
	"\033[35m",
	"\033[36m",
	"\033[37m",
	"\033[39m",
	"\033[90m",
	"\033[91m",
	"\033[92m",
	"\033[93m",
	"\033[94m",
	"\033[95m",
	"\033[96m",
	"\033[97m"
    };

    if (color_control(enumerator))
	return mode[static_cast<int>(enumerator)];

    else
	return std::string_view {};
}

constexpr std::string_view
terminal::screen_interface::set_graphic_mode(graphic enumerator) const noexcept
{
    constexpr std::string_view mode[] = {
	"\033[1m",
	"\033[2m",
	"\033[3m",
	"\033[4m",
	"\033[5m",
	"\033[7m",
	"\033[8m",
	"\033[9m"
    };

    if (graphic_control(enumerator))
	return mode[static_cast<int>(enumerator)];

    else
	return std::string_view {};
}

constexpr std::string_view
terminal::screen_interface::unset_graphic_mode(graphic enumerator) const noexcept
{
    constexpr std::string_view mode[] = {
	"\033[22m",
	"\033[22m",
	"\033[23m",
	"\033[24m",
	"\033[25m",
	"\033[27m",
	"\033[28m",
	"\033[29m"
    };

    if (graphic_control(enumerator))
	return mode[static_cast<int>(enumerator)];

    else
	return std::string_view {};
}
