#pragma once

#include <system_error>
#include <stdexcept>
#include <cerrno>
#include <limits>

extern "C"
{

#include <sys/ioctl.h>
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
	::tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

	::ioctl(STDIN_FILENO, TIOCSWINSZ, &old_winsize);
    }

    int get_colums() const noexcept
    {
	return new_winsize.ws_col;
    }

    void set_colums(int size)
    {
	check_screen_resolution(size);

	new_winsize.ws_col =
	    static_cast<decltype(new_winsize.ws_col)>(size);
    }

    int get_rows() const noexcept
    {
	return new_winsize.ws_row;
    }

    void set_rows(int size)
    {
	check_screen_resolution(size);

	new_winsize.ws_row =
	    static_cast<decltype(new_winsize.ws_row)>(size);
    }

    baud_rate get_speed() const noexcept
    {
	return (static_cast<baud_rate>(::cfgetispeed(&get_termios())));
    }

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

    const ::termios& get_termios() const noexcept
    {
	return new_termios;
    }

    ::termios& get_termios() noexcept
    {
	using const_this = const terminal_interface*;

	return const_cast<::termios&>(const_cast<const_this>(this)->get_termios());
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

    void set_minimum_transfer_bytes(int number) noexcept
    {
	get_termios().c_cc[VMIN] = number;
    }

    void unset_minimum_transfer_byfes() noexcept
    {
	set_minimum_transfer_bytes(0);
    }

    void set_timer(int ds) noexcept
    {
	get_termios().c_cc[VTIME] = ds;
    }

    void unset_timer() noexcept
    {
	get_termios().c_cc[VTIME] = 0;
    }

    template<terminal_flag T>
    void set_flag(T) noexcept;

    template<terminal_flag... Args>
    void set_flags(Args...) noexcept;

    template<terminal_flag T>
    bool test_flag(T) const noexcept;

    template<terminal_flag... Args>
    bool test_flags(Args...) const noexcept;

    template<terminal_flag T>
    void unset_flag(T) noexcept;

    template<terminal_flag... Args>
    void unset_flags(Args...) noexcept;

protected:
    terminal_interface();

private:
    void check_screen_resolution(int size) const
    {
	if (size < std::numeric_limits<unsigned short>::min() ||
	    size > std::numeric_limits<unsigned short>::max())
	{
	    throw std::out_of_range {"screen resolution exceeded"};
	}
    }

private:
    ::termios old_termios, new_termios;
    ::winsize old_winsize, new_winsize;
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
