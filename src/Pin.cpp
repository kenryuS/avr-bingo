#include "Pin.hpp"

#include <stdint.h>

Pin::Pin(uint8_t* pt, uint8_t pn):
    port(pt),
    pin(pn)
{}

Pin::Pin(const Pin& p) {
    if (this != &p) {
        port = p.port;
        pin = p.pin;
    }
}

Pin::Pin(const Pin&& p):
    port(p.port),
    pin(p.pin)
{}

Pin& Pin::operator=(const Pin& p) {
    if (this != &p) {
        port = p.port;
        pin = p.pin;
    }
    return *this;
}

void Pin::setPort(uint8_t* prt) {
    port = prt;
}

uint8_t* Pin::getPort() {
    return port;
}

void Pin::setPin(uint8_t pn) {
    pin = pn;
}

uint8_t Pin::getPin() {
    return pin;
}

bool Pin::getState() {
    return *port & (1 << pin);
}

void Pin::setState(bool x) {
    if (x) {
        *port |= (1 << pin);
    } else {
        *port &= ~(1 << pin);
    }
}
