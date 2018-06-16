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
	int count, index, start, end, opt_value, long_opt_index;
	char *line, *range, *token;
	size_t len;
	ssize_t read;

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

	index = 0;
	start = 0;
	end = 0;

	range = ALLOC(sizeof(argv[1]));
	copy(range, argv[1]);

	while ((token = strsep(&range, ","))) {
		if (!is_numeric(token)) {
			fprintf(stderr, "%s: '%s' is not a valid integer\n\n", PROGNAME, token);

			usage();

			exit(EXIT_FAILURE);
		}

		switch (index) {
			case 0:
				start = atoi(token);

				break;
			case 1:
				end = atoi(token);

				break;
			default:
				break;
		}

		index++;
	}

	count = 1;

	while ((read = getline(&line, &len, stdin)) != -1) {
		if (count >= start && (count <= end || !end)) {
			fwrite(line, read, 1, stdout);
		}

		count++;
	}

	return EXIT_SUCCESS;
}
