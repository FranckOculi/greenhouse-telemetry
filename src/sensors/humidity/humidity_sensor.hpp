#ifndef __HUMIDITY_SENSOR__
#define __HUMIDITY_SENSOR__

#include "i_humidity_driver.hpp"

#include <string>

class HumiditySensor {
    public :
        HumiditySensor(IHumidityDriver& d);
        float read();
        static const std::string SENSOR_ID;
        static const std::string SENSOR_NAME;

    private :
        IHumidityDriver& _driver;
};

#endif