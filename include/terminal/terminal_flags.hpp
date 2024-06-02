#pragma once

#include <concepts>

extern "C"
{

#include <termios.h>

}

namespace terminal
{
    enum class input_mode;
    enum class local_mode;

    template<typename T>
    concept terminal_flag =
	std::same_as<input_mode, T> ||
	std::same_as<local_mode, T>;

    enum class optional_actions;
}

enum class terminal::input_mode {
    brkint = BRKINT,
    ignbrk = IGNBRK
};

enum class terminal::local_mode {
    echo    = ECHO,
    echoctl = ECHOCTL,
    echoe   = ECHOE,
    echok   = ECHOK
};

enum class terminal::optional_actions {
    tcsadrain = TCSADRAIN,
    tcsaflush = TCSAFLUSH,
    tcsanow   = TCSANOW
};
