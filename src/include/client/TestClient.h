//
// Created by maziyang on 25-3-17.
//

#ifndef TESTCLIENT_H
#define TESTCLIENT_H
#include "Client.h"
#include <string>

class TestClient : public Client {
public:
    TestClient();
    explicit TestClient(const std::string &configPath);
    TestClient(const std::string &host, unsigned short port);

    void start();

private:
    std::string host;
    std::string port;
    std::string configPath;

};

#endif //TESTCLIENT_H
