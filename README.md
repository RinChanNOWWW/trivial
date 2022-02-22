# trivial

Useful cpp codes for writing some simple cpp programs.

## Contains

- algorithm: 
    - quick pow.
    - heap sort.
- string operation:
    - join.
    - split.
- advance data structure:
    - skip list.

## Usage

Install the lib (In fact, the lib only contains header files now).


```bash
mkdir build
cd build
cmake ..
# move the *.h files to /usr/local/include/trivial 
sudo make install 
```
Write the codes..

```cpp
#include <trivial/algorithm.h>
#include <trivial/strings.h>

using namespace trivial;

// ...
```

More detail examples can be found in `tests/`.

## Supported OS

The lib is **only tested on my own Ubuntu 20.04(on WSL)**.
