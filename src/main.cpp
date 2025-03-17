//
// Created by banser on 24-11-28.
//

#include "cmdline.h"
#include "Server.h"
#include "EventCapturer.h"
#include "TestClient.h"

/**
 * ./server host port[:8080]
 */

int start_client(const std::string& host, const std::string& port)
{
    try
    {
        TestClient testClient{};
        testClient.start();
    }catch(const std::exception& e)
    {
        RootError() << "Client Crashed as for: " << e.what();
        return 1;
    }
    return 0;
}

int start_server(const std::string& host, const std::string& port)
{
    try{
        Server server(host, std::stoi(port));
        // net kernel runs in current thread
        server.start();
    }catch(std::exception& e){
        RootError() << "Server Crashed as for: " << e.what();
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]){
    cmdline::parser cmd;
    cmd.add<std::string>(
        "host"
        , 'h'
        , "host name"
        , false
        , "127.0.0.1");
    cmd.add<std::string>(
        "port"
        , 'p'
        , "port number"
        , false
        , "9831");
    cmd.add<std::string>(
        "client"
        , 'c'
        , "use client"
        , false
        , "no"
        , cmdline::oneof<std::string>("yes", "no", "true", "false"));
    cmd.add<std::string>(
        "target-host"
        ,'t'
        ,"the target server host"
        ,false
        , "127.0.0.1");
    cmd.add<std::string>(
        "target-port"
        ,'a'
        ,"the target server port"
        ,false
        , "9831");
    cmd.parse(argc, argv);
    std::string option = cmd.get<std::string>("client");
    if(option == "yes" || option == "true") {
        start_client(
            cmd.get<std::string>("target-host")
            , cmd.get<std::string>("target-port"));
    }else {
        start_server(
            cmd.get<std::string>("host")
            , cmd.get<std::string>("port"));
    }
}

