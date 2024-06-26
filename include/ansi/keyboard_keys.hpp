#pragma once

#include <concepts>

namespace ansi::escape
{
    enum class keyboard;
    enum class keypad;

    inline keyboard keyboard_enumerator(const char*, std::size_t);

    template<std::contiguous_iterator T>
    inline keyboard keyboard_enumerator(T, T);

    keyboard keyboard_enumerator(std::string_view);
}

enum class ansi::escape::keyboard {
    backspace = 0,
    delete_key,
    down_arrow,
    end_key,
    enter,
    home_key,
    // insert_key,
    left_arrow,
    page_down,
    page_up,
    // pause_break,
    // print_screen,
    right_arrow,
    tab,
    up_arrow,
    // f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    // f10,
    // f11,
    f12,
    alt_a,
    ctrl_a,
    alt_b,
    ctrl_b,
    alt_c,
    ctrl_c,
    alt_d,
    ctrl_d,
    alt_e,
    ctrl_e,
    alt_f,
    ctrl_f,
    alt_g,
    ctrl_g,
    alt_h,
    ctrl_h,
    alt_i,
    ctrl_i,
    alt_j,
    ctrl_j,
    alt_k,
    ctrl_k,
    alt_l,
    ctrl_l,
    alt_m,
    ctrl_m,
    alt_n,
    ctrl_n,
    alt_o,
    ctrl_o,
    alt_p,
    ctrl_p,
    alt_q,
    ctrl_q,
    alt_r,
    ctrl_r,
    alt_s,
    ctrl_s,
    alt_t,
    ctrl_t,
    alt_u,
    ctrl_u,
    alt_v,
    ctrl_v,
    alt_w,
    ctrl_w,
    alt_x,
    ctrl_x,
    alt_y,
    ctrl_y,
    alt_z,
    ctrl_z,
    undefined
};

enum class ansi::escape::keypad {
    home_key = 0,
    up_arrow,
    page_up,
    left_arrow,
    right_arrow,
    end_key,
    down_arrow,
    page_down,
    insert_key,
    delete_key
};

ansi::escape::keyboard
inline ansi::escape::keyboard_enumerator(const char* pointer, std::size_t size)
{
    return keyboard_enumerator(std::string_view {pointer, size});
}

template<std::contiguous_iterator T>
ansi::escape::keyboard
inline ansi::escape::keyboard_enumerator(T first, T last)
{
    return keyboard_enumerator(std::string_view {first, last});
}
