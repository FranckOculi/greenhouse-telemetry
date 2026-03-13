#ifndef __DATABASE_SERVICE
#define __DATABASE_SERVICE

#include "orca-zhang/influxdb.hpp"
#include <string>
#include <stdint.h>

class DatabaseService {
    public :
        static const std::string HOST;
        static int PORT;
        static const std::string NAME;

        struct Raw {
            std::string field;
            int value;
        };

        DatabaseService(const std::string& host, const int port, const std::string& name);
        ~DatabaseService() = default;

        void insert(const std::string& meas, Raw& raw1, Raw& raw2);
        std::string select(std::string& query);
        void read(std::string res);

    private :
        influxdb_cpp::server_info _si;
        std::string _res;
};

#endif