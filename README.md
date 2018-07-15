# rng

`rng` is a friendly, flexible alternative to `sed -n '<START>,<END>p'`.

## Table of Contents

- [Installation](#installation)
  + [Homebrew](#homebrew)
  + [Source](#source)
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

## Examples

Get lines 7-15 in `file.txt`.

```
rng 7,15 file.txt
```

Skip the first 4 lines of input.

```
echo -e "First\nSecond\nThird\nFourth\nFifth" | rng 5
```
