//============================================================================
// Name        : Main.cpp
// Author      : Thulio Ferraz Assis
// Contact     : contato@thulioassis.com.br
// Copyright   : Thulio Ferraz Assis all rights reserved
//============================================================================

#include <iostream>
#include <chrono>

#include "../ByteArray.h"

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

void display(ByteArray sss) {
	sss.setPosition(3);
	cout << "bytes available" << sss.bytesAvailable() << endl;
}

int main() {
	print(">> Testing ByteArray.h <<\n\n", 31, true);

	ByteArray testArray1(11);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing write operations\n", 31, false);
	print("> Testing writeByte(105)... ", 30, true);
	print(testArray1.writeByte(105) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing writeShort(31000)... ", 30, true);
	print(testArray1.writeShort(31000) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing unsigned writeShort(45000)... ", 30, true);
	print(testArray1.writeShort(45000) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing negative writeShort(-31000)... ", 30, true);
	print(testArray1.writeShort(-31000) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing writeInt(145845304)... ", 30, true);
	print(testArray1.writeInt(145845304) ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Trying to exceed capacity with writeShort(310)... ", 30, true);
	print(testArray1.writeShort(31000) ? "error!\n" : "passed! Short not written\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Switching position to 0... ", 30, true);
	testArray1.setPosition(0);
	print(testArray1.getPosition() == 0 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;

	print("\n> Testing read operations\n", 31, false);
	print("> Testing readByte() expected 105... ", 30, true);
	print(testArray1.readByte() == 105 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readShort() expected 31000... ", 30, true);
	print(testArray1.readShort() == 31000 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readUnsignedShort() expected 45000... ", 30, true);
	print(testArray1.readUnsignedShort() == 45000 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readShort() expected -31000... ", 30, true);
	print(testArray1.readShort() == -31000 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Testing readInt() expected 145845304... ", 30, true);
	print(testArray1.readInt() == 145845304 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Trying to exceed read with readByte()... ", 30, true);
	try {
		testArray1.readByte();
		print("error!\n", 31);
	} catch(int e) {
		print("passed!\n", 31);
	}
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;
	print("> Trying to exceed read with readShort() in position (size - 1)... ", 30, true);
	try {
		testArray1.setPosition(testArray1.size() - 1);
		testArray1.readShort();
		print("error!\n", 31);
	} catch(int e) {
		print("passed!\n", 31);
		testArray1.setPosition(testArray1.size());
	}
	cout << "> Position: " << testArray1.getPosition() << " | Size: " << testArray1.size() << " | Bytes Available: " << testArray1.bytesAvailable() << endl;

	print("\n> Testing creation of another ByteArray to use UTF\n", 31, false);
	ByteArray testArray3(10);

	print("> Testing writeUTF(str)... ", 30, true);
	print(testArray3.writeUTF("testArray3") ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.size() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;
	print("> Switching position to 0... ", 30, true);
	testArray3.setPosition(0);
	print(testArray3.getPosition() == 0 ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.size() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;
	print("> Testing readUTF(testArray3.bytesAvailable())... ", 30, true);
	print(testArray3.readUTF(testArray3.bytesAvailable()) == "testArray3" ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.size() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;
	print("> Testing readUTF(3, 7)... ", 30, true);
	print(testArray3.readUTF(3, 7) == "tArray3" ? "passed!\n" : "error!\n", 31);
	cout << "> Position: " << testArray3.getPosition() << " | Size: " << testArray3.size() << " | Bytes Available: " << testArray3.bytesAvailable() << endl;

	print("\n>> Testing performance <<\n", 31, true);
	print("> Creating ByteArray of size 10.000.000, writeByte(110) until fill\n", 30, true);
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();
	unsigned int size_performance = 10000000;
	ByteArray performance_ByteArray(size_performance);
	for (unsigned int i = 0; i < size_performance; i++) {
		performance_ByteArray.writeByte(110);
	}
	end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds;
	elapsed_seconds = end-start;
	print("Result: ", 31, false);
	cout << elapsed_seconds.count() * 1000 << " ms\n";

	print("> Reading ByteArray of size 10.000.000 using readByte()\n", 30, true);
	performance_ByteArray.setPosition(0);
	start = chrono::system_clock::now();
	for (unsigned int i = 0; i < size_performance; i++) {
		performance_ByteArray.readByte();
	}
	end = chrono::system_clock::now();

	elapsed_seconds = end-start;
	print("Result: ", 31, false);
	cout << elapsed_seconds.count() * 1000 << " ms\n";

	print("> Reading ByteArray of size 10.000.000 using readShort()\n", 30, true);
	performance_ByteArray.setPosition(0);
	start = chrono::system_clock::now();
	for (unsigned int i = 0; i < size_performance / 2; i++) {
		performance_ByteArray.readShort();
	}
	end = chrono::system_clock::now();

	elapsed_seconds = end-start;
	print("Result: ", 31, false);
	cout << elapsed_seconds.count() * 1000 << " ms\n";

	print("> Reading ByteArray of size 10.000.000 using readInt()\n", 30, true);
	performance_ByteArray.setPosition(0);
	start = chrono::system_clock::now();
	for (unsigned int i = 0; i < size_performance / 4; i++) {
		performance_ByteArray.readInt();
	}
	end = chrono::system_clock::now();

	display(performance_ByteArray);

	elapsed_seconds = end-start;
	print("Result: ", 31, false);
	cout << elapsed_seconds.count() * 1000 << " ms\n";

	print("> Creating 10.000.000 of ByteArray and write 5 shorts\n", 30, true);
	start = chrono::system_clock::now();
	for (uint32_t i = 0; i < size_performance; i++) {
		ByteArray tenmillionarrays(10);
		for (uint8_t j = 0; j < 5; j++) {
			tenmillionarrays.writeShort(5968);
		}
	}
	end = chrono::system_clock::now();

	elapsed_seconds = end-start;
	print("Result: ", 31, false);
	cout << elapsed_seconds.count() * 1000 << " ms\n";

	return 0;
}