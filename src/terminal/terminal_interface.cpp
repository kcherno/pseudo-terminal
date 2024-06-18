#include <system_error>
#include <cerrno>

extern "C"
{

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

}

#include "terminal/terminal_interface.hpp"

terminal::terminal_interface::terminal_interface()
{
    if (::isatty(STDIN_FILENO) == 0 || ::isatty(STDOUT_FILENO) == 0)
	throw std::system_error {errno, std::system_category(), __func__};

    if (::tcgetattr(STDIN_FILENO, &old_termios) == -1)
	throw std::system_error {errno, std::system_category(), __func__};

    if (::ioctl(STDIN_FILENO, TIOCGWINSZ, &old_winsize) == -1)
	throw std::system_error {errno, std::system_category(), __func__};

    new_termios = old_termios;
    new_winsize = old_winsize;
}
