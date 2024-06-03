#pragma once

#include <stdexcept>

#include <cerrno>

extern "C"
{

#include <termios.h>
#include <unistd.h>

}

#include "terminal_flags.hpp"

namespace terminal
{   
    class terminal_interface;
}

class terminal::terminal_interface {
public:    
    virtual ~terminal_interface()
    {
	::tcsetattr(STDIN_FILENO, TCSANOW, &original_tattr);
    }

    baud_rate get_speed() const noexcept
    {
	return (static_cast<baud_rate>(::cfgetispeed(&get_termios())));
    }

    template<terminal_flag T>
    void set_flag(T) noexcept;

    template<terminal_flag... Args>
    void set_flags(Args...) noexcept;

    void set_speed(baud_rate speed, std::error_code& error) noexcept
    {
	if (::cfsetispeed(&get_termios(), static_cast<speed_t>(speed)) == -1)
	    error = std::error_code {errno, std::system_category()};
    }

    void set_speed(baud_rate speed)
    {
	std::error_code error;

	if (set_speed(speed, error); error)
	    throw std::system_error {error, __func__};
    }

    template<terminal_flag T>
    bool test_flag(T) const noexcept;

    template<terminal_flag... Args>
    bool test_flags(Args...) const noexcept;

    template<terminal_flag T>
    void unset_flag(T) noexcept;

    template<terminal_flag... Args>
    void unset_flags(Args...) noexcept;

    const ::termios& get_termios() const noexcept
    {
	return modified_tattr;
    }

    ::termios& get_termios() noexcept
    {
	return modified_tattr;
    }

    void set_attr(optional_actions option, std::error_code& error) const noexcept
    {
	if (::tcsetattr(STDIN_FILENO, static_cast<int>(option), &get_termios()) == -1)
	    error = std::error_code {errno, std::system_category()};
    }

    void set_attr(optional_actions option) const
    {
	std::error_code error;
	
	if (set_attr(option, error); error)
	    throw std::system_error {error, __func__};
    }

protected:
    terminal_interface();

private:
    ::termios original_tattr;
    ::termios modified_tattr;
};

template<terminal::terminal_flag T>
void terminal::terminal_interface::set_flag(T flag) noexcept
{
    if constexpr (std::same_as<input_mode, T>)
        get_termios().c_iflag |= static_cast<tcflag_t>(flag);

    if constexpr (std::same_as<local_mode, T>)
        get_termios().c_lflag |= static_cast<tcflag_t>(flag);
}

template<terminal::terminal_flag... Args>
void terminal::terminal_interface::set_flags(Args... args) noexcept
{
    static_assert(sizeof...(args) != 0, "Argument list is empty");
	
    (set_flag(args), ...);
}

template<terminal::terminal_flag T>
bool terminal::terminal_interface::test_flag(T flag) const noexcept
{
    if constexpr (std::same_as<input_mode, T>)
        return (get_termios().c_iflag & static_cast<tcflag_t>(flag));

    if constexpr (std::same_as<local_mode, T>)
        return (get_termios().c_lflag & static_cast<tcflag_t>(flag));
}

template<terminal::terminal_flag... Args>
bool terminal::terminal_interface::test_flags(Args... args) const noexcept
{
    static_assert(sizeof...(args) != 0, "Argument list is empty");

    return (... && test_flag(args));
}

template<terminal::terminal_flag T>
void terminal::terminal_interface::unset_flag(T flag) noexcept
{
    if constexpr (std::same_as<input_mode, T>)
        get_termios().c_iflag &= ~static_cast<tcflag_t>(flag);

    if constexpr (std::same_as<local_mode, T>)
        get_termios().c_lflag &= ~static_cast<tcflag_t>(flag);
}

template<terminal::terminal_flag... Args>
void terminal::terminal_interface::unset_flags(Args... args) noexcept
{
    static_assert(sizeof...(args) != 0, "Argument list is empty");

    (unset_flag(args), ...);
}

terminal::terminal_interface::terminal_interface()
{
    if (::isatty(STDIN_FILENO) == 0 || ::isatty(STDOUT_FILENO) == 0)
	throw std::system_error {errno, std::system_category(), __func__};

    if (::tcgetattr(STDIN_FILENO, &original_tattr) == -1)
	throw std::system_error {errno, std::system_category(), __func__};

    modified_tattr = original_tattr;
}
