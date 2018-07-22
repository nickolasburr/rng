/**
 * main.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 *
 * Usage:
 *
 * rng 5,35 <FILE>
 * cat <FILE> | rng 5,35
 */

#include "main.h"

int main (int argc, char **argv) {
	int index, zindex;
	int count, start, end, opt_value, long_opt_index;
	size_t len;
	ssize_t read;
	FILE *stream = NULL;
	char *ptr = NULL;
	char *range = NULL;
	char *line = NULL,
	     *token = NULL;
	Range_T **ranges;
	Range_T *rng;

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
	 * At minimum, require a range argument. This is enforced to
	 * prevent rng from being [mis]used the way cat is [mis]used.
	 */
	if (argc < 2) {
		fprintf(stderr, "%s: Invalid number of arguments\n", PROGNAME);

		exit(EXIT_FAILURE);
	}

	start = 0;
	end = 0;

	int track = 0;
	ranges = ALLOC(sizeof(ranges));

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

					fprintf(stdout, "1.) range: %s\n", range);

					rng = ALLOC(sizeof(rng));
					rng->start = 0;
					rng->end = 0;

					/**
					 * Split the range into tokens.
					 */
					while ((token = strsep(&range, ","))) {
						fprintf(stdout, "2.) token: %s\n", token);

						if (!is_numeric(token)) {
							fprintf(stderr, "%s: '%s' is not a valid range.\n\n", PROGNAME, argv[index]);

							usage();

							goto on_error;
						}

						switch (zindex) {
							case 0:
								rng->start = (int) strtoul(token, NULL, 0);

								break;
							case 1:
								rng->end = (int) strtoul(token, NULL, 0);

								break;
							default:
								break;
						}

						zindex++;
					}

					RESIZE(ranges, sizeof(rng));
					ranges[track++] = rng;
				}

				break;
			case 2:
				if (!is_file(argv[index])) {
					fprintf(stderr, "%s: '%s' is not a valid filename.\n\n", PROGNAME, argv[index]);

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
	int t;

	while ((read = getline(&line, &len, stream)) != -1) {
		for (t = 0; t < track; t++) {
			// fprintf(stdout, "track: %d\n", track);
			// fprintf(stdout, "ranges[t]->start: %d\n", ranges[t]->start);
			// fprintf(stdout, "ranges[t]->end: %d\n", ranges[t]->end);

			if (count >= ranges[t]->start && (count <= ranges[t]->end || !ranges[t]->end)) {
				fwrite(line, read, 1, stdout);
			}
		}

		count++;
	}

	FREE(range);

	return EXIT_SUCCESS;

on_error:
	FREE(range);

	return EXIT_FAILURE;
}
