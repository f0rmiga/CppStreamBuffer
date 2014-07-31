//============================================================================
// Name        : ByteArray.h
// Author      : Thulio Ferraz Assis
// Contact     : contato@thulioassis.com.br
// Copyright   : Thulio Ferraz Assis all rights reserved
//============================================================================

#include <cstring>

using namespace std;

#define LITTLE_ENDIAN_ 0
#define BIG_ENDIAN_ 1

class ByteArray {
public:
	/* Empty ByteArray */
	ByteArray() {
		buffer = NULL;
	}
	/* Initialize empty ByteArray with predefined size */
	ByteArray(size_t size) {
		size_ = size; // Set the private var "size" to the provided "size_"
		bytesAvailable_ = size; // Set the bytes available
		buffer = new int8_t[size]; // Reserve the size in memory
	}
	/* Initialize empty ByteArray with predefined size and endianness option */
	ByteArray(size_t size, uint8_t endianness) {
		size_ = size;
		bytesAvailable_ = size_;
		buffer = new int8_t[size]; // Reserve the size in memory
		if (endianness == BIG_ENDIAN_ || endianness == LITTLE_ENDIAN_)
			endianness_ = endianness;
	}
	/* Copy constructor */
	ByteArray(const ByteArray &other) {
		size_ = other.size_;
		position_ = other.position_;
		bytesAvailable_ = other.bytesAvailable_;
		endianness_ = other.endianness_;
		buffer = new int8_t[size_];
		copy(other.buffer, other.buffer+size_, buffer);
	}
	/* Assignment operator */
	ByteArray &operator=(const ByteArray& other) {
		if (this != &other) {
			size_ = other.size_;
			position_ = other.position_;
			bytesAvailable_ = other.bytesAvailable_;
			endianness_ = other.endianness_;
			buffer = new int8_t[size_];
			copy(other.buffer, other.buffer+size_, buffer);
		}
		return *this;
	}

	~ByteArray() {
		delete[] buffer;
	}

	/* Set the position to write or read */
	void setPosition(uint32_t position) {
		position_ = position; // set the private var "position" to the provided "position_"
		bytesAvailable_ = size_ - position; // set the bytes available based on the size and the new position
	}

	/* Returns actual position to write or read */
	uint32_t getPosition() {
		return position_;
	}

	/* Returns the number of bytes available to read */
	size_t bytesAvailable() {
		return bytesAvailable_;
	}

	/* Returns related to the array */
	int8_t *result() { return buffer; } // Returns the buffer of the ByteArray to use in other classes or libraries
	size_t size() { return size_; }

	/* Write functions */
	/* returns true if wrote, otherwise, returns false */
	bool writeByte(int8_t byte_) {
		if (position_ > size_ - 1) { // Verifies if the ByteArray has available space to write 1 byte
			return false; // Returns false if it doesn't
		}
		buffer[position_] = byte_; // Writes the byte in the current position
		position_++; // Moves the position
		bytesAvailable_ = size_ - position_; // Calculate the new bytes available
		return true;
	}

	bool writeShort(int16_t short_) {
		return writeShort(short_, endianness_);
	}
	bool writeShortBE(int16_t short_) {
		return writeShort(short_, BIG_ENDIAN_);
	}
	bool writeShortLE(int16_t short_) {
		return writeShort(short_, LITTLE_ENDIAN_);
	}

	bool writeInt(int32_t int_) {
		return writeInt(int_, endianness_);
	}
	bool writeIntBE(int32_t int_) {
		return writeInt(int_, BIG_ENDIAN_);
	}
	bool writeIntLE(int32_t int_) {
		return writeInt(int_, LITTLE_ENDIAN_);
	}

	bool writeUTF(string string_) {
		if (bytesAvailable_ < string_.size()) { // Verifies if the ByteArray has available space to write the entire string
			return false; // Returns false if it doesn't
		}
		for (unsigned int i = 0; i < string_.size(); i++) { // Loop thru the string to write
			writeByte(string_[i]); // Writes each char to the ByteArray
		}
		return true;
	}

	/* Read functions */
	/* Throws exception if try to read out of bounds */
	int8_t readByte() {
		if (position_ >= size_) { // Stop the read if it has no bytes available to read
			throw 1; // Throws error
		}
		int8_t byte_ = (uint8_t)buffer[position_]; // Gets the byte in the current position
		position_++; // Moves the position
		bytesAvailable_ = size_ - position_; // Calculate the new bytes available
		return byte_; // Returns the byte
	}
	int8_t readByte(uint32_t offset) {
		if (offset < size_) { // Sets the position to the provided offset only if the read will handle it
			position_ = offset;
		}
		return readByte();
	}

	uint8_t readUnsignedByte() {
		return readByte();
	}
	uint8_t readUnsignedByte(uint32_t offset) {
		return readByte(offset);
	}

	int16_t readShort() {
		return readShort(position_, endianness_);
	}
	int16_t readShort(uint32_t offset) {
		if (offset < size_ - 1) { // Sets the position to the provided offset only if the read will handle it
			position_ = offset;
		}
		return readShort(position_, endianness_);
	}
	int16_t readShortBE() {
		return readShort(position_, BIG_ENDIAN_);
	}
	int16_t readShortLE() {
		return readShort(position_, LITTLE_ENDIAN_);
	}
	int16_t readShortBE(uint32_t offset) {
		if (offset < size_ - 1) {
			position_ = offset;
		}
		return readShort(position_, BIG_ENDIAN_);
	}
	int16_t readShortLE(uint32_t offset) {
		if (offset < size_ - 1) {
			position_ = offset;
		}
		return readShort(position_, LITTLE_ENDIAN_);
	}

	uint16_t readUnsignedShort() {
		return readShort(position_, endianness_);
	}
	uint16_t readUnsignedShortBE() {
		return readShort(position_, BIG_ENDIAN_);
	}
	uint16_t readUnsignedShortLE() {
		return readShort(position_, LITTLE_ENDIAN_);
	}
	uint16_t readUnsignedShort(uint32_t offset) {
		return readShort(offset);
	}
	uint16_t readUnsignedShortBE(uint32_t offset) {
		return readShortBE(offset);
	}
	uint16_t readUnsignedShortLE(uint32_t offset) {
		return readShortLE(offset);
	}

	int32_t readInt() {
		return readInt(position_, endianness_);
	}
	int32_t readInt(uint32_t offset) {
		if (offset < size_ - 3) { // Sets the position to the provided offset only if the read will handle it
			position_ = offset;
		}
		return readInt(position_, endianness_);
	}
	int32_t readIntBE() {
		return readInt(position_, BIG_ENDIAN_);
	}
	int32_t readIntLE() {
		return readInt(position_, LITTLE_ENDIAN_);
	}
	int32_t readIntBE(uint32_t offset) {
		if (offset < size_ - 3) {
			position_ = offset;
		}
		return readInt(position_, BIG_ENDIAN_);
	}
	int32_t readIntLE(uint32_t offset) {
		if (offset < size_ - 3) {
			position_ = offset;
		}
		return readInt(position_, LITTLE_ENDIAN_);
	}

	uint32_t readUnsignedInt() {
		return readInt(position_, endianness_);
	}
	uint32_t readUnsignedIntBE() {
		return readInt(position_, BIG_ENDIAN_);
	}
	uint32_t readUnsignedIntLE() {
		return readInt(position_, LITTLE_ENDIAN_);
	}
	uint32_t readUnsignedInt(uint32_t offset) {
		return readInt(offset);
	}
	uint32_t readUnsignedIntBE(uint32_t offset) {
		return readIntBE(offset);
	}
	uint32_t readUnsignedIntLE(uint32_t offset) {
		return readIntLE(offset);
	}

	string readUTF(unsigned int size) {
		if (size > size_ - position_) { // Stop the read if the size provided exceeds the bytes available to read
			throw 1; // Throws error
		}
		string string_; // Instantiate new string to return
		for (unsigned int o = 0; o < size; position_++, o++) { // Loop thru the ByteArray to push to the string
			string_.push_back(buffer[position_]); // Pushes each byte to the string
		}
		bytesAvailable_ = size_ - position_; // Calculate the new bytes available
		return string_; // Returns the string
	}
	string readUTF(unsigned int offset, unsigned int size) {
		if (size <= size_ - offset) { // Sets the position to the provided offset only if the read will handle it
			position_ = offset;
		}
		return readUTF(size);
	}

private:
	/* The array of chars */
	int8_t *buffer;

	/* Position of the offset in read and write operations */
	uint32_t position_ = 0;

	/* Number of bytes available to read */
	size_t bytesAvailable_;

	/* Fixed size of the ByteArray */
	size_t size_ = 0;

	/* Define the endianness, little endian by default*/
	uint8_t endianness_ = LITTLE_ENDIAN_;

	/* All private functions to be called from public functions */
	bool writeShort(int16_t short_, uint8_t endianness) {
		if (bytesAvailable_ < 2) { // Verifies if the ByteArray has available space to write 2 bytes
			return false; // Returns false if it doesn't
		}
		if (endianness == LITTLE_ENDIAN_)
			return writeByte(short_ & 0xFF) && writeByte((short_ >> 8) & 0xFF); // Writes the little endian sequence
		else
			return writeByte((short_ >> 8) & 0xFF) && writeByte(short_ & 0xFF); // Writes the big endian sequence
	}

	bool writeInt(int32_t int_, uint8_t endianness) {
		if (bytesAvailable_ < 4) { // Verifies if the ByteArray has available space to write 4 bytes
			return false; // Returns false if it doesn't
		}
		if (endianness == LITTLE_ENDIAN_)
			return writeByte(int_ & 0xFF) && writeByte((int_ >> 8) & 0xFF) && writeByte((int_ >> 16) & 0xFF) && writeByte((int_ >> 24) & 0xFF); // Writes the little endian sequence
		else
			return writeByte((int_ >> 24) & 0xFF) && writeByte((int_ >> 16) & 0xFF) && writeByte((int_ >> 8) & 0xFF) && writeByte(int_ & 0xFF); // Writes the big endian sequence
	}

	int16_t readShort(uint32_t offset, uint8_t endianness) {
		if (offset >= size_ -1) { // Stop the read if it has not enough bytes available to read
			throw 1; // Throws error
		}
		int16_t short_ = ((int16_t)(uint8_t)buffer[offset + (endianness == LITTLE_ENDIAN_ ? 1 : 0)] << 8) | (uint8_t)buffer[offset + (endianness == LITTLE_ENDIAN_ ? 0 : 1)]; // Gets the bytes in the right sequence based on the endianness
		position_ += 2; // Moves the position by 2 bytes
		bytesAvailable_ = size_ - position_; // Calculate the new bytes available
		return short_; // Returns the short
	}

	int32_t readInt(uint32_t offset, uint8_t endianness) {
		if (offset >= size_ -3) { // Stop the read if it has not enough bytes available to read
			throw 1; // Throws error
		}
		int32_t int_ = ((int32_t)(uint8_t)buffer[offset + (endianness == LITTLE_ENDIAN_ ? 3 : 0)] << 24) | ((int32_t)(uint8_t)buffer[offset + (endianness == LITTLE_ENDIAN_ ? 2 : 1)] << 16) | ((int32_t)(uint8_t)buffer[offset + (endianness == LITTLE_ENDIAN_ ? 1 : 2)] << 8) | (uint8_t)buffer[offset + (endianness == LITTLE_ENDIAN_ ? 0 : 3)]; // Gets the bytes in the right sequence based on the endianness
		position_ += 4; // Moves the position by 4 bytes
		bytesAvailable_ = size_ - position_; // Calculate the new bytes available
		return int_; // Returns the int
	}
};