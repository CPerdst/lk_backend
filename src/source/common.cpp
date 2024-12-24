//
// Created by l1Akr on 2024/12/11.
//

#include "common.h"
#include "tools.h"
//#include "boost/mysql.hpp"

// -----------------
// LoginDataBase 实现
// -----------------

LoginDataBase::LoginDataBase(std::string account, std::string password):
account(std::move(account)),
password(std::move(password)){}

void LoginDataBase::from_json(const nlohmann::json &j) {
    j.at("account").get_to(account);
    j.at("password").get_to(password);
}

nlohmann::json LoginDataBase::to_json() {
    return {{"account", account}, {"password", password}};
}

// -----------------
// RegisterDataBase 实现
// -----------------

RegisterDataBase::RegisterDataBase(std::string account, std::string username, std::string password, std::string phone):
account(std::move(account)),
username(std::move(username)),
password(std::move(password)),
phone(std::move(phone)){}

void RegisterDataBase::from_json(const nlohmann::json &j) {
    j.at("account").get_to(account);
    j.at("username").get_to(username);
    j.at("password").get_to(password);
    j.at("phone").get_to(phone);
}

nlohmann::json RegisterDataBase::to_json() {
    return {{"account", account},
            {"username", username},
            {"password", password},
            {"phone", phone}};
}

// -----------------
// 初始化Server
// 注册DataBase
// 注册Handler
// -----------------

auto initServer = []() -> bool {
    auto initLogger = [](){ // 初始化Logger
        logger::logger::Root()->setLevel(packer::Debug);
        if(logger::logger::Root()->getLevel() == packer::Debug){
            logger::logger::Root()->setLogFormater("[%level] [%s {%Y-%m-%d %H-%M-%S}] [%path:%line]: %message \n");
        }else if(logger::logger::Root()->getLevel() == packer::Info){
            logger::logger::Root()->setLogFormater("[%level] [%s {%Y-%m-%d %H-%M-%S}]: %message \n");
        }
        return true;
    }();

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

    auto registerRequestHandler = []() -> bool { // 注册对应协议请求的Handler
        RequestHandlerRouter::getInstance().registerHandlerGetterWithResponse(PROTOCOL_REQUEST_LOGIN, [](){
            return [](const Request&) -> Response {
                /**
                 * 登录逻辑：
                 */
               return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
            };
        });
        RequestHandlerRouter::getInstance().registerHandlerGetterWithResponse(PROTOCOL_REQUEST_REGISTER, [](){
            return [](const Request& request) -> Response {
                auto data = dynamic_cast<RegisterDataBase*>(request.getData().get());
                /**
                 * 注册逻辑：
                 * 1、判断参数是否不为空、且格式正确（用户名：长度6-18，只能为数字，
                 * 密码：长度6-18，只能为ASCII可见字符，必须包含大小写字母和数字，
                 * 手机号：必须符合中国手机号格式）
                 * 2、像数据库中写入用户信息
                 * 3、判断插入结果，是否成功
                 * 3.1 成功则返回注册成功
                 * 3.2 失败则根据插入结果返回错误状态
                 */
                if(data->account.empty() ||
                   data->username.empty() |\
                   data->password.empty() ||
                   data->phone.empty()){
                    return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
                }

                if (!isValidAccount(data->account)) { // 账号格式不正确
                    return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
                }

                if(!isValidPassword(data->password)) { // 密码格式不正确
                    return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
                }

                if(!isValidPhoneNum(data->phone)) { // 手机号格式不正确
                    return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
                }

                { // 使用Boost.Mysql模块进行数据库操作


                }


                return Response{PROTOCOL_RESPONSE_STATUS, std::make_unique<DataBaseStatus>(DataBaseStatus::Success)};
            };
        });
        return true;
    }();

    return true;
}();