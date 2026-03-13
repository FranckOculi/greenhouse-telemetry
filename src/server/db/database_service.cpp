#include "database_service.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

DatabaseService::DatabaseService(const std::string& host, const int port, const std::string& name)
: _si(host, port, name, std::getenv("DATABASE_USERNAME"), std::getenv("DATABASE_TOKEN")) {
    std::string query = "select * from " + name;
    if (select(query).find("database not found") != std::string::npos) {
        std::cout << "No database found for : " << name << std::endl;
        create(name);
    }
}

void DatabaseService::create(std::string name) {
    std::cout << "Creating database : " << name << std::endl;
    std::string res;
    influxdb_cpp::create_db(res, name, _si);
    if (res.find("database not found") != std::string::npos) {
        std::runtime_error("database not found");
    }
    
    std::cout << "Database created!\n";
}

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