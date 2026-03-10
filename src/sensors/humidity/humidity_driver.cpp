#include "humidity_driver.hpp"

#include <stdlib.h>
#include <time.h>

void AHT20HumidityDriverSimulated::init() {
    srand(static_cast<int>(time(nullptr)));
}

uint32_t AHT20HumidityDriverSimulated::read_raw() {
    int humidity = (rand() % (max - min + 1)) + min;
    uint32_t raw = static_cast<uint32_t>(humidity / 100.0f * (1 << 20));

    if(raw > 0xFFFFF) raw = 0xFFFFF;
    return raw;
}