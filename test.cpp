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
    std::string t12("amazing big string to t!!! áúã''@ç");
    std::string t12_b;

    CppStreamBuffer::Buffer buffer;
    buffer << t1 << t2 << t3 << t4 << t5 << t6 << t7 << t8 << t9 << t10 << t11 << t12;

    buffer >> t1_b >> t2_b >> t3_b >> t4_b >> t5_b >> t6_b >> t7_b >> t8_b >> t9_b >> t10_b >> t11_b >> t12_b;

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

    return 0;
}