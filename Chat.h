#pragma once
#include <string>
#include "SHA1.h"
#include "HashTable.h"

#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    ~Chat();
    void reg(const char _login[LOGINLENGTH], const char _pass[], const int pass_length);
    bool login(const char _login[LOGINLENGTH], const char _pass[], const int pass_length);

private:
    HashTable* _data;
};
