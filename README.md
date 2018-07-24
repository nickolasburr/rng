# rng

`rng` is a friendly, flexible alternative to `sed -n '<START>,<END>p'`.

## Table of Contents

- [Installation](#installation)
  + [Homebrew](#homebrew)
  + [Source](#source)
- [Notes](#notes)
- [Examples](#examples)

## Installation

You can install `rng` via Homebrew or manually.

### Homebrew

```
brew tap nickolasburr/pfa
brew install rng
```

### Source

```
git clone https://github.com/nickolasburr/rng.git
cd rng
make
make install
```

By default, files are installed to `/usr/local` You can install to an alternate location by passing `PREFIX` to `make install`.

For example, `make install PREFIX=/opt`

## Notes

Certain range values can be omitted if they can be properly implied. To get multiple ranges, use the colon (`:`) operator.

## Examples

Get lines 7-15 in `Makefile`.

```
rng 7,15 Makefile
```

Skip the first 4 lines of input.

```
echo -e "First\nSecond\nThird\nFourth\nFifth" | rng 5
```

Output lines 1-25 in `Makefile`.

```
rng ,25 Makefile
```

Get lines 5-10 and 17-22 in `main.c`.

```
rng 5,10:17,22 main.c
```

Output all lines except 11-19 in main.c

```
rng ,10:20, main.c
```
