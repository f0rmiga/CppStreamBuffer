//============================================================================
// Name        : Main.cpp
// Author      : Thulio Ferraz Assis
// Contact     : contato@thulioassis.com.br
// Copyright   : Thulio Ferraz Assis all rights reserved
//============================================================================

#include <iostream>
#include "ByteArray.h"

using namespace std;

void print(string str, int color, bool bold) {
	cout << "\033[" << (bold ? "1;" : "") << color << "m" << str << "\033[0m";
}
void print(string str, int color) {
	print(str, color, false);
}
void print(string str) {
	print(str, 30, false);
}

int main() {
	print(">> Testing ByteArray.h <<\n\n", 31, true);

	ByteArray testArray1(11);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing write operations\n", 31, false);
	print("> Testing writeByte(105)... ", 30, true);
	print(testArray1.writeByte(105) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing writeShort(31000)... ", 30, true);
	print(testArray1.writeShort(31000) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing unsigned writeShort(45000)... ", 30, true);
	print(testArray1.writeShort(45000) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing negative writeShort(-31000)... ", 30, true);
	print(testArray1.writeShort(-31000) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing writeInt(145845304)... ", 30, true);
	print(testArray1.writeInt(145845304) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Trying to exceed capacity with writeShort(310)... ", 30, true);
	print(testArray1.writeShort(31000) ? "error!\n" : "passed! Short not written\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Switching position to 0... ", 30, true);
	testArray1.setPosition(0);
	print(testArray1.getPosition() == 0 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;

	print("\n> Testing read operations\n", 31, false);
	print("> Testing readByte() expected 105... ", 30, true);
	print(testArray1.readByte() == 105 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readShort() expected 31000... ", 30, true);
	print(testArray1.readShort() == 31000 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readUnsignedShort() expected 45000... ", 30, true);
	print(testArray1.readUnsignedShort() == 45000 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readShort() expected -31000... ", 30, true);
	print(testArray1.readShort() == -31000 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readInt() expected 145845304... ", 30, true);
	print(testArray1.readInt() == 145845304 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Trying to exceed read with readByte()... ", 30, true);
	try {
		testArray1.readByte();
		print("error!\n", 31);
	} catch(int e) {
		print("passed!\n", 31);
	}
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Trying to exceed read with readShort() in position (size - 1)... ", 30, true);
	try {
		testArray1.setPosition(testArray1.getSize() - 1);
		testArray1.readShort();
		print("error!\n", 31);
	} catch(int e) {
		print("passed!\n", 31);
		testArray1.setPosition(testArray1.getSize());
	}
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.getSize() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;

	print("\n> Testing creation of another ByteArray using a vector of char\n", 31, false);
	char newchars[7] = {-16,2,77,120,20,52,12};
	vector<char> vectornewchars(newchars, newchars + sizeof(newchars) / sizeof(char) );
	ByteArray testArray2(vectornewchars);

	print("\n> Testing read operations\n", 31, false);
	print("> Testing readByte()... ", 30, true);
	cout << int(testArray2.readByte()) << endl;
	cout << "> Position: " << testArray2.getPosition() << " | Size: " << testArray2.getSize() << " | Bytes Available: " << testArray2.bytesAvailable() << endl;
	print("> Testing readShort()... ", 30, true);
	cout << int(testArray2.readShort()) << endl;
	cout << "> Position: " << testArray2.getPosition() << " | Size: " << testArray2.getSize() << " | Bytes Available: " << testArray2.bytesAvailable() << endl;
	print("> Testing readInt()... ", 30, true);
	cout << int(testArray2.readInt()) << endl;
	cout << "> Position: " << testArray2.getPosition() << " | Size: " << testArray2.getSize() << " | Bytes Available: " << testArray2.bytesAvailable() << endl;

	print("\n> Testing creation of another ByteArray to use UTF\n", 31, false);
	ByteArray testArray3(10);

	print("> Testing writeUTF(str)... ", 30, true);
	print(testArray3.writeUTF("testArray3") ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.getSize() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;
	print("> Switching position to 0... ", 30, true);
	testArray3.setPosition(0);
	print(testArray3.getPosition() == 0 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.getSize() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;
	print("> Testing readUTF(testArray3.bytesAvailable())... ", 30, true);
	print(testArray3.readUTF(testArray3.bytesAvailable()) == "testArray3" ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.getSize() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;
	print("> Testing readUTF(3, 7)... ", 30, true);
	print(testArray3.readUTF(3, 7) == "tArray3" ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.getSize() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;

	return 0;
}