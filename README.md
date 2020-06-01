# parallel_programming
## env
### local
- macOS mojave
- clang++
### server
- ubunt 18.04.4 LTS
- g++


## requirement (MacOS)
### libomp
```sh
brew install libomp
```

## how to complile
### local
```sh
clang++ -Xpreprocessor -fopenmp -lomp -O2 xxx.cpp -o xxx
```
### server
```sh
gcc++ -fopenmp xxx.cpp -o xxx
```


## Computing Node
- AM (24Cores)
- CM (8Cores)

## example job file
```sh
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

# exec
#-----------------------------------
OMP_NUM_THREADS=1 ./hello
OMP_NUM_THREADS=2 ./hello
OMP_NUM_THREADS=4 ./hello
#-----------------------------------

#-----------------------------------
exit 0
#-----------------------------------
```

## exec job
## post
```sh
sbatch xxx.sh
```
## test
```sh
srun xxx.sh
```