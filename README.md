kdebug (simple c++ debug class)
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
If You wish to actually output on console/file, you need to define `DEBUG_MESSAGE` at compile time, like
```shell
g++ -o output output.cpp -DDEBUG_MESSAGE
```
##### Note: compiling without the macro, non of the debug code will be append to your source and you simply do not receive any log messages

before you start you could do
```cpp
#include "kdebug/kdebug.h"
```

##### NOTE: you do not need to do `using namespace kdebug; // not necessary`

<hr>
#### C++
In the c++ source code, simply write

```cpp
// logging
LOG(INFO) << "info logging";
LOG(WARNING) << "warning logging";
LOG(ERROR) << "error logging";
LOG(null) << "info logging";

// debug
DBG(INFO) << "info debugging";
DBG(WARNING) << "warning debugging";
DBG(ERROR) << "error debugging";
DBG(null) << "nothing";

// timer
TIMER(INFO) << "info timing";
TIMER(WARNING) << "warning timing";
TIMER(ERROR) << "error timing";
TIMER(null) << "nothing";

// update start time
// logging
LOG(info) << "info logging\n";
LOG(warning) << "warning logging\n";
LOG(error) << "error logging\n";

// debugging
DBG(info) << "info debugging\n";
DBG(warning) << "warning debugging\n";
DBG(error) << "error debugging\n";

// timer
TIMER(info) << "info timing\n";
TIMER(warning) << "warning timing\n";
TIMER(error) << "error timing\n";
```
for different level of logging

To direct output to file, simply write
```cpp
SET_OUTPUT_FILE("filename")
```
all types of debug will be written to file ```"filename"```

to turn is on/off, write
```cpp
// turn on
LOG_OUTPUT_FILE(true)
DBG_OUTPUT_FILE(true)
TIMER_OUTPUT_FILE(true)

// turn off
LOG_OUTPUT_FILE(false)
DBG_OUTPUT_FILE(false)
TIMER_OUTPUT_FILE(false)
```

to turn on/off the filename tag, write
```cpp
// turn on
LOG_SOURCE_NAME(true)
DBG_SOURCE_NAME(true)
TIMER_SOURCE_NAME(true)

// turn off
LOG_SOURCE_NAME(false)
DBG_SOURCE_NAME(false)
TIMER_SOURCE_NAME(false)
```

#### C

```c
LOG("logging");
ERROR("error");
```
for different level of logging

## Future Plan
- [x] Add Colors to debug messages
- [x] Continuous timing
- [ ] More test on multithreaded
