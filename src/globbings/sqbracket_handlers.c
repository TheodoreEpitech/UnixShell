/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Handlers for sqbracket globbing pattern
*/

#include "globber.h"

static int is_in_range(char start, char end, char c)
{
    if (start > end) {
        return (end <= c && c <= start);
    } else if (start == end) {
        return (c == start);
    } else {
        return (start <= c && c <= end);
    }
}

static int is_in_array(const char *array, char c)
{
    for (; *array != ']'; array++) {
        if (*array == c) {
            return 1;
        }
        if (!*array) {
            return 84;
        }
    }
    return 0;
}

static int handle_sqbracket_internal(const char *pattern, const char *str)
{
    if (!*pattern || !*str) {
        return 0;
    }
    if (pattern[1] == '-') {
        if (is_in_range(pattern[0], pattern[2], *str)) {
            return 1;
        }
        return 0;
    }
    if (is_in_array(pattern, *str) == 1) {
        return 1;
    }
    return 0;
}

int handle_sqbracket_neg(const char *pattern, const char *str)
{
    int res = handle_sqbracket_internal(pattern, str);

    if (res == 1) {
        return 0;
    }
    if (res == 0) {
        for (; *pattern && *pattern != ']'; pattern++);
        return is_match(++pattern, ++str);
    }
    return 84;
}

int handle_sqbracket_pos(const char *pattern, const char *str)
{
    int res = handle_sqbracket_internal(pattern, str);

    if (res == 1) {
        for (; *pattern && *pattern != ']'; pattern++);
        return is_match(++pattern, ++str);
    }
    if (res == 0) {
        return 0;
    }
    return 84;
}
