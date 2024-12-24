//
// Created by l1Akr on 2024/12/12.
//

#include "tools.h"
#include "string"
#include "regex"

bool isValidAccount(const std::string& account) {
    if (account.length() < 6 || account.length() > 18) return false;
    std::regex accountPattern("^[0-9]+$");
    return std::regex_match(account, accountPattern);
}

bool isValidUsername(const std::string&){

}

bool isValidPhoneNum(const std::string& phoneNum){
    std::regex phonePattern("^1[3-9][0-9]{9}$");
    return std::regex_match(phoneNum, phonePattern);
}

bool isValidPassword(const std::string& password){
    if (password.length() < 6 || password.length() > 18) return false;
    std::regex passwordPattern(
            "^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])[!-~]+$"); // ASCII可见字符，包含大小写字母和数字
    return std::regex_match(password, passwordPattern);
}
