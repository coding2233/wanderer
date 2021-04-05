#ifndef OPENSSL_UTILITY_H
#define OPENSSL_UTILITY_H

#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/pem.h>

#include "base/system.h"
#include "base/easylogging++.h"

namespace wanderer
{
    class OpenSSLUtility
    {
    private:
        /* data */
    public:
        OpenSSLUtility(/* args */);
        ~OpenSSLUtility();

        //RSA公钥加密
        std::string EncryptRSA(const std::string &data);
        //RSA私钥解密
        std::string DecodeRSA(const std::string &data);
    };

}

#endif