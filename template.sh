#!/bin/bash
#-----------------------------------

# slrum
#-----------------------------------
#SBATCH --partition CM
#SBATCH --output %x.o%j
#SBATCH --time=10:00
#-----------------------------------

#-----------------------------------
cd $SLURM_SUBMIT_DIR
#-----------------------------------

# exec
#-----------------------------------
if [ $# -eq 0 ]
    then
    ./hello
else
    OMP_NUM_THREADS=$1 ./hello
fi
#-----------------------------------

#-----------------------------------
exit 0
#-----------------------------------