/**
 * utils.c
 *
 * Copyright (C) 2018 Nickolas Burr <nickolasburr@gmail.com>
 */

#include "utils.h"

/**
 *
 * String utilities (syntactic sugar, mostly)
 *
 */

/**
 * GNU `basename` polyfill.
 */
char *base_name (char *path) {
	char *base = strrchr(path, '/');

	return base ? (base + 1) : path;
}

/**
 * `strcmp` wrapper
 */
int compare (char *one, char *two) {
	return strcmp(one, two);
};

/**
 * `strcat` wrapper
 */
char *concat (char *buf, char *str) {
	return strcat(buf, str);
}

/**
 * `strcpy` wrapper
 */
char *copy (char *buf, char *str) {
	return strcpy(buf, str);
}

/**
 * GNU `dirname` polyfill.
 */
char *dir_name (char *path) {
	static const char *dot = ".";
	char *pslash;

	/**
	 * Get trailing slash.
	 */
	pslash = !is_null(path)
	       ? strrchr(path, '/')
	       : NULL;

	if (pslash == path) {
		++pslash;
	} else if (!is_null(pslash) && pslash[1] == '\0') {
		pslash = memchr(path, pslash - path, '/');
	}

	if (!is_null(pslash)) {
		pslash[0] = '\0';
	} else {
		path = (char *) dot;
	}

	return path;
}

/**
 * Get index of element in array.
 */
int index_of (char *element, char **array, size_t size) {
	unsigned int i;

	for (i = 0; i < size; i += 1) {
		if (!compare(array[i], element)) {
			return i;
		}
	}

	return -1;
}

/**
 * Check if element exists in array.
 */
int in_array (char *element, char **array, size_t size) {
	unsigned int i;

	for (i = 0; i < size; i += 1) {
		if (!compare(array[i], element)) {
			return 1;
		}
	}

	return 0;
}

/**
 * `strlen` wrapper
 */
int length (char *str) {
	return strlen(str);
}

/**
 * Basic `strtok_r` wrapper (derived from https://stackoverflow.com/a/9210560/4322351)
 */
char **str_split (char *str, const char delim) {
	size_t count, index;
	char *tmp, *token, *lastcomma, *ptr;
	char **result;
	char _delim[2];

	count = 0;
	result = 0;
	lastcomma = 0;
	tmp = str;
	_delim[0] = delim;
	_delim[1] = 0;

	while (*tmp) {
		if (_delim == *tmp) {
			count++;
			lastcomma = tmp;
		}

		tmp++;
	}

	count += (lastcomma < (str + strlen(str) - 1));
	count++;

	result = ALLOC(sizeof(char *) * count);

	if (result) {
		index = 0;
		token = strtok_r(str, _delim, &ptr);

		while (token) {
			assert(index < count);
			*(result + index++) = strdup(token);
			token = strtok_r(NULL, _delim, &ptr);
        }

		assert(index == (count - 1));
		*(result + index) = 0;
	}

	return result;
}

/**
 *
 * Filesystem utilities
 *
 */

/**
 * Get pointer to directory by its pathname.
 */
DIR *get_dir (int *error, const char *path) {
	DIR *dp;

	*error = 0;

	if (!(dp = opendir(path))) {
		*error = 1;
	}

	return dp;
}

/**
 * Get pointer to file by its pathname.
 */
FILE *get_file (int *error, const char *filename, const char *filemode) {
	FILE *fp = fopen(filename, filemode);

	*error = 0;

	if (is_null(fp)) {
		*error = 1;
	}

	return fp;
}

/**
 * Get pointer to pipe.
 */
FILE *open_pipe (int *error, const char *command, const char *pipemode) {
	FILE *fp = popen(command, pipemode);

	*error = 0;

	if (is_null(fp)) {
		*error = 1;
	}

	return fp;
}

/**
 * Close pointer to pipe.
 */
int close_pipe (FILE *fp) {
	return pclose(fp);
}

/**
 * Determine if pathname is a directory.
 *
 * @note Adapted from https://goo.gl/ZmWfbx
 */
int is_dir (const char *path) {
	struct dirent *de;
	int is_dir, error;
	DIR *dp = get_dir(&error, path);

	if (!error) {
		while ((de = readdir(dp))) {
		#ifdef _DIRENT_HAVE_D_TYPE
			if (de->d_type != DT_UNKNOWN && de->d_type != DT_LNK) {
				is_dir = (de->d_type == DT_DIR);
			} else
		#endif
			{
				struct stat st;

				stat(de->d_name, &st);
				is_dir = S_ISDIR(st.st_mode);
			}

			if (is_dir) {
				return 1;
			}
		}
	}

	return 0;
}

/**
 * Determine if pathname is a regular file.
 *
 * @note Adapted from https://goo.gl/ZmWfbx
 */
int is_file (const char *path) {
	struct stat st;

	if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) {
		return 1;
	}

	return 0;
}

/**
 * Determine if pathname is writable.
 */
int is_writable (const char *path) {
	if (!access(path, W_OK)) {
		return 1;
	}

	return 0;
}

/**
 *
 * Type utilities
 *
 */

/**
 * `isdigit` wrapper
 */
int is_digit (int c) {
	return isdigit(c);
}

/**
 * Determine if pointer is a null pointer.
 */
int is_null (void *ptr) {
	if (ptr == NULL) {
		return 1;
	}

	return 0;
}

/**
 * Determine if string is numeric.
 */
int is_numeric (char *str) {
	int index;

	index = 0;

	while (str[index] != '\0') {
		if (!is_digit(str[index])) {
			return 0;
		}

		index++;
	}

	return 1;
}
