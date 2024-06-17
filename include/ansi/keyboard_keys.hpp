#pragma once

namespace ansi::escape
{
    enum class keyboard;
    enum class keypad;

    keyboard get_keyboard_key(std::string_view);
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
