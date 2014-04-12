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
Some notes: the position (or index) moves automatic to next read. But you can set the read to specific position. Ex:
```c++
myByteArray.readInt(3); // The position moves automatic to next read. But you can set the read to specific position

// Or:

myByteArray.setPosition(3); // Manual set the position to 3
myByteArray.readInt(); // Read int at position 3

bool byteWritten = myByteArray.writeByte(78); // Returns false, there are no space available to write

char byte_ = myByteArray.readByte(); // Throws exception, there are no bytes available to read

// You can check if there are bytes available enough to read or write

if (myByteArray.bytesAvailable() >= 4) {
    myByteArray.writeInt(2950124);
}
```

Same example in other languages
===============================
##Node.js

```javascript
const myByteArray = new Buffer(7); // Initiate the Buffer with size 7

myByteArray.writeInt8(104, 0); // Write single byte to Buffer in position 0
myByteArray.writeInt16LE(17923, 1); // Write 2 bytes to Buffer in position 1
myByteArray.writeInt32LE(4987241, 3); // Write 4 bytes to Buffer in position 3

const byte_ = myByteArray.readInt8(0); // Read single byte from position 0
const short_ = myByteArray.readInt16LE(1); // Read 2 bytes from position 1
const int_ = myByteArray.readInt32LE(3); // Read 4 bytes from position 3
```

Everyone are welcome to contribute!
