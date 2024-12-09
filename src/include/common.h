//
// Created by l1Akr on 2024/12/9.
//

#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

enum PROTOCOL_MAPS {
    PROTOCOL_REQUEST_LOGIN = 0x101,
    PROTOCOL_REQUEST_REGISTER = 0x102,
    PROTOCOL_RESPONSE_STATUS = 0x201
};

struct LoginDataBase: public DataBase{
    std::string username{};
    std::string password{};

    void from_json(nlohmann::json &j) override {
        j.at("username").get_to(username);
        j.at("password").get_to(password);
    }

    nlohmann::json to_json() override {
        return {{"username", username}, {"password", password}};
    }
};

struct RegisterDataBase: public DataBase {
    std::string username{};
    std::string password{};

    void from_json(nlohmann::json &j) override {
        j.at("username").get_to(username);
        j.at("password").get_to(password);
    }

    nlohmann::json to_json() override {
        return {{"username", username}, {"password", password}};
    }
};

#endif //SERVER_COMMON_H
