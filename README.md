simple c++ debug class
======================

## Installation
Simply include this file. Pretty simple.

Note: this debug utility can only be compile with `-std=c++11` or above

## Usage
If You wish to actually output on console, you need to define `DEBUG_MESSAGE` at compile time, like
```shell
g++ -o output output.cpp -DEBUG_MESSAGE
```

before you start you could do (not necessary)
```cpp
using namespace kdebug;
```

In the c++ source code, simply write
```cpp
LOG(info) << "info logging\n";
LOG(warning) << "warning logging\n";
LOG(error) << "error logging\n";
```
for different level of logging

To output to file, simply write
```cpp
kdebug.debug.set_fileoutput("some-output.log");
LOG(file) << "file logging\n";
```

