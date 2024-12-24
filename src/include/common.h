//
// Created by l1Akr on 2024/12/9.
//

#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "Server.h"

enum PROTOCOL_MAPS {
    PROTOCOL_REQUEST_LOGIN = 0x101,
    PROTOCOL_REQUEST_REGISTER = 0x102,
    PROTOCOL_RESPONSE_STATUS = 0x201
};

struct LoginDataBase: public DataBase{
    std::string account{};
    std::string password{};

    LoginDataBase() = default;
    ~LoginDataBase() override = default;

    LoginDataBase(std::string, std::string);

    void from_json(const nlohmann::json &j) override;

    nlohmann::json to_json() override;
};

struct RegisterDataBase: public DataBase {
    RegisterDataBase() = default;
    ~RegisterDataBase() override = default;

    RegisterDataBase(std::string, std::string, std::string, std::string);

    std::string account{};
    std::string username{};
    std::string password{};
    std::string phone{};

    void from_json(const nlohmann::json &j) override;

    nlohmann::json to_json() override;
};

#endif //SERVER_COMMON_H
