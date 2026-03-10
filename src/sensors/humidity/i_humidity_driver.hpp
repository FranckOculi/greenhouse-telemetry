#ifndef __I_HUMIDITY_DRIVER__
#define __I_HUMIDITY_DRIVER__

#include <stdint.h>

class IHumidityDriver {
    public : 
        virtual void init() = 0;
        virtual uint32_t read_raw() = 0;
        virtual ~IHumidityDriver() = default;
};

#endif