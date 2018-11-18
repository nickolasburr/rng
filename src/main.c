/**
 * main.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#include "main.h"

int main (int argc, char **argv) {
	int i, n;
	int start, end, count;
	int pairs, index, zindex;
	int opt_value, long_opt_index;
	size_t len;
	ssize_t read;
	FILE *stream = NULL;
	Range_T **ranges;
	Range_T *rng;
	char *ptr = NULL;
	char *range = NULL,
	     *urange = NULL;
	char *line = NULL,
	     *token = NULL;

	/**
	 * Designated getopt long options.
	 */
	static struct option long_options[] = {
		{ "help", no_argument, 0, 'h' },
		{ "version", no_argument, 0, 'v' },
	};

	long_opt_index = 0;

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

	/**
	 * At minimum, require a range argument.
	 */
	if (argc < 2) {
		fprintf(stderr, "%s: Invalid number of arguments\n", PROGNAME);

		exit(EXIT_FAILURE);
	}

	i = 0;
	n = 1;

	/**
	 * User-provided range[s].
	 */
	urange = argv[1];

	while (urange[i++]) {
		if (urange[i] == ':') {
			n++;
		}
	}

	pairs = 0;
	ranges = ALLOC(sizeof(*ranges) * n);

	for (index = 1; index < argc; index += 1) {
		/**
		 * Use positional context to determine
		 * the anticipated type of argument.
		 */
		switch (index) {
			case 1:
				/**
				 * Get range[s] from ranges string.
				 */
				for (range = strtok_r(argv[index], ":", &ptr); !is_null(range); range = strtok_r(NULL, ":", &ptr)) {
					zindex = 0;

					rng = ALLOC(sizeof(rng));

					/**
					 * Default <START>,<END> values.
					 */
					rng->start = 0;
					rng->end = 0;

					/**
					 * Split the range into tokens.
					 */
					while ((token = strsep(&range, ","))) {
						if (!is_numeric(token)) {
							fprintf(stderr, "%s: '%s' is not a valid range value.\n\n", PROGNAME, token);

							usage();

							goto on_error;
						}

						switch (zindex) {
							case 0:
								rng->start = (unsigned int) strtoul(token, NULL, 0);

								break;
							case 1:
								rng->end = (unsigned int) strtoul(token, NULL, 0);

								break;
							default:
								break;
						}

						zindex++;
					}

					ranges[pairs++] = rng;
				}

				break;
			case 2:
				if (!is_file(argv[index])) {
					fprintf(stderr, "%s: '%s' is not a valid filename.\n", PROGNAME, argv[index]);

					goto on_error;
				}

				stream = fopen(argv[index], "r");

				break;
			default:
				break;
		}
	}

	/**
	 * In the absence of a filename, read from STDIN.
	 */
	if (is_null(stream)) {
		stream = stdin;
	}

	count = 1;

	while ((read = getline(&line, &len, stream)) != -1) {
		for (index = 0; index < pairs; index += 1) {
			if (count >= ranges[index]->start && (count <= ranges[index]->end || !ranges[index]->end)) {
				fwrite(line, read, 1, stdout);
			}
		}

		count++;
	}

	/**
	 * Run clean-up tasks.
	 */
	for (index = 0; index < pairs; index += 1) {
		FREE(ranges[index]);
	}

	FREE(ranges);

	return EXIT_SUCCESS;

on_error:
	/**
	 * Run clean-up tasks.
	 */
	for (index = 0; index < pairs; index += 1) {
		FREE(ranges[index]);
	}

	FREE(ranges);

	return EXIT_FAILURE;
}
