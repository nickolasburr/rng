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

#define OPT_LSEP "--"

typedef struct {
	char *key;
	int value;
} method_t;

typedef struct {
	char *value;
	char *alias;
	char *desc;
} option_t;

static method_t methods[NUM_METHODS];
static option_t options[NUM_OPTIONS];

int get_bitmask_from_key(char *);
void usage(void);

#endif /* RNG_ARGV_H */
