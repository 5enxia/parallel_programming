#!/bin/bash
#-----------------------------------

# slrum
#-----------------------------------
#SBATCH --partition AM
#SBATCH --output %x.o%j
#SBATCH --time=10:00
#-----------------------------------

#-----------------------------------
# cd $SLURM_SUBMIT_DIR
#-----------------------------------

# exec
#-----------------------------------
echo '1 threads'
OMP_NUM_THREADS=1 ./a.out
echo '2 threads'
OMP_NUM_THREADS=2 ./a.out
echo '4 threads'
OMP_NUM_THREADS=4 ./a.out
echo '8 threads'
OMP_NUM_THREADS=8 ./a.out
#-----------------------------------

#-----------------------------------
exit 0
#-----------------------------------