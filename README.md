CppByteArray
============

CppByteArray is a simple class header only to create byte arrays easy to deal with in C++. It also makes integration easier with Node.js Buffer, ActionScript ByteArray, Akka ByteString and others.

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
###Node.js

```javascript
const myByteArray = new Buffer(7); // Initiate the Buffer with size 7

myByteArray.writeInt8(104, 0); // Write single byte to Buffer in position 0
myByteArray.writeInt16LE(17923, 1); // Write 2 bytes to Buffer in position 1
myByteArray.writeInt32LE(4987241, 3); // Write 4 bytes to Buffer in position 3

const byte_ = myByteArray.readInt8(0); // Read single byte from position 0
const short_ = myByteArray.readInt16LE(1); // Read 2 bytes from position 1
const int_ = myByteArray.readInt32LE(3); // Read 4 bytes from position 3
```

Documentation
=========
##Class: ByteArray
###ByteArray(size)
  - _size - size_t_
  
  Allocates a new ByteArray of size octets. Little endian set by default.
  
###ByteArray(size, endianness)
  - _size - size_t_
  - _endianness - uint8_t_

  Same as ByteArray(size), but with endianness as second parameter. Use LITTLE_ENDIAN_ or BIG_ENDIAN_.

##Write operations
###writeByte(int8_t)
  Writes a int8_t value (single byte) in current position. Returns true or false.
###writeShort(int16_t)
  Writes a int16_t value (2 bytes) in current position (uses the endianness set in constructor). Returns true or false.
###writeShortBE(int16_t)
  Same as writeShort(int16_t), but forces to write in Big Endian sequence. Returns true or false.
###writeShortLE(int16_t)
  Same as writeShort(int16_t), but forces to write in Little Endian sequence. Returns true or false.
###writeInt(int32_t)
  Writes a int32_t value (4 bytes) in current position (uses the endianness set in constructor). Returns true or false.
###writeIntBE(int32_t)
  Same as writeInt(int32_t), but forces to write in Big Endian sequence. Returns true or false.
###writeIntLE(int32_t)
  Same as writeInt(int32_t), but forces to write in Little Endian sequence. Returns true or false.
###writeUTF(string)
  Writes an UTF string in current position. Returns true or false.

##Read operations
  As a sugestion to avoid to throw errors, verify if there are any bytes available to read from the ByteArray.
###readByte()
  Reads a single byte in current position. Returns a char if available, or throws error.
###readByte(offset)
  - _offset - uint32_t_

  Same as readByte(), but reads in the offset position.
  
###readUnsignedByte()
  Same as readByte(), but returns a uint8_t instead.
###readUnsignedByte(offset)
  - _offset - uint32_t_

  Same as readByte(offset), but returns a uint8_t instead.

###readShort()
  Reads a short value in current position (uses the endianness set in constructor). Returns a int16_t if available, or throws error.
###readShort(offset)
  - _offset - uint32_t_
  
  Same as readShort(), but reads in the offset position.

###readShortBE()
  Same as readShort(), but forces to read in Big Endian sequence.
###readShortLE()
  Same as readShort(), but forces to read in Little Endian sequence.
###readShortBE(offset)
  - _offset - uint32_t_

  Same as readShortBE(), but reads in the offset position.
  
###readShortLE(offset)
  - _offset - uint32_t_
  
  Same as readShortLE(), but reads in the offset position.

###readUnsignedShort()
###readUnsignedShortBE()
###readUnsignedShortLE()
###readUnsignedShort(offset)
###readUnsignedShortBE(offset)
###readUnsignedShortLE(offset)
###readInt()
  Reads a int value in current position (uses the endianness set in constructor). Returns a int32_t if available, or throws error.
  
###readInt(offset)
  - _offset - uint32_t_

  Same as readInt(), but reads in the offset position.
  
###readIntBE()
  Same as readInt(), but forces to read in Big Endian sequence.

###readIntLE()
  Same as readInt(), but forces to read in Little Endian sequence.

###readIntBE(offset)
  - _offset - uint32_t_
  
  Same as readIntBE(), but reads in the offset position.

###readIntLE(offset)
  - _offset - uint32_t_
  
  Same as readIntLE(), but reads in the offset position.

###readUnsignedInt()
###readUnsignedIntBE()
###readUnsignedIntLE()
###readUnsignedInt(offset)
###readUnsignedIntBE(offset)
###readUnsignedIntLE(offset)
###readUTF(size)
  - _size - size_t_
  
  Reads an UTF string in current position of the specified size. Returns a string if available, or throws error.

###readUTF(offset, size)
  - _offset - uint32_t_
  - _size - size_t_
  
  Reads an UTF string in the offset position of the specified size. Returns a string if available, or throws error.
  
##Other functions
###resize(size)
  - _size - size_t_
  
  Resizes the ByteArray reallocating memory.
  
###setPosition(position)
  - _position - uint32_t_
  
  Manually set the position to read or write.
  
###getPosition()
  Returns the current position as a uint32_t value.
  
###bytesAvailable()
  Returns the current available bytes to read or write as a size_t value.
  
###size()
  Returns the size of allocated memory by the ByteArray as a size_t value.
  
###result()
  Returns a const char * to use with other libraries, or to send over network, for example.
  
###getStringView()
  Returns a string representation of the ByteArray, just for debug purposes. Returns as hexadecimal format.
  
###getStringView(decimal view)
  - _decimal view - bool_
  
  Returns a string representation of the ByteArray, just for debug porposes. The parameter sets if the return will be as decimal format or not.
