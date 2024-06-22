#include "terminal/screen_interface.hpp"

#include <cstdio>
#include <string>

std::string
terminal::screen_interface::rgb_color(color_format format, int r, int g, int b) const
{
    constexpr std::string_view ansi_color_format[] = {
	"\033[48;5;%dm",
	"\033[48;2;%d;%d;%dm",
	"\033[38;5;%dm",
	"\033[38;2;%d;%d;%dm"
    };

    constexpr static int color_buffer_size = 20;

    std::string buf;

    buf.reserve(color_buffer_size);

    switch (format)
    {

    using enum color_format;
	
    case background_256:
    case foreground_256:
	if (rgb_color_control(r))
	{
	    std::snprintf(buf.data(),
			  buf.capacity(),
			  ansi_color_format[static_cast<int>(format)].data(),
			  r);
	}

	break;

    case background_rgb:
    case foreground_rgb:
	if (rgb_color_control(r) &&
	    rgb_color_control(g) &&
	    rgb_color_control(b))
	{
	    std::snprintf(buf.data(),
			  buf.capacity(),
			  ansi_color_format[static_cast<int>(format)].data(),
			  r, g, b);
	}

	break;
    }

    return buf.data();
}
