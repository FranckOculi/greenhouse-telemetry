#ifndef __AHT20_TEMPERATURE_DRIVER_SIMULATED__
#define __AHT20_TEMPERATURE_DRIVER_SIMULATED__

#include "i_temperature_driver.hpp"

// AHT20 Temp & Humidity Sensor
class AHT20TemperatureDriverSimulated : public ITemperatureDriver {
    public : 
        void init() override;

        /**
         * T(°c) = (St / 2^20) * 200 - 50
         * 
         * St = Temperature signal
         */
        uint32_t read_raw() override;

    private :
        int8_t min = -20;
        int8_t max = 90;
};

#endif