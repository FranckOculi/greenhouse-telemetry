#ifndef __AHT20_HUMIDITY_DRIVER_SIMULATED__
#define __AHT20_HUMIDITY_DRIVER_SIMULATED__

#include "i_humidity_driver.hpp"

// AHT20 Temp & Humidity Sensor
class AHT20HumidityDriverSimulated : public IHumidityDriver {
    public :
        void init() override;

        /**
        * RH[%] = (Srh / 2^20) * 100%
        *
        * RH = Relative humidity
        * Srh = Relative humidity signal
        */
        uint32_t read_raw() override;

    private :
        int8_t min = 10;
        int8_t max = 90;
};
#endif