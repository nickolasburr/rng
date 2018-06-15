#!/bin/sh

set -ex

PREFIX=/usr/local
BINDIR=$PREFIX/bin

RM="rm"
RMFLAGS="-rf"

TARGET="rng"
MANPAGE="$TARGET.1.gz"
MANDEST=$PREFIX/share/man/man1

$RM $RMFLAGS $BINDIR/$TARGET $MANDEST/$MANPAGE
