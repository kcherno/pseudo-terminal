#pragma once

#include <concepts>

extern "C"
{

#include <termios.h>

}

namespace terminal
{
    enum class baud_rate;

    constexpr int actual_baud_rate(baud_rate) noexcept;

    enum class input_mode;
    enum class local_mode;

    template<typename T>
    concept terminal_flag =
	std::same_as<input_mode, T> ||
	std::same_as<local_mode, T>;

    enum class optional_actions;
}

enum class terminal::baud_rate {
    baud_0       = B0,
    baud_50      = B50,
    baud_75      = B75,
    baud_110     = B110,
    baud_134     = B134,
    baud_150     = B150,
    baud_200     = B200,
    baud_300     = B300,
    baud_600     = B600,
    baud_1200    = B1200,
    baud_1800    = B1800,
    baud_2400    = B2400,
    baud_4800    = B4800,
    baud_9600    = B9600,
    baud_19200   = B19200,
    baud_38400   = B38400,
    baud_57600   = B57600,
    baud_115200  = B115200,
    baud_230400  = B230400,
    baud_460800  = B460800,
    baud_500000  = B500000,
    baud_576000  = B576000,
    baud_921600  = B921600,
    baud_1000000 = B1000000,
    baud_1152000 = B1152000,
    baud_1500000 = B1500000,
    baud_2000000 = B2000000
};

constexpr int terminal::actual_baud_rate(baud_rate speed) noexcept
{
    switch (speed)
    {
	using enum baud_rate;

    case baud_0:       return 0;
    case baud_50:      return 50;
    case baud_75:      return 75;
    case baud_110:     return 110;
    case baud_134:     return 134;
    case baud_150:     return 150;
    case baud_200:     return 200;
    case baud_300:     return 300;
    case baud_600:     return 600;
    case baud_1200:    return 1200;
    case baud_1800:    return 1800;
    case baud_2400:    return 2400;
    case baud_4800:    return 4800;
    case baud_9600:    return 9600;
    case baud_19200:   return 19200;
    case baud_38400:   return 38400;
    case baud_57600:   return 57600;
    case baud_115200:  return 115200;
    case baud_230400:  return 230400;
    case baud_460800:  return 460800;
    case baud_500000:  return 500000;
    case baud_576000:  return 576000;
    case baud_921600:  return 921600;
    case baud_1000000: return 1000000;
    case baud_1152000: return 1152000;
    case baud_1500000: return 1500000;
    case baud_2000000: return 2000000;

    default:           return -1;

    }
}

enum class terminal::input_mode {
    brkint  = BRKINT,
    icrnl   = ICRNL,
    ignbrk  = IGNBRK,
    igncr   = IGNCR,
    ignpar  = IGNPAR,
    imaxbel = IMAXBEL,
    inlcr   = INLCR,
    inpck   = INPCK,
    istrip  = ISTRIP,
    iuclc   = IUCLC,
    iutf8   = IUTF8,
    ixany   = IXANY,
    ixoff   = IXOFF,
    ixon    = IXON,
    parmrk  = PARMRK
};

enum class terminal::local_mode {
    echo    = ECHO,
    echoctl = ECHOCTL,
    echoe   = ECHOE,
    echok   = ECHOK,
    echoke  = ECHOKE,
    echonl  = ECHONL,
    echoprt = ECHOPRT,
    icanon  = ICANON,
    iexten  = IEXTEN,
    isig    = ISIG,
    noflsh  = NOFLSH,
    tostop  = TOSTOP
};

enum class terminal::optional_actions {
    drain = TCSADRAIN,
    flush = TCSAFLUSH,
    now   = TCSANOW
};
