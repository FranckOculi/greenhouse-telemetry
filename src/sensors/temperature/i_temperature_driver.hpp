#ifndef __I_TEMPERATURE_DRIVER__
#define __I_TEMPERATURE_DRIVER__

#include <stdint.h>

class ITemperatureDriver {
    public : 
        virtual void init() = 0;
        virtual uint32_t read_raw() = 0;
        virtual ~ITemperatureDriver() = default;
};

#endif