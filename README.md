# parallel_programming
## local env
- OS
  - macOS mojave
- compiler
  - clang++

## requirement
### libomp
```sh
brew install libomp
```

## how to complile
```sh
clang++ -Xpreprocessor -fopenmp -lomp xxx.cpp
```