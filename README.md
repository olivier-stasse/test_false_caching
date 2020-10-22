# Introduction

This project examplifies the False Caching problem.
It occurs when multiple threads access the same memory zone. As this memory zone
is copied in the local cache, they are modification of the same initial zone
in various caches. This breaks down the  performance of  the multiple threading
when reconstructing the memory.

The way to solve this problem is to make sure that each thread access a
different memory part.

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

Results on a mac catalina:
```
One MT
 0.126542s wall, 0.120000s user + 0.000000s system = 0.120000s CPU (94.8%)
8 MT - False caching
 0.256694s wall, 2.030000s user + 0.000000s system = 2.030000s CPU (790.8%)
8 MT - Spreading of the memory
 0.098515s wall, 0.770000s user + 0.000000s system = 0.770000s CPU (781.6%)
```

