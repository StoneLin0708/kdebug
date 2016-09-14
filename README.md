project on github https://github.com/StoneLin0708/kdebug

simple c++ debug class
======================

## Installation

#### Option 1.
put all files in `src` folder into your project

#### Option 2.
* For Linux

```shell
mkdir build
cd build
cmake ..
make
sudo make install
```

* For Windows
Not yet done

##### Note: this debug utility can only be compile with `-std=c++11` or above


## Usage
If You wish to actually output on console, you need to define `DEBUG_MESSAGE` at compile time, like
```shell
g++ -o output output.cpp -DDEBUG_MESSAGE
```

before you start you could do
```cpp
#include "kdebug.h"

```

<hr>
#### C++

you could do `using namespace kdebug; // not necessary but convenient`

In the c++ source code, simply write

```cpp
LOG(info) << "info logging\n";
LOG(warning) << "warning logging\n";
LOG(error) << "error logging\n";

DBG(info) << "info debugging\n";
DBG(warning) << "warning debugging\n";
DBG(error) << "error debugging\n";

TIMER(info) << "info timing\n";
TIMER(warning) << "warning timing\n";
TIMER(error) << "error timing\n";
```
for different level of logging

To output to file, simply write
```cpp
kdebug.debug.set_fileoutput("some-output.log");

LOG(file) << "file logging\n";
DBG(file) << "file debuggin\n";
TIMER(file) << "file timing\n";
```

#### C

```c
LOG("logging");
ERROR("error");
```
for different level of logging

## Future Plan
- [ ] Add Colors to debug messages
- [ ] Continuous timing
