#include <unordered_map>
#include <string_view>

#include "ansi/keyboard_keys.hpp"

ansi::escape::keyboard ansi::escape::keyboard_enumerator(std::string_view key)
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
	{"\033[24~", keyboard::f12},
        {"\033a",    keyboard::alt_a},
        {"\1",       keyboard::ctrl_a},
        {"\033b",    keyboard::alt_b},
        {"\2",       keyboard::ctrl_b},
        {"\033c",    keyboard::alt_c},
        {"\3",       keyboard::ctrl_c},
        {"\033d",    keyboard::alt_d},
        {"\4",       keyboard::ctrl_d},
        {"\033e",    keyboard::alt_e},
        {"\5",       keyboard::ctrl_e},
        {"\033f",    keyboard::alt_f},
        {"\6",       keyboard::ctrl_f},
        {"\033g",    keyboard::alt_g},
        {"\7",       keyboard::ctrl_g},
        {"\033h",    keyboard::alt_h},
        {"\8",       keyboard::ctrl_h},
        {"\033i",    keyboard::alt_i},
        {"\9",       keyboard::ctrl_i},
        {"\033j",    keyboard::alt_j},
        {"\10",      keyboard::ctrl_j},
        {"\033k",    keyboard::alt_k},
        {"\11",      keyboard::ctrl_k},
        {"\033l",    keyboard::alt_l},
        {"\12",      keyboard::ctrl_l},
        {"\033m",    keyboard::alt_m},
        {"\13",      keyboard::ctrl_m},
        {"\033n",    keyboard::alt_n},
        {"\14",      keyboard::ctrl_n},
        {"\033o",    keyboard::alt_o},
        {"\15",      keyboard::ctrl_o},
        {"\033p",    keyboard::alt_p},
        {"\16",      keyboard::ctrl_p},
        {"\033q",    keyboard::alt_q},
        {"\17",      keyboard::ctrl_q},
        {"\033r",    keyboard::alt_r},
        {"\18",      keyboard::ctrl_r},
        {"\033s",    keyboard::alt_s},
        {"\19",      keyboard::ctrl_s},
        {"\033t",    keyboard::alt_t},
        {"\20",      keyboard::ctrl_t},
        {"\033u",    keyboard::alt_u},
        {"\21",      keyboard::ctrl_u},
        {"\033v",    keyboard::alt_v},
        {"\22",      keyboard::ctrl_v},
        {"\033w",    keyboard::alt_w},
        {"\23",      keyboard::ctrl_w},
        {"\033x",    keyboard::alt_x},
        {"\24",      keyboard::ctrl_x},
        {"\033y",    keyboard::alt_y},
        {"\25",      keyboard::ctrl_y},
        {"\033z",    keyboard::alt_z},
        {"\26",      keyboard::ctrl_z}
    };

    const auto iterator = keys.find(key);

    if (iterator == keys.cend())
	return keyboard::undefined;

    else
	return iterator->second;
}
