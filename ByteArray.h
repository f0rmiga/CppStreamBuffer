//============================================================================
// Name        : ByteArray.h
// Author      : Thulio Ferraz Assis
// Contact     : contato@thulioassis.com.br
// Copyright   : Thulio Ferraz Assis all rights reserved
//============================================================================

#include <vector>

using namespace std;

#define LITTLE_ENDIAN_ 0
#define BIG_ENDIAN_ 1

class ByteArray {
public:
	/* Initialize empty ByteArray with predefined size */
	ByteArray(unsigned int size_) {
		size = size_;
		bytesAvailable_ = size;
		vector_.reserve(size);
	}
	/* Initialize ByteArray using existing vector of char */
	ByteArray(vector<char> newvector_) {
		size = newvector_.size();
		bytesAvailable_ = size;
		vector_.reserve(size);
		vector_.assign(newvector_.begin(), newvector_.end());
	}
	/* Initialize empty ByteArray with predefined size and endianness option */
	ByteArray(unsigned int size_, unsigned char endianness_) {
		size = size_;
		bytesAvailable_ = size;
		vector_.reserve(size);
		if (endianness_ == BIG_ENDIAN_ || endianness_ == LITTLE_ENDIAN_)
			endianness = endianness_;
	}
	/* Initialize ByteArray using existing vector of char and endianness option */
	ByteArray(vector<char> newvector_, unsigned char endianness_) {
		size = newvector_.size();
		bytesAvailable_ = size;
		vector_.reserve(size);
		vector_.assign(newvector_.begin(), newvector_.end());
		if (endianness_ == BIG_ENDIAN_ || endianness_ == LITTLE_ENDIAN_)
			endianness = endianness_;
	}

	/* Set the position to write or read */
	void setPosition(unsigned int position_) {
		position = position_;
		bytesAvailable_ = size - position;
	}

	/* Returns actual position to write or read */
	unsigned int getPosition() {
		return position;
	}

	/* Number of bytes available to read */
	unsigned int bytesAvailable() {
		return bytesAvailable_;
	}

	/* Returns related to the vector */
	vector<char> result() { return vector_; }
	unsigned int getSize() { return size; }

	/* Write functions */
	/* returns true if wrote, otherwise, returns false */
	bool writeByte(char byte_) {
		if (position > size - 1) {
			return false;
		}
		vector_[position] = byte_;
		position++;
		bytesAvailable_ = size - position;
		return true;
	}

	bool writeShort(short short_) {
		if (bytesAvailable_ < 2) {
			return false;
		}
		if (endianness == LITTLE_ENDIAN_)
			return writeByte(short_ & 0xFF) && writeByte((short_ >> 8) & 0xFF);
		else
			return writeByte((short_ >> 8) & 0xFF) && writeByte(short_ & 0xFF);
	}

	bool writeInt(int int_) {
		if (bytesAvailable_ < 4) {
			return false;
		}
		if (endianness == LITTLE_ENDIAN_)
			return writeByte(int_ & 0xFF) && writeByte((int_ >> 8) & 0xFF) && writeByte((int_ >> 16) & 0xFF) && writeByte((int_ >> 24) & 0xFF);
		else
			return writeByte((int_ >> 24) & 0xFF) && writeByte((int_ >> 16) & 0xFF) && writeByte((int_ >> 8) & 0xFF) && writeByte(int_ & 0xFF);
	}

	bool writeUTF(string string_) {
		if (bytesAvailable_ < string_.size()) {
			return false;
		}
		for (unsigned int i = 0; i < string_.size(); i++) {
			writeByte(string_[i]);
		}
		return true;
	}

	/* Read functions */
	/* Throws exception if try to read out of bounds */
	char readByte() {
		char byte_ = vector_[position];
		if (position >= size) {
			throw 1;
		}
		position++;
		bytesAvailable_ = size - position;
		return byte_;
	}
	char readByte(unsigned int offset) {
		if (offset < size) {
			position = offset;
		}
		return readByte();
	}

	unsigned char readUnsignedByte() {
		return readByte();
	}
	unsigned char readUnsignedByte(unsigned int offset) {
		return readByte(offset);
	}

	short readShort() {
		short short_ = ((int)(unsigned char)vector_[position + (endianness == LITTLE_ENDIAN_ ? 1 : 0)] << 8) | (unsigned char)vector_[position + (endianness == LITTLE_ENDIAN_ ? 0 : 1)];
		if (position >= size -1) {
			throw 1;
		}
		position += 2;
		bytesAvailable_ = size - position;
		return short_;
	}
	short readShort(unsigned int offset) {
		if (offset < size - 1) {
			position = offset;
		}
		return readShort();
	}

	unsigned short readUnsignedShort() {
		return readShort();
	}
	unsigned short readUnsignedShort(unsigned int offset) {
		return readShort(offset);
	}

	int readInt() {
		int int_ = ((int)(unsigned char)vector_[position + (endianness == LITTLE_ENDIAN_ ? 3 : 0)] << 24) | ((int)(unsigned char)vector_[position + (endianness == LITTLE_ENDIAN_ ? 2 : 1)] << 16) | ((int)(unsigned char)vector_[position + (endianness == LITTLE_ENDIAN_ ? 1 : 2)] << 8) | (unsigned char)vector_[position + (endianness == LITTLE_ENDIAN_ ? 0 : 3)];
		if (position >= size -3) {
			throw 1;
		}
		position += 4;
		bytesAvailable_ = size - position;
		return int_;
	}
	int readInt(unsigned int offset) {
		if (offset < size - 3) {
			position = offset;
		}
		return readInt();
	}

	unsigned int readUnsignedInt() {
		return readInt();
	}
	unsigned int readUnsignedInt(unsigned int offset) {
		return readInt(offset);
	}

	string readUTF(unsigned int size_) {
		if (size_ > size - position) {
			throw 1;
		}
		string string_;
		for (unsigned int o = 0; o < size_; position++, o++) {
			string_.push_back(vector_[position]);
		}
		bytesAvailable_ = size - position;
		return string_;
	}
	string readUTF(unsigned int offset, unsigned int size_) {
		if (size_ <= size - offset) {
			position = offset;
		}
		return readUTF(size_);
	}

private:
	/* The vector of chars */
	vector<char> vector_;

	/* Position of the offset in read and write operations */
	unsigned int position = 0;

	/* Number of bytes available to read */
	unsigned int bytesAvailable_;

	/* Fixed size of the ByteArray */
	unsigned int size = 0;

	/* Define the endianness, little endian by default*/
	unsigned char endianness = LITTLE_ENDIAN_;
};