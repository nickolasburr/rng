/**
 * main.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#include "main.h"

/**
 * Usage:
 *
 * rng 5:35 -f filename
 * cat filename | rng 5:35
 */

int main (int argc, char **argv) {
	int opt_value, long_opt_index;

	long_opt_index = 0;

	static struct option long_options[] = {
		{ "help", no_argument, 0, 'h' },
		{ "version", no_argument, 0, 'v' },
	};

	while ((opt_value = getopt_long(argc, argv, "fhv", long_options, &long_opt_index)) != -1) {
		switch (opt_value) {
			case 'h':
				usage();

				break;
			case 'v':
				fprintf(stdout, "%s\n", RNG_VERSION);

				exit(EXIT_SUCCESS);
			case '?':
				usage();

				exit(EXIT_FAILURE);
		}
	}
}
