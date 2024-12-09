//
// Created by banser on 24-11-28.
//

#include "eventCapturer.h"
#include "Server.h"
#include "common.h"

void initLogger(){
    logger::logger::Root()->setLevel(packer::Debug);
    logger::logger::Root()->setLogFormater("[%level] [%s {%Y-%m-%d %H:%M:%S}] [%path:%line]: %message\n");
}

void registerDataBase() {
    // 注册请求协议
    DataBaseRegister::getInstance().registerDataBase(PROTOCOL_REQUEST_LOGIN, [](){
        return std::make_unique<LoginDataBase>();
    });
    DataBaseRegister::getInstance().registerDataBase(PROTOCOL_REQUEST_REGISTER, [](){
        return std::make_unique<RegisterDataBase>();
    });
    // 注册响应协议
    DataBaseRegister::getInstance().registerDataBase(PROTOCOL_RESPONSE_STATUS, [](){
        return std::make_unique<DataBaseStatus>();
    });
};

void registerHandler() {
    RequestHandlerRouter::getInstance().registerHandlerGetterWithResponse(PROTOCOL_REQUEST_LOGIN, [](){
        return [](const Request& r) {
            std::cout << "this is handler(id: " << r.getId() << ")" << std::endl;
            return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
        };
    });
    RequestHandlerRouter::getInstance().registerHandlerGetterWithResponse(PROTOCOL_REQUEST_REGISTER, [](){
        return [](const Request& r) {
            std::cout << "this is handler(id: " << r.getId() << ")" << std::endl;
            return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
        };
    });
}

void initServer() {
    initLogger();
    registerDataBase();
    registerHandler();
}

/**
 * ./server host port[:8080]
 */

int main(int argc, char* argv[]){
    std::string host{};
    unsigned short port = 0;

    initServer();

    switch (argc) {
        case 1:
        {
            host = "0.0.0.0";
            port = 8080;
            break;
        }
        case 2:
        {
            host = argv[1];
            port = 8080;
            break;
        }
        case 3:
        {
            host = argv[1];
            unsigned short tmp = static_cast<unsigned short>(std::atoi(argv[2]));
            if(tmp){
                port = tmp;
                break;
            }
        }
        default:
        {
            // --help
            RootInfo() << "usage: \n" << argv[0] << " [host] [port]\ndefault use 0.0.0.0:8080";
            exit(1);
        }
    }

    start:
    try{
        Server server(host, port);
        // net kernel runs in current thread
        server.start();
    }catch(std::exception& e){
        RootError() << "Server Crashed as for: " << e.what();
        exit(1);
    }

    end:
    return 0;
}