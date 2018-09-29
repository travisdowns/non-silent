See the associated [stackoverflow question](https://stackoverflow.com/q/52565303) first.

This version of the code requires linux, although you could fairly easily compile it on another
platform (but how would you measure the performance counters).

## Building

Just run `make`.

## Run Perf

I collected the results like:

```
for i in {4..20}; do
  s=$((2**i))
  perf stat -x, -D498 -e l2_lines_in.all:u,l2_lines_out.silent:u,l2_lines_out.non_silent:u,l2_trans.l2_wb ./non-silent $s
done |& tee results
```

You can use `transpose.sh` to parse the results file into a csv suitable for graphing, like: `transpose.sh results`.
