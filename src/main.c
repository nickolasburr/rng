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
	char *line, *range, *token;
	size_t len;
	ssize_t read;
	FILE *stream = NULL;

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

	/**
	 * At minimum, require a range argument.
	 */
	if (argc < 2) {
		fprintf(stderr, "%s: Invalid number of arguments\n", PROGNAME);

		exit(EXIT_FAILURE);
	}

	start = 0;
	end = 0;

	for (index = 1; index < argc; index += 1) {
		switch (index) {
			case 1:
				range = ALLOC(sizeof(argv[index]) + NULL_BYTE);
				copy(range, argv[index]);

				zindex = 0;

				while ((token = strsep(&range, ","))) {
					if (!is_numeric(token)) {
						fprintf(stderr, "%s: '%s' is not a valid range.\n\n", PROGNAME, argv[index]);
						usage();

						exit(EXIT_FAILURE);
					}

					switch (zindex) {
						case 0:
							start = (int) strtoul(token, NULL, 0);

							break;
						case 1:
							end = (int) strtoul(token, NULL, 0);

							break;
						default:
							break;
					}

					zindex++;
				}

				break;
			case 2:
				if (!is_file(argv[index])) {
					fprintf(stderr, "%s: '%s' is not a valid filename.\n\n", PROGNAME, argv[index]);

					exit(EXIT_FAILURE);
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
		if (count >= start && (count <= end || !end)) {
			fwrite(line, read, 1, stdout);
		}

		count++;
	}

	return EXIT_SUCCESS;
}
