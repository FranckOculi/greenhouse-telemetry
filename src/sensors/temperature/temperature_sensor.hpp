#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

#include "i_temperature_driver.hpp"

class TemperatureSensor {
    public : 
        TemperatureSensor(ITemperatureDriver& d);
        float read();

    private : 
        ITemperatureDriver& _driver;
};


#endif