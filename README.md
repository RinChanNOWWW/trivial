# trivial

Useful cpp codes for writing some simple cpp programs.

## Contains

- algorithm: 
    - quick pow.
    - heap sort.
- string operation:
    - join.
    - split.
    - trim(ltrim/rtrim/trim).
- utilites:
    - get a vector or a 2-dims vector from a string.
    - print a vector.
- advanced data structure:
    - skip list.
    - key-value collections (for string only):
        - lru.
        - lfu.
        - trie (iterator implemented).
    

## Usage

Install the lib.


```bash
mkdir build
cd build
# build in Release mode
cmake -DCMAKE_BUILD_TYPE=Release ..
# build in Debug mode
cmake ..
# install the header files under /usr/local/include (trivial)
# install the library under /usr/local/lib (libtrivial.a)
sudo make install 
```
Write the codes..

```cpp
#include <trivial/algorithm.h>
#include <trivial/strings.h>

using namespace trivial;

// ...
```

Compile the codes:

```bash
g++ main.cpp -o main -ltrivial
```

More detail examples can be found in `tests/`.

## Attention

The lib is **only tested on my own Ubuntu 20.04(WSL) with g++ 9.3.0 in C++17**.
