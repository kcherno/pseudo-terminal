#include <unordered_map>
#include <string_view>

#include "ansi/keyboard_keys.hpp"

ansi::escape::keyboard ansi::escape::get_keyboard_key(std::string_view key)
{
    const static std::unordered_map<std::string_view, keyboard> keys {
	{"\177",     keyboard::backspace},
	{"\033[3~",  keyboard::delete_key},
	{"\033[B",   keyboard::down_arrow},
	{"\033[F",   keyboard::end_key},
	{"\n",       keyboard::enter},
	{"\033[H",   keyboard::home_key},
	{"\033[D",   keyboard::left_arrow},
	{"\033[6~",  keyboard::page_down},
	{"\033[5~",  keyboard::page_up},
	{"\033[C",   keyboard::right_arrow},
	{"\t",       keyboard::tab},
	{"\033[A",   keyboard::up_arrow},
	{"\033OQ",   keyboard::f2},
	{"\033OR",   keyboard::f3},
	{"\033OS",   keyboard::f4},
	{"\033[15~", keyboard::f5},
	{"\033[17~", keyboard::f6},
	{"\033[18~", keyboard::f7},
	{"\033[19~", keyboard::f8},
	{"\033[20~", keyboard::f9},
	{"\033[24~", keyboard::f12}
    };

    const auto iterator = keys.find(key);

    if (iterator == keys.cend())
	return keyboard::undefined;

    else
	return iterator->second;
}
