//
// Created by banser on 24-11-28.
//

#include "eventCapturer.h"
#include "Server.h"
#include "common.h"

/**
 * ./server host port[:8080]
 */

int main(int argc, char* argv[]){
    std::string host{};
    unsigned short port = 0;

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