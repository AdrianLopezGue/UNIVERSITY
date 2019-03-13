#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "recursivocontabla.eps"
set key right bottom
set xlabel "Tamano (n)"
set ylabel "Tiempo real (t)"
plot "recursivocontabla.txt" using 1:2 t "Tiempo real frente a n" w l, 'recursivocontabla.txt' using 1:3 t "Tiempo estimado frente a n" w l
_end_
