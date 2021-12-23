#!/bin/sh
#module add mpi/openmpi-local
module add openmpi
mpic++ cpi.cpp -o cpi

