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
g++ -o output output.cpp -DEBUG_MESSAGE
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
LOG(kdebug::info) << "info logging\n";
LOG(kdebug::warning) << "warning logging\n";
LOG(kdebug::error) << "error logging\n";
```
for different level of logging

To output to file, simply write
```cpp
kdebug.debug.set_fileoutput("some-output.log");
LOG(file) << "file logging\n";
```

#### C

```c
LOG("logging");
ERROR("error");
```
for different level of logging
