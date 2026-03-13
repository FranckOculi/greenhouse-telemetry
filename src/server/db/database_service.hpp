#ifndef __DATABASE_SERVICE
#define __DATABASE_SERVICE

#include "orca-zhang/influxdb.hpp"
#include <laserpants/dotenv.h>
#include <string>
#include <stdint.h>

class DatabaseService {
    public :
        struct Raw {
            std::string field;
            int value;
        };

        DatabaseService(const std::string& host = std::getenv("DATABASE_HOST"), const int port = std::atoi(std::getenv("DATABASE_PORT")), const std::string& name = std::getenv("DATABASE_NAME"));
        ~DatabaseService() = default;

        void create(std::string name);
        void insert(const std::string& meas, Raw& raw1, Raw& raw2);
        std::string select(std::string& query);
        void read(std::string res);

    private :
        influxdb_cpp::server_info _si;
        std::string _res;
};

#endif