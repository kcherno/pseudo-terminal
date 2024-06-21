#pragma once

#include <cstdio>
#include <string>

#include "feature_macros.hpp"

namespace terminal
{
    class cursor_interface;

    class dec_sequence_cursor;
    class sco_sequence_cursor;
}

class terminal::cursor_interface {
public:
    virtual ~cursor_interface() = default;

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view erase_after_cursor() const noexcept
    {
	return "\033[0K";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view erase_before_cursor() const noexcept
    {
	return "\033[1K";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view make_cursor_invisible() const noexcept
    {
	return "\033[?25l";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view make_cursor_visible() const noexcept
    {
	return "\033[?25h";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_beg_nl() const noexcept
    {
	// moves cursor to beginning of next line

	return "\033[E";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_beg_pl() const noexcept
    {
	// moves cursor to beginning of previous line

	return "\033[F";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_down() const noexcept
    {
	return "\033[B";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_home() const noexcept
    {
	return "\033[H";
    }
    
    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_left() const noexcept
    {
	return "\033[D";
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_right() const noexcept
    {
	return "\033[C";
    }

    std::string move_cursor_to(int row, int col) const
    {
	std::string string;

	string.reserve(60);

	std::snprintf(string.data(), string.capacity(), "\033[{%d};{%d}H", row, col);

	return string.data();
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    std::string_view move_cursor_up() const noexcept
    {
	return "\033[A";
    }

    CONSTEXPR_VIRTUAL_FUNCTION_SPECIFIER__
    virtual std::string_view restore_cursor_position() const noexcept = 0;

    CONSTEXPR_VIRTUAL_FUNCTION_SPECIFIER__
    virtual std::string_view save_cursor_position() const noexcept = 0;
};

class terminal::dec_sequence_cursor final :
    public terminal::cursor_interface
{
public:
    CONSTEXPR_VIRTUAL_FUNCTION_SPECIFIER__
    std::string_view restore_cursor_position() const noexcept override
    {
	// restores the cursor to the last saved position (DEC)

	return "\033 8";
    }

    CONSTEXPR_VIRTUAL_FUNCTION_SPECIFIER__
    std::string_view save_cursor_position() const noexcept override
    {
	// save cursor position (DEC)

	return "\033 7";
    }
};

class terminal::sco_sequence_cursor final :
    public terminal::cursor_interface
{
public:
    CONSTEXPR_VIRTUAL_FUNCTION_SPECIFIER__
    std::string_view restore_cursor_position() const noexcept override
    {
	// restores the cursor to the last saved position (SCO)

	return "\033[u";
    }

    CONSTEXPR_VIRTUAL_FUNCTION_SPECIFIER__
    std::string_view save_cursor_position() const noexcept override
    {
	// save cursor position (SCO)

	return "\033[s";
    }
};
