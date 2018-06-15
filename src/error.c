/**
 * error.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#include "error.h"

/**
 * A more expressive way of determining if an
 * error was encountered by comparing a return
 * value against a known error code (e.g. -1).
 */
int is_error (int value, int code) {
	return (value == code);
}
