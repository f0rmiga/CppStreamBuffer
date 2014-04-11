CppByteArray
============

To start:

```
  mkdir bin/ && cd bin/
  cmake ..
  make
  ./main.o
```

The goal
========

The goal is to create a simple class that deal easier with Node.js Buffer, ActionScript ByteArray, Akka ByteString and others.

Basic example
=============

```c++
#include "ByteArray.h"

int main() {
    ByteArray myByteArray(7); // Initiate the ByteArray with size 7
    
    myByteArray.writeByte(104); // Write single byte to ByteArray
    myByteArray.writeShort(17923); // Write 2 bytes to ByteArray
    myByteArray.writeInt(4987241); // Write 4 bytes to ByteArray
    
    myByteArray.setPosition(0); // Back the position to 0
    
    char byte_ = myByteArray.readByte(); // Read single byte into char
    short short_ = myByteArray.readShort(); // Read 2 bytes into short
    int int_ = myByteArray.readInt(); // Read 4 bytes into int

    return 0;
}
```


Everyone are welcome to contribute!
