#!/bin/sh
#module add mpi/openmpi-local
module add openmpi
mpicc cpi.c -o cpi

