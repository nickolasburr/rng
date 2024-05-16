/**
 * common.h
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#ifndef RNG_COMMON_H
#define RNG_COMMON_H

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __APPLE__
#include <limits.h>
#else
#include <linux/limits.h>
#endif

#define is_null(ptr) ((ptr) == ((void *) 0))

#define PROGNAME "rng"
#define RNG_VERSION "1.0.3"

#define _GNU_SOURCE
#define NULL_DEVICE "/dev/null"
#define NULL_BYTE 1

#endif /* RNG_COMMON_H */
