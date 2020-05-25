#!/bin/bash
#-----------------------------------

# slrum
#-----------------------------------
#SBATCH --partition CM
#SBATCH --output %x.o%j
#SBATCH --time=10:00
#-----------------------------------

# exec
#-----------------------------------
cd $SLURM_SUBMIT_DIR
if [ $# -eq 0 ]
    then
    ./omp_hw1
else
    OMP_NUM_THREADS=$1 ./omp_hw1
fi
exit 0
#-----------------------------------