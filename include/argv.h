/**
 * argv.h
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#ifndef RNG_ARGV_H
#define RNG_ARGV_H

#include "common.h"
#include "error.h"
#include "utils.h"

#define NUM_OPTIONS 2
#define OPT_DELIMIT "--"

typedef struct {
	char *value;
	char *alias;
	char *desc;
} option_t;

static option_t options[NUM_OPTIONS];
void usage(void);

#endif /* RNG_ARGV_H */
