#ifndef __AHT20_DRIVER_SIMULATED__
#define __AHT20_DRIVER_SIMULATED__

#include "i_temperature_driver.hpp"

#include <stdint.h>

// AHT20 Temp & Humidity Sensor
class AHT20DriverSimulated: public ITemperatureDriver {
    public : 
        void init() override;

        /**
         * t°c = (v / 2^20) * 200 - 50
         */
        uint32_t read_raw() override;

    private :
        int8_t min = -20;
        int8_t max = 90;
};

#endif