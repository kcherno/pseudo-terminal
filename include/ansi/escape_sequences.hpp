#pragma once

#include <concepts>
#include <string>

#include "confing/escape_sequence_type.hpp"

namespace ansi::escape
{
    enum class cursor;
    enum class erase;
    enum class screen;

    template<typename T>
    concept escape_sequence =
	std::same_as<cursor, T> ||
	std::same_as<erase,  T> ||
	std::same_as<screen, T>;

    template<escape_sequence T>
    constexpr std::string_view get_sequence(T) noexcept;

    template<escape_sequence... Args>
    std::string get_sequences(Args...);
}

enum class ansi::escape::cursor {
    beginning_nl = 0,
    beginning_pl,
    move_down,
    move_home,
    move_left,
    move_right,
    move_up,
    restore_position,
    save_position
};

enum class ansi::escape::erase {
    entire_screen
};

enum class ansi::escape::screen {
    restore_screen = 0,
    save_screen
};

template<ansi::escape::escape_sequence T>
constexpr std::string_view ansi::escape::get_sequence(T sequence) noexcept
{
    if constexpr (std::same_as<cursor, T>)
    {
	constexpr std::string_view cursor_sequences[] = {
	    "\033[E", // moves cursor to beginning of next line
	    "\033[F", // moves cursor to beginning of previous line
	    "\033[B", // moves cursor down
	    "\033[H", // moves cursor to home position (0, 0)
	    "\033[D", // moves cursor left
	    "\033[C", // moves cursor right
	    "\033[A", // moves cursor up

#if   defined(DEC_ESCAPE_SEQUENCES)

	    "\033 8", // restores the cursor to the last saved position (DEC)
	    "\033 7"  // save cursor position (DEC)

#elif defined(SCO_ESCAPE_SEQUENCES)

	    "\033[u", // restores the cursor to the last saved position (SCO)
	    "\033[s"  // save cursor position (SCO)

#endif
	};

	if (cursor::beginning_nl <= sequence && sequence <= cursor::save_position)
	    return cursor_sequences[static_cast<int>(sequence)];

	else
	    return std::string_view {};
    }

    if constexpr (std::same_as<erase, T>)
    {
	constexpr std::string_view erase_sequences[] = {
	    "\033[2J" // erase entire screen
	};

	if (erase::entire_screen <= sequence && sequence <= erase::entire_screen)
	    return erase_sequences[static_cast<int>(sequence)];

	else
	    return std::string_view {};
    }

    if constexpr (std::same_as<screen, T>)
    {
	constexpr std::string_view screen_sequences[] = {
	    "\033[?47l", // restore screen
	    "\033[?47h"  // save screen
	};

	if (screen::restore_screen <= sequence && sequence <= screen::save_screen)
	    return screen_sequences[static_cast<int>(sequence)];

	else
	    return std::string_view {};
    }
}

template<ansi::escape::escape_sequence... Args>
std::string ansi::escape::get_sequences(Args... args)
{
    static_assert(sizeof...(args) != 0, "Argument list is empty");
    
    std::string sequences;

    (sequences.append(get_sequence(args)), ...);

    return sequences;
}
