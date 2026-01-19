#include "u80.hpp"

#include <stdint.h>

constexpr U80::U80(uint16_t x[5]):
    val()
{
    for (int i = 0; i < 5; i++) {
        val[i] = x.val[i];
    }
}

U80::U80(const U80& x) {
    for (int i = 0; i < 5; i++) {
        val[i] = x.val[i];
    }
}

U80::U80(const U80&& x):


U80& U80::operator=(const U80& other) const {
    if (this != &other) {
        for (int i = 0; i < 5; i++) {
            val[i] = other.val[i];
        }
    }
    return *this;
}

constexpr U80 U80::operator~() {
    std::array<uint16_t,5> res = {0};
    for (int i = 0; i < 5; i++) {
        res[i] = ~(val[i]);
    }
    return U80(res);
}

bool U80::operator[](const std::size_t n) {
    return (val[n / 16] & ((uint16_t)1 << (n % 16))) != 0;
}

bool U80::operator==(const U80& rhs) {
    for (int i = 0; i < 5; i++) {
        if (val[i] != rhs.val[i]) {
            return false;
        }
    }

    return true;
}

bool U80::operator!=(const U80& rhs) {
    for (int i = 0; i < 5; i++) {
        if (val[i] == rhs.val[i]) {
            return false;
        }
    }

    return true;
}

void U80::toggle(const std::size_t n) {
    uint8_t idx = n / 16;
    uint8_t s = n % 16;

    val[idx] ^= ((uint16_t)1 << s);
}

constexpr U80 operator""_xU80(const char* x, std::size_t sz) {
    std::array<uint16_t,5> r = {0};
    for (std::size_t i = 0; i < sz; i++) {
        uint8_t idx = 4 - (i / 4);
        uint8_t dig = i % 4;
        char c = x[sz - i - 1];
        if (c >= '0' && c <= '9') {
            r[idx] += (c - '0') * ((uint16_t)1 << (4*dig));
        }
        if (c >= 'A' && c <= 'F') {
            r[idx] += (c - 'A' + 10) * ((uint16_t)1 << (4*dig));
        }
        if (c >= 'a' && c <= 'f') {
            r[idx] += (c - 'a' + 10) * ((uint16_t)1 << (4*dig));
        }
    }

    return U80(r);
}
