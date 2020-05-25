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
```

## post job file
```sh
srun xxx.sh
```