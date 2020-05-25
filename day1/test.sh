#!/bin/bash

# SBATCH -p AM               # キュー「AM」を使用する
# SBATCH -o %x.o%j           # stdout と stderr の両方を xxxx.sh.oNNNN の名前で出力する

cd $SLURM_SUBMIT_DIR        # jobを投入したディレクトリに移動

# OMP_NUM_THREADS=8 

./omp_hw1

exit 0