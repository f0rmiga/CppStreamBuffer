/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Thulio Ferraz Assis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * :)
 *
 * Tell me at (contato at thulioassis dot com dot br) if you are using it
 *
 */

#ifndef CPP_STREAM_BUFFER_HPP
#define CPP_STREAM_BUFFER_HPP

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>

using namespace std;

const int iCheck = 1;
#define isLE() ( (*(char*)&iCheck) != 0 ) // check if the system is little-endian
#define ieee754Err std::runtime_error("Your system is not using IEEE 754, don't use float and double operations")

namespace CppStreamBuffer {
    enum Endianness {
        LITTLE, BIG
    };

    enum Format {
        BINARY, HEX
    };

    class Buffer {
    public:
        explicit Buffer() : endianness(Endianness::BIG) { }

        explicit Buffer(Endianness endianness) : endianness(endianness) { }

        explicit Buffer(Endianness endianness, size_t reserve) : endianness(endianness) {
            buffer.reserve(reserve);
        }

        explicit Buffer(size_t reserve) : endianness(Endianness::BIG) {
            buffer.reserve(reserve);
        }

        ~Buffer() { }

        size_t size() { return size_; }

        Buffer &operator<<(const Format &flag) {
            printformat = flag;
            return *this;
        }

        Buffer &operator<<(const bool &var) {
            buffer += (var & 0xFF);
            size_++;
            return *this;
        }

        Buffer &operator<<(const int8_t &var) {
            buffer += (var & 0xFF);
            size_++;
            return *this;
        }

        Buffer &operator<<(const uint8_t &var) {
            buffer += (var & 0xFF);
            size_++;
            return *this;
        }

        Buffer &operator<<(const int16_t &var) {
            Append16(var);
            return *this;
        }

        Buffer &operator<<(const uint16_t &var) {
            Append16(var);
            return *this;
        }

        Buffer &operator<<(const int32_t &var) {
            Append32(var);
            return *this;
        }

        Buffer &operator<<(const uint32_t &var) {
            Append32(var);
            return *this;
        }

        Buffer &operator<<(const int64_t &var) {
            Append64(var);
            return *this;
        }

        Buffer &operator<<(const uint64_t &var) {
            Append64(var);
            return *this;
        }

        Buffer &operator<<(const float &var) {
            if (std::numeric_limits<float>::is_iec559) {
                uint8_t b[4];
                memcpy(b, &var, 4);
                if ((isLE() && endianness == Endianness::BIG) || (!isLE() && endianness == Endianness::LITTLE))
                    std::reverse(std::begin(b), std::end(b));
                for (uint8_t i = 0; i < 4; i++) {
                    buffer += (b[i] & 0xFF);
                }
                size_ += 4;
            } else {
                throw ieee754Err;
            }
            return *this;
        }

        Buffer &operator<<(const double &var) {
            if (std::numeric_limits<float>::is_iec559) {
                uint8_t b[8];
                memcpy(b, &var, 8);
                if ((isLE() && endianness == Endianness::BIG) || (!isLE() && endianness == Endianness::LITTLE))
                    std::reverse(std::begin(b), std::end(b));
                for (uint8_t i = 0; i < 8; i++) {
                    buffer += (b[i] & 0xFF);
                }
                size_ += 8;
            } else {
                throw ieee754Err;
            }
            return *this;
        }

        Buffer &operator<<(const string &var) {
            if (var.size() <= numeric_limits<uint16_t>::max()) {
                *this << (uint16_t) var.size();
                buffer += var;
                size_ += var.size() + sizeof(uint16_t);
            }
            return *this;
        }

        Buffer &operator>>(bool &var) {
            if (readpos + 1 <= size_) {
                var = buffer[readpos];
                readpos++;
            }
            return *this;
        }

        Buffer &operator>>(int8_t &var) {
            if (readpos + 1 <= size_) {
                var = buffer[readpos];
                readpos++;
            }
            return *this;
        }

        Buffer &operator>>(uint8_t &var) {
            if (readpos + 1 <= size_) {
                var = (uint8_t) buffer[readpos];
                readpos++;
            }
            return *this;
        }

        Buffer &operator>>(int16_t &var) {
            if (readpos + 2 <= size_) {
                Get16(var);
                readpos += 2;
            }
            return *this;
        }

        Buffer &operator>>(uint16_t &var) {
            if (readpos + 2 <= size_) {
                Get16(var);
                readpos += 2;
            }
            return *this;
        }

        Buffer &operator>>(int32_t &var) {
            if (readpos + 4 <= size_) {
                Get32(var);
                readpos += 4;
            }
            return *this;
        }

        Buffer &operator>>(uint32_t &var) {
            if (readpos + 4 <= size_) {
                Get32(var);
                readpos += 4;
            }
            return *this;
        }

        Buffer &operator>>(int64_t &var) {
            if (readpos + 8 <= size_) {
                Get64(var);
                readpos += 8;
            }
            return *this;
        }

        Buffer &operator>>(uint64_t &var) {
            if (readpos + 8 <= size_) {
                Get64(var);
                readpos += 8;
            }
            return *this;
        }

        Buffer &operator>>(float &var) {
            if (std::numeric_limits<float>::is_iec559) {
                if (readpos + 4 <= size_) {
                    uint8_t b[] = {(uint8_t) buffer[readpos],
                                   (uint8_t) buffer[readpos + 1],
                                   (uint8_t) buffer[readpos + 2],
                                   (uint8_t) buffer[readpos + 3]};
                    if ((isLE() && endianness == Endianness::BIG) || (!isLE() && endianness == Endianness::LITTLE))
                        std::reverse(std::begin(b), std::end(b));
                    memcpy(&var, &b, 4);
                    readpos += 4;
                }
            } else {
                throw ieee754Err;
            }
            return *this;
        }

        Buffer &operator>>(double &var) {
            if (std::numeric_limits<double>::is_iec559) {
                if (readpos + 8 <= size_) {
                    uint8_t b[] = {(uint8_t) buffer[readpos],
                                   (uint8_t) buffer[readpos + 1],
                                   (uint8_t) buffer[readpos + 2],
                                   (uint8_t) buffer[readpos + 3],
                                   (uint8_t) buffer[readpos + 4],
                                   (uint8_t) buffer[readpos + 5],
                                   (uint8_t) buffer[readpos + 6],
                                   (uint8_t) buffer[readpos + 7]};
                    if ((isLE() && endianness == Endianness::BIG) || (!isLE() && endianness == Endianness::LITTLE))
                        std::reverse(std::begin(b), std::end(b));
                    memcpy(&var, &b, 8);
                    readpos += 8;
                }
            } else {
                throw ieee754Err;
            }
            return *this;
        }

        Buffer &operator>>(string &var) {
            var.clear();
            uint16_t s_size;
            *this >> s_size;
            copy(buffer.begin() + readpos, buffer.begin() + readpos + s_size, back_inserter(var));
            readpos += s_size;
            return *this;
        }

        friend ostream &operator<<(ostream &ostr, const Buffer &buff) {
            switch (buff.printformat) {
                case Format::BINARY: {
                    ostr << buff.buffer;
                }
                    break;

                case Format::HEX: {
                    ostringstream oss;

                    oss << "< ";
                    oss << uppercase << hex << setw(2) << setfill('0');
                    for_each(buff.buffer.begin(), buff.buffer.begin() + min(buff.buffer.size(), (size_t) 50),
                             [&](int8_t c) {
                                 oss << "0x" << static_cast<uint32_t>(static_cast<uint8_t>(c)) << " ";
                             });
                    if (buff.buffer.size() > 50)
                        oss << dec << "... " << buff.buffer.size() - 50 << " more item" <<
                        (buff.buffer.size() - 50 > 1 ? "s " : " ");
                    oss << ">";

                    ostr << oss.str();
                }
                    break;

                default:
                    break;
            }
            return ostr;
        }

    private:
        template<typename T>
        inline void Append16(const T &var) {
            if (endianness == CppStreamBuffer::Endianness::LITTLE) {
                buffer += (var & 0xFF);
                buffer += ((var >> 8) & 0xFF);
            } else {
                buffer += ((var >> 8) & 0xFF);
                buffer += (var & 0xFF);
            }
            size_ += 2;
        }

        template<typename T>
        inline void Append32(const T &var) {
            if (endianness == CppStreamBuffer::Endianness::LITTLE) {
                buffer += (var & 0xFF);
                buffer += ((var >> 8) & 0xFF);
                buffer += ((var >> 16) & 0xFF);
                buffer += ((var >> 24) & 0xFF);
            } else {
                buffer += ((var >> 24) & 0xFF);
                buffer += ((var >> 16) & 0xFF);
                buffer += ((var >> 8) & 0xFF);
                buffer += (var & 0xFF);
            }
            size_ += 4;
        }

        template<typename T>
        inline void Append64(const T &var) {
            if (endianness == CppStreamBuffer::Endianness::LITTLE) {
                buffer += (var & 0xFF);
                buffer += ((var >> 8) & 0xFF);
                buffer += ((var >> 16) & 0xFF);
                buffer += ((var >> 24) & 0xFF);
                buffer += ((var >> 32) & 0xFF);
                buffer += ((var >> 40) & 0xFF);
                buffer += ((var >> 48) & 0xFF);
                buffer += ((var >> 56) & 0xFF);
            } else {
                buffer += ((var >> 56) & 0xFF);
                buffer += ((var >> 48) & 0xFF);
                buffer += ((var >> 40) & 0xFF);
                buffer += ((var >> 32) & 0xFF);
                buffer += ((var >> 24) & 0xFF);
                buffer += ((var >> 16) & 0xFF);
                buffer += ((var >> 8) & 0xFF);
                buffer += (var & 0xFF);
            }
            size_ += 8;
        }

        template<typename T>
        inline void Get16(T &var) {
            if (endianness == CppStreamBuffer::Endianness::LITTLE) {
                var = ((uint16_t) (uint8_t) buffer[readpos + 1] << 8) | (uint8_t) buffer[readpos];
            } else {
                var = ((uint16_t) (uint8_t) buffer[readpos] << 8) | (uint8_t) buffer[readpos + 1];
            }
        }

        template<typename T>
        inline void Get32(T &var) {
            if (endianness == CppStreamBuffer::Endianness::LITTLE) {
                var = ((uint32_t) (uint8_t) buffer[readpos + 3] << 24) |
                      ((uint32_t) (uint8_t) buffer[readpos + 2] << 16) |
                      ((uint16_t) (uint8_t) buffer[readpos + 1] << 8) |
                      (uint8_t) buffer[readpos];
            } else {
                var = ((uint32_t) (uint8_t) buffer[readpos] << 24) |
                      ((uint32_t) (uint8_t) buffer[readpos + 1] << 16) |
                      ((uint16_t) (uint8_t) buffer[readpos + 2] << 8) |
                      (uint8_t) buffer[readpos + 3];
            }
        }

        template<typename T>
        inline void Get64(T &var) {
            if (endianness == CppStreamBuffer::Endianness::LITTLE) {
                var = ((uint64_t) (uint8_t) buffer[readpos + 7] << 56) |
                      ((uint64_t) (uint8_t) buffer[readpos + 6] << 48) |
                      ((uint64_t) (uint8_t) buffer[readpos + 5] << 40) |
                      ((uint64_t) (uint8_t) buffer[readpos + 4] << 32) |
                      ((uint32_t) (uint8_t) buffer[readpos + 3] << 24) |
                      ((uint32_t) (uint8_t) buffer[readpos + 2] << 16) |
                      ((uint16_t) (uint8_t) buffer[readpos + 1] << 8) |
                      (uint8_t) buffer[readpos];
            } else {
                var = ((uint64_t) (uint8_t) buffer[readpos] << 56) |
                      ((uint64_t) (uint8_t) buffer[readpos + 1] << 48) |
                      ((uint64_t) (uint8_t) buffer[readpos + 2] << 40) |
                      ((uint64_t) (uint8_t) buffer[readpos + 3] << 32) |
                      ((uint32_t) (uint8_t) buffer[readpos + 4] << 24) |
                      ((uint32_t) (uint8_t) buffer[readpos + 5] << 16) |
                      ((uint16_t) (uint8_t) buffer[readpos + 6] << 8) |
                      (uint8_t) buffer[readpos + 7];
            }
        }

        // copy ctor and assignment not implemented; copying not allowed
        Buffer(const Buffer &);

        Buffer &operator=(const Buffer &);

        string buffer;

        size_t size_ = 0;
        uint32_t readpos = 0;

        Endianness endianness;
        Format printformat = Format::BINARY;
    };
}

#endif // CPP_STREAM_BUFFER_HPP