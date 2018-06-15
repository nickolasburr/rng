/**
 * main.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#include "main.h"

/**
 * Usage:
 *
 * rng 5,35 < filename
 * cat filename | rng 5,35
 */

int main (int argc, char **argv) {
	int index, opt_value, long_opt_index;
	char **tokens;

	long_opt_index = 0;

	static struct option long_options[] = {
		{ "help", no_argument, 0, 'h' },
		{ "version", no_argument, 0, 'v' },
	};

	while ((opt_value = getopt_long(argc, argv, "hv", long_options, &long_opt_index)) != -1) {
		switch (opt_value) {
			case 'h':
				usage();

				exit(EXIT_SUCCESS);
			case 'v':
				fprintf(stdout, "%s\n", RNG_VERSION);

				exit(EXIT_SUCCESS);
			case '?':
				usage();

				exit(EXIT_FAILURE);
		}
	}

	if (argc != 2) {
		fprintf(stderr, "%s: Invalid number of arguments\n", PROGNAME);

		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "argc: %d\n", argc);
	fprintf(stdout, "argv[1]: %s\n", argv[1]);

	tokens = str_split(argv[1], ',');

	if (tokens) {
		for (index = 0; *(tokens + index); index += 1) {
			fprintf(stdout, "Line number: %s\n", *(tokens + index));
			FREE(*(tokens + index));
		}

		fprintf(stdout, "\n");
		FREE(tokens);
	}

	return EXIT_SUCCESS;
}
