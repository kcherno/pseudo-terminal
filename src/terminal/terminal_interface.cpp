#include <system_error>
#include <cerrno>

extern "C"
{

#include <termios.h>
#include <unistd.h>

}

#include "terminal/terminal_interface.hpp"

terminal::terminal_interface::terminal_interface()
{
    if (::isatty(STDIN_FILENO) == 0 || ::isatty(STDOUT_FILENO) == 0)
	throw std::system_error {errno, std::system_category(), __func__};

    if (::tcgetattr(STDIN_FILENO, &original_tattr) == -1)
	throw std::system_error {errno, std::system_category(), __func__};

    modified_tattr = original_tattr;
}
