#ifndef __OPENSSL_UTILITY_H__
#define __OPENSSL_UTILITY_H__

#include <iostream>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <string>

#include "base/easylogging++.h"
#include "utility/base64.h"
#include "utility/utility.h"

namespace wanderer
{

    //#define byte unsigned char

    class OpenSSLUtility
    {
    private:
        /* data */
        std::string rsa_public_key = "-----BEGIN PUBLIC KEY-----\n"
                                     "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCanf92YkIxqkXaZUhWkCC5tiPn\n"
                                     "o7xP057AjL3uJ3QzNCFkR3FnVj6VtKgLD6sxR/e2rH7FtnX2WF+aXDcv7zzBi6f6\n"
                                     "qeDvGGy6ActlNz+YMdscFrwz0ISMIpcJ0JsgBZ6WTLqDSp5zwXMrebCx6DJq2p7V\n"
                                     "RVaFx8dQJWPClVGg1QIDAQAB\n"
                                     "-----END PUBLIC KEY-----\n";
#if BUILD_EXEC
        std::string rsa_private_key = "-----BEGIN RSA PRIVATE KEY-----\n"
                                      "MIICXAIBAAKBgQCanf92YkIxqkXaZUhWkCC5tiPno7xP057AjL3uJ3QzNCFkR3Fn\n"
                                      "Vj6VtKgLD6sxR/e2rH7FtnX2WF+aXDcv7zzBi6f6qeDvGGy6ActlNz+YMdscFrwz\n"
                                      "0ISMIpcJ0JsgBZ6WTLqDSp5zwXMrebCx6DJq2p7VRVaFx8dQJWPClVGg1QIDAQAB\n"
                                      "AoGAKCitd5Qh2UB+kDEKTuF0fofeX4XZnWo7q4tisX6x4bLCkYc030A5VSztEKJr\n"
                                      "NouYvWukKbowfWGKw078Toj24G8EmI7xocCzZ21zI/AxBSbz0mt4Gja/Kadxciu5\n"
                                      "LvQnJpEnT/jQsF/YF/6HCf+dVVJWco78+p0nypi2ghg+Q+kCQQDLCmiVKI3Ad4vd\n"
                                      "JSMq0UalBgEmYrhGG2kcJCOgrsy6wGWmELMqLiI/A1CFWkTFgr458n0Ku5rWYNh3\n"
                                      "/5t1EnNnAkEAwvI38SJd//XHpvEiFb2tFIC+bWi1CdViVPAQAlVhUbG5Da9M6+Gb\n"
                                      "Z6jqxDnnXZclZg2ixcGa3xODnGkDcPkAYwJBAMUZNorNEkXrBr/HZEsVWnGp0YX0\n"
                                      "wRN1WmSyBE/gP+duC37YqUPiAuaOjiTVivr8vzK7XX0Evvsqihh67esI3TMCQGYS\n"
                                      "w53bu9JI08ginBE8JoMEwjCxUZGbjAgjRo6iO/m1j8qNjj43+9H0DTC/jNhhSrC7\n"
                                      "1Q2syLWjFxdvmOCvUDcCQALzUEBfzqcEuFRwGpTliN9u6AwOuJYNx8ajPRuSnmHs\n"
                                      "Ejo/CIMpO1yP594IWyWp6d1n92ilEcMk1GTYMdeQTug=\n"
                                      "-----END RSA PRIVATE KEY-----\n";
#else
        std::string rsa_private_key = "";
#endif

    public:
        OpenSSLUtility(/* args */);
        ~OpenSSLUtility();

        //RSA公钥加密
        std::string EncryptRSA(const std::string data);
        //RSA私钥解密 Decrypt
        std::string DecryptRSA(const std::string data);
        //AES随机密钥
        static void RandSecretKey(char *secret_key, int size);
        //AES加密
        std::string EncryptAES(const std::string &data, const std::string &key);
        //AES解密
        std::string DecryptAES(const std::string &data, const std::string &key);
        //md5加密
        static std::string Md5(const std::string &data);
    };

}

#endif