#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

#include "i_temperature_driver.hpp"

#include <string>

class TemperatureSensor {
    public : 
        TemperatureSensor(ITemperatureDriver& d);
        float read();
        static const std::string SENSOR_ID;
        static const std::string SENSOR_NAME;

    private : 
        ITemperatureDriver& _driver;
};


#endif