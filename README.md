# rng

An elegant alternative to `sed -n '<START>,<END>p'`.

## Examples

Get lines 7-15 in `file.txt`.

```
rng 7,15 < file.txt
```

Skip the first 4 lines of input.

```
echo -e "First\nSecond\nThird\nFourth\nFifth\n" | rng 5
```
