#include <chrono>
#include <iostream>

#include "CppStreamBuffer.hpp"

int main() {
    bool t1 = true;
    bool t1_b;
    uint8_t t2 = 68;
    uint8_t t2_b;
    int8_t t3 = 98;
    int8_t t3_b;
    uint16_t t4 = 2489;
    uint16_t t4_b;
    int16_t t5 = 9950;
    int16_t t5_b;
    uint32_t t6 = 148982;
    uint32_t t6_b;
    int32_t t7 = 883910;
    int32_t t7_b;
    uint64_t t8 = 42981498242;
    uint64_t t8_b;
    int64_t t9 = 1237987244;
    int64_t t9_b;
    float t10 = 21.16621;
    float t10_b;
    double t11 = 2.424982478;
    double t11_b;
    std::string t12("amazing big string to test!!! áúã''@ç");
    std::string t12_b;

    CppStreamBuffer::Buffer buffer1;
    buffer1 << t1 << t2 << t3 << t4 << t5 << t6 << t7 << t8 << t9 << t10 << t11 << t12;

    buffer1 >> t1_b >> t2_b >> t3_b >> t4_b >> t5_b >> t6_b >> t7_b >> t8_b >> t9_b >> t10_b >> t11_b >> t12_b;

    std::cout << "bool:             " << (t1 == t1_b ? "ok" : "error") << std::endl;
    std::cout << "unsigned char:    " << (t2 == t2_b ? "ok" : "error") << std::endl;
    std::cout << "char:             " << (t3 == t3_b ? "ok" : "error") << std::endl;
    std::cout << "unsigned short:   " << (t4 == t4_b ? "ok" : "error") << std::endl;
    std::cout << "short:            " << (t5 == t5_b ? "ok" : "error") << std::endl;
    std::cout << "unsigned int:     " << (t6 == t6_b ? "ok" : "error") << std::endl;
    std::cout << "int:              " << (t7 == t7_b ? "ok" : "error") << std::endl;
    std::cout << "unsigned long:    " << (t8 == t8_b ? "ok" : "error") << std::endl;
    std::cout << "long:             " << (t9 == t9_b ? "ok" : "error") << std::endl;
    std::cout << "float:            " << (t10 == t10_b ? "ok" : "error") << std::endl;
    std::cout << "double:           " << (t11 == t11_b ? "ok" : "error") << std::endl;
    std::cout << "std::string:      " << (t12 == t12_b ? "ok" : "error") << std::endl;

    std::cout << "\nTesting constructors:" << std::endl;

    std::cout << "Little-endian:    ";
    CppStreamBuffer::Buffer buffer2(CppStreamBuffer::Endianness::LITTLE);
    buffer2 << t5 << t10 << t11 << t12;
    buffer2 >> t5_b >> t10_b >> t11_b >> t12_b;
    std::cout << (t9 == t9_b && t10 == t10_b && t11 == t11_b && t12 == t12_b ? "ok" : "error") << std::endl;

    std::cout << "Big-endian:       ";
    CppStreamBuffer::Buffer buffer3(CppStreamBuffer::Endianness::BIG);
    buffer3 << t5 << t10 << t11 << t12;
    buffer3 >> t5_b >> t10_b >> t11_b >> t12_b;
    std::cout << (t9 == t9_b && t10 == t10_b && t11 == t11_b && t12 == t12_b ? "ok" : "error") << std::endl;

    std::cout << "Big reserved:     ";
    CppStreamBuffer::Buffer buffer4(CppStreamBuffer::Endianness::LITTLE, 50);
    buffer4 << t5 << t10 << t11 << t12;
    buffer4 >> t5_b >> t10_b >> t11_b >> t12_b;
    std::cout << (t9 == t9_b && t10 == t10_b && t11 == t11_b && t12 == t12_b ? "ok" : "error") << std::endl;

    std::cout << "Big reserved2:    ";
    CppStreamBuffer::Buffer buffer5(1000);
    buffer5 << t5 << t10 << t11 << t12;
    buffer5 >> t5_b >> t10_b >> t11_b >> t12_b;
    std::cout << (t9 == t9_b && t10 == t10_b && t11 == t11_b && t12 == t12_b ? "ok" : "error") << std::endl;

    std::cout << "\nTesting speed:" << std::endl;

    std::cout << "Writing 1k bytes: ";
    auto start = chrono::high_resolution_clock::now();
    CppStreamBuffer::Buffer buffer6;
    for (uint16_t i = 0; i < 1000; i++) {
        buffer6 << t1;
    }
    auto end = chrono::high_resolution_clock::now();
    std::cout << chrono::duration<uint32_t, nano>(end - start).count() << " ns" << std::endl;

    std::cout << "Reading 1k bytes: ";
    start = chrono::high_resolution_clock::now();
    for (uint16_t i = 0; i < buffer6.size(); i++) {
        buffer6 >> t1_b;
    }
    end = chrono::high_resolution_clock::now();
    std::cout << chrono::duration<uint32_t, nano>(end - start).count() << " ns" << std::endl;

    std::cout << "Writing 10k bytes: ";
    start = chrono::high_resolution_clock::now();
    CppStreamBuffer::Buffer buffer7;
    for (uint16_t i = 0; i < 10000; i++) {
        buffer7 << t1;
    }
    end = chrono::high_resolution_clock::now();
    std::cout << chrono::duration<uint32_t, nano>(end - start).count() << " ns" << std::endl;

    std::cout << "Reading 10k bytes: ";
    start = chrono::high_resolution_clock::now();
    for (uint16_t i = 0; i < buffer7.size(); i++) {
        buffer7 >> t1_b;
    }
    end = chrono::high_resolution_clock::now();
    std::cout << chrono::duration<uint32_t, nano>(end - start).count() << " ns" << std::endl;

    std::cout << "Writing 100k bytes: ";
    start = chrono::high_resolution_clock::now();
    CppStreamBuffer::Buffer buffer8;
    for (uint32_t i = 0; i < 100000; i++) {
        buffer8 << t1;
    }
    end = chrono::high_resolution_clock::now();
    std::cout << chrono::duration<uint32_t, nano>(end - start).count() << " ns" << std::endl;

    std::cout << "Reading 100k bytes: ";
    start = chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < buffer8.size(); i++) {
        buffer8 >> t1_b;
    }
    end = chrono::high_resolution_clock::now();
    std::cout << chrono::duration<uint32_t, nano>(end - start).count() << " ns" << std::endl;

    std::cout << "\nPrinting in HEX format: buffer << CppStreamBuffer::Format::HEX;" << std::endl;
    buffer8 << CppStreamBuffer::Format::HEX;
    std::cout << buffer8;

    return 0;
}