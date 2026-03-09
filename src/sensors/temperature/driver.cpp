#include "driver.hpp"

#include <stdlib.h>
#include <time.h>

void AHT20DriverSimulated::init() {
    srand(static_cast<int>(time(nullptr)));
}

uint32_t AHT20DriverSimulated::read_raw() {
    int temp = (rand() % (max - min + 1)) + min;
    uint32_t raw = static_cast<uint32_t>((temp + 50) / 200.0f * (1 << 20));

    if(raw > 0xFFFFF) raw = 0xFFFFF;
    return raw;
}