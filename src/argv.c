/**
 * argv.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#include "argv.h"

static option_t options[] = {
	{
		"--file",
		"-f",
		"File whose contents are sent to STDIN.",
	},
	{
		"--help",
		"-h",
		"Show help information.",
	},
	{
		"--version",
		"-v",
		"Show version number.",
	},
};

/**
 * Print usage information.
 */
void usage (void) {
	int index;
	char fvalue[36];

	fprintf(stdout, "Usage: rng [OPTIONS]\n\n");
	fprintf(stdout, "Options:\n\n");

	for (index = 0; index < NUM_OPTIONS; index += 1) {
		option_t *option = &options[index];

		/**
		 * Format option->value string.
		 */
		copy(fvalue, option->value);
		concat(fvalue, ",");

		fprintf(stdout, "%4s%-22s %s: %-24s\n", "", fvalue, option->alias, option->desc);
	}
}
