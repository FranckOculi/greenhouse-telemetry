#include "database_service.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

const std::string DatabaseService::HOST = "127.0.0.1";
int DatabaseService::PORT = 8086;
const std::string DatabaseService::NAME = "sensors";

DatabaseService::DatabaseService(const std::string& host, const int port, const std::string& name) : _si(host, port, name) {}

void DatabaseService::insert(const std::string& meas, Raw& raw1, Raw& raw2) {
    influxdb_cpp::builder()
        .meas(meas)
        .field(raw1.field, raw1.value)
        .field(raw2.field, raw2.value)
        .post_http(_si);
}

std::string DatabaseService::select(std::string& query) {
    influxdb_cpp::query(_res, query, _si);
    return _res;
}

void DatabaseService::read(std::string data) {
    nlohmann::json j = nlohmann::json::parse(data);

    auto columns = j["results"][0]["series"][0]["columns"];
    auto values  = j["results"][0]["series"][0]["values"];

    for (const auto& row : values) {

        for (size_t i = 0; i < columns.size(); i++) {
            std::cout << columns[i] << " = " << row[i] << " ";
        }

        std::cout << std::endl;
    }
}