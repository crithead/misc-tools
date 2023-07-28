# Coin Flip

_coinflip_ is a program that generates a stream of data by adding values, +1 or
-1, from a stream of random bits.  Graphing the resulting data produces plots
that are indistinguishable from those of stock prices.  This idea comes from
Benoit Mandelbrot's _The (Mis)Behavior of Markets_.


## Basic Usage

Examples

```sh
./cf -h
./cf -t PQR -n 22500
```
1.  Print the usage information.
2.  Generate 22,500 points with the title ``PQR'' 

## Adjusting Data

The `adjust` tool can shift or scale the points in the data into a desired
range.

Examples

```sh
./cf -n 10 ; cat default.data                             <1>
./adjust -a default.data                                  <2>
./adjust -f 10 default.data; cat default.data             <3>
./adjust -c 10 default.data; cat default.data             <4>
./adjust -f 10 -c 20 default.data; cat default.data       <5>
./adjust -o 100 default.data; cat default.data            <6>
```

1. Generate a data set of 10 points
2. Print information about the data set
3. Shift the data so that the least value is 10
4. Shift the data so that the greatest value is 10
5. Scale the data so that the least value is 10 and the greatest value is 20
6. Add 100 to each data point

# Combining Data Sets

Several data files can be combined using the +join+ tool.  It joins two sets
of data on a common sorted column.  Each line has the 'x' coordinate in column
1 and data sets 'a', 'b', 'c', and 'd' in columns 2, 3, 4, and 5.

```sh
join a.data b.data > ab.data
join c.data d.data > cd.data
join ab.data cd.data > abcd.data
```

The resulting data can be plotted with

```gnuplot
set title 'Coin Flip'
set term png size 800, 600
set output "abcd.png"
plot for [i=2:5] "abcd.data" using 1:i with lines title columnheaders
```

## Financial Plots

```sh
./cf -n 22500 XYZA                                    <1>
python3 financials.py XYZA.data                       <2>
gnuplot financials.plt                                <3>
```

1.  Generate 1 year (250 days) of coinflip data at 5 minutes intervals
2.  Calculate daily (open, low, high, close)
3.  Plot daily (o, l, h, c)
-   Note: Change +NAME = ``XYZA''+ in 'financials.plt' before plotting
    the data.

## To Do

* DONE: Add a '-c' option to print the count value on each data line
* DONE: Add a '-d' option to add a data header as a column header
* DONE: Add a '-t' for the plot title
* DONE: Add a 'adjust' tool to make adjustments to the data file
* Improve documentation comments
* Generate multicolumn output
* Add ``technical analysis'' to plots

