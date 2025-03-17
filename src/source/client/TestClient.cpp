//
// Created by maziyang on 25-3-17.
//

#include "TestClient.h"
#include "ConfigLoader.h"
#include "string"
#include "iostream"
#include "common.h"

TestClient::TestClient() : Client("127.0.0.1", 9831) {
    // Client();
    // TestClient("127.0.0.1", 9831);
}

TestClient::TestClient(const std::string &configPath_) {
    // Client(configPath_);
    // lknet::util::ConfigLoader& loader = lknet::util::ConfigLoader::getInstance();
    // loader.setConfigOptions({{"parseFormat", "json"}});
    // loader.loadConfig(configPath);
    // auto config = loader.getConfig();
    // std::string host = config["host"];
    // std::string port = config["port"];
    this->configPath = configPath;
    // TestClient(host, std::stoi(port));
}

TestClient::TestClient(const std::string &host, unsigned short port) {
    Client(host, port);
    this->host = host;
    this->port = port;
}

void TestClient::start()
{
    Client::start(true);
    std::string msg;
    while (true)
    {
        // 构造一个LoginDatabase
        Request request;
        request.setId(PROTOCOL_REQUEST_LOGIN);
        std::unique_ptr<LoginDataBase> db(new LoginDataBase());
        db->account = "account";
        db->password = "password";
        request.setData(std::move(db));
        send(request, [](const Response &r)
        {
            auto& data = r.getData();
            if (dynamic_cast<LoginDataBase*>(data.get()) != nullptr)
            {
                std::cout << "LoginDataBase1" << std::endl;
            }else
            {
                std::cout << "LoginDataBase2" << std::endl;
            }
        });

        // 睡眠一秒
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}

bool res = []()
{
    // 注册Database
    auto registerDataBase = []() -> bool { // 注册DataBase，用于支持动态序列化反序列化
        DataBaseRegister::getInstance().registerDataBase(PROTOCOL_REQUEST_LOGIN, [](){
            return std::make_unique<LoginDataBase>();
        });
        DataBaseRegister::getInstance().registerDataBase(PROTOCOL_REQUEST_REGISTER, [](){
            return std::make_unique<RegisterDataBase>();
        });
        DataBaseRegister::getInstance().registerDataBase(PROTOCOL_RESPONSE_STATUS, [](){
            return std::make_unique<DataBaseStatus>();
        });
        return true;
    }();



    return true;
}();
