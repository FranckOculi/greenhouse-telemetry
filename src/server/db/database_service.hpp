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
    
        DatabaseService(const std::string& host, const int port, const std::string& name);
        ~DatabaseService() = default;

        void insert(const std::string& field, int& value);
        std::string select(std::string& query);
        void read(std::string res);

    private :
        influxdb_cpp::server_info _si;
        std::string _res;
};

#endif