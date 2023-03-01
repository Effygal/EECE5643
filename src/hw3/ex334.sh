#!/bin/sh
make ex334a
echo "with Service time drawn from Uniform(1.0, 2.0):"
for capacity in 0 1 2 3 4 5 6 
do
	./ex334a $capacity
done
make ex334b
echo "with Service time drawn from Uniform(1.0, 3.0):"
for capacityb in 0 1 2 3 4 5 6 
do
	./ex334b $capacityb
done
make clean
