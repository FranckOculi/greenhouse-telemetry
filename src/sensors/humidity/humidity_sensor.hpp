#ifndef __HUMIDITY_SENSOR__
#define __HUMIDITY_SENSOR__

#include "i_humidity_driver.hpp"

class HumiditySensor {
    public :
        HumiditySensor(IHumidityDriver& d);
        float read();

    private :
        IHumidityDriver& _driver;
};

#endif