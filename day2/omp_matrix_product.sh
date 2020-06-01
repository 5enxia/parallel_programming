#!/bin/bash
#-----------------------------------

# slrum
#-----------------------------------
#SBATCH --partition AM
#SBATCH --output %x.o%j
#SBATCH --time=10:00
#-----------------------------------

#-----------------------------------
cd $SLURM_SUBMIT_DIR
#-----------------------------------

# info
#-----------------------------------
date
hostname
lscpu
#-----------------------------------

# param
#-----------------------------------
N=10000
#-----------------------------------

# exec
#-----------------------------------
echo '1 threads'
OMP_NUM_THREADS=1 ./omp_matrix_product $N
echo '2 threads'
OMP_NUM_THREADS=2 ./omp_matrix_product $N 
echo '4 threads'
OMP_NUM_THREADS=4 ./omp_matrix_product $N 
echo '8 threads'
OMP_NUM_THREADS=8 ./omp_matrix_product $N 
echo '16 threads'
OMP_NUM_THREADS=16 ./omp_matrix_product $N 
#-----------------------------------

#-----------------------------------
exit 0
#-----------------------------------