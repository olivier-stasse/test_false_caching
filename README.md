# Introduction

This project examplifies the False Caching problem.
It occurs when multiple threads access the same memory zone. As this memory zone
is copied in the local cache, they are modification of the same initial zone
in various caches. This breaks down the  performance of  the multiple threading
when reconstructing the memory.

The way to solve this problem is to make sure that each thread access a
different memory part.

This example is build upon [this example](https://www.openmp.org/wp-content/uploads/openmp-examples-5.0.0.pdf).

# Building

```
git clone https://github.com/olivier-stasse/test_false_caching
cd test_false_caching
mkdir build
cd build
cmake ..
make
```

# Running

```
./test_false_caching
```

## Results

## Description of the computer

Mac Book Pro 2019, Catalina 10.15.7 Intel Core i9 8 core 2.3 GHz 32 Go 2667 MHz DDR4
Apple clang version 12.0.0 (clang-1200.0.32.2)
Target: x86_64-apple-darwin19.6.0
Thread model: posix

OMP version 11.0.0 (bottled)

### Buffer size: 80
```
One MT
 0.126542s wall, 0.120000s user + 0.000000s system = 0.120000s CPU (94.8%)
8 MT - False caching
 0.256694s wall, 2.030000s user + 0.000000s system = 2.030000s CPU (790.8%)
8 MT - Spreading of the memory
 0.098515s wall, 0.770000s user + 0.000000s system = 0.770000s CPU (781.6%)
```

### Buffer size: 124
```
One MT
 0.206265s wall, 0.200000s user + 0.000000s system = 0.200000s CPU (97.0%)
8 MT - False caching
 0.287493s wall, 2.270000s user + 0.000000s system = 2.270000s CPU (789.6%)
8 MT - Spreading of the memory
 0.090279s wall, 0.700000s user + 0.000000s system = 0.700000s CPU (775.4%)
```

### Buffer size: 256
```
One MT
 0.362221s wall, 0.360000s user + 0.000000s system = 0.360000s CPU (99.4%)
8 MT - False caching
 0.454266s wall, 3.600000s user + 0.000000s system = 3.600000s CPU (792.5%)
8 MT - Spreading of the memory
 0.096486s wall, 0.770000s user + 0.000000s system = 0.770000s CPU (798.0%)
```

### Buffer size: 512
```
One MT
 0.701388s wall, 0.700000s user + 0.000000s system = 0.700000s CPU (99.8%)
8 MT - False caching
 0.719904s wall, 5.710000s user + 0.010000s system = 5.720000s CPU (794.6%)
8 MT - Spreading of the memory
 0.102633s wall, 0.820000s user + 0.000000s system = 0.820000s CPU (799.0%)
```

### Buffer size: 1024
```
One MT
 1.395748s wall, 1.390000s user + 0.000000s system = 1.390000s CPU (99.6%)
8 MT - False caching
 1.035511s wall, 8.240000s user + 0.010000s system = 8.250000s CPU (796.7%)
8 MT - Spreading of the memory
 0.124755s wall, 0.980000s user + 0.000000s system = 0.980000s CPU (785.5%)
```

## Analysis

It appears clearly that False caching is breaking the performances of the parallelism if the memory accessed by each thread is not
carefully taken into account. The size of the memory is also important. The full benefit of the multiple threads appears only in this case
when using memory over 512*4 bytes.