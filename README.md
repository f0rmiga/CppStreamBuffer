CppStreamBuffer
===============

Build C++ byte arrays like you were using streams.

Example
=======

```c++
#include <iostream>
#include "CppStreamBuffer.hpp"

int main() {
    CppStreamBuffer::Buffer buffer;
    buffer << CppStreamBuffer::Format::HEX; // Set flag to print as HEX representation of data
    buffer << (int) 300 << (double) 20.0; // Insert an int followed by a double
    std::cout << buffer << std::endl; // Print result buffer as HEX representation
    int back1;
    double back2;
    buffer >> back1 >> back2; // Extract values from buffer to new variables
    std::cout << back1 << " | " << back2 << std::endl; // Print the values
    return 0;
}
```

Support for Data Types
======================

You can insert/extract almost any type of data.

- Integer types:
    - uint8_t (unsigned char)
    - uint16_t (unsigned short)
    - uint32_t (unsigned int)
    - uint64_t (unsigned long)
    - int8_t (char)
    - int16_t (short)
    - int32_t (int)
    - int64_t (long)

- Floating-point types:
    - float
    - double

- String types:
    - std::string

Tutorial
========

There is not much to say on how to use. You need to pay attention to match the order of write and read. For example, if you write 2 shorts and 1 float, you need to read in that sequence, but it is more than obvious, I guess.

Dependencies
============

C++11 Standard Library

License
=======

MIT License
