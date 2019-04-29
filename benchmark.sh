#!/bin/bash

N=500;
for prob in narrow_20 narrow_10 narrow_05 narrow_03 sitterson circular_maze; do
	for m in 40 80 120 160; do
		./holonomic_2d_planning -f test_data/$prob -n 20 -k 5 -m $m -N $N > $prob-$m.log
	done
done