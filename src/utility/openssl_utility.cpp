#include "utility/openssl_utility.h"

namespace wanderer
{
    OpenSSLUtility::OpenSSLUtility(/* args */)
    {
    }

    OpenSSLUtility::~OpenSSLUtility()
    {
        CRYPTO_cleanup_all_ex_data();
    }

    std::string OpenSSLUtility::EncryptRSA(const std::string &data)
    {
        const std::string public_pem_file = System::app_config_->rsa_public_key;
        FILE *pub_key_file_handle = fopen(public_pem_file.c_str(), "rb");
        if (pub_key_file_handle == nullptr)
        {
            std::string error_tip = "RSA public key file read failed: " + public_pem_file;
            std::runtime_error(error_tip.c_str());
            return "";
        }

        RSA *rsa_pub_key = RSA_new();
        if (PEM_read_RSA_PUBKEY(pub_key_file_handle, &rsa_pub_key, 0, 0) == NULL)
        {
            std::runtime_error("RSA public key read failed! ");
            return "";
        }

        int key_size = RSA_size(rsa_pub_key);
        char *encode = new char[key_size + 1];
        int ret = RSA_public_encrypt(data.length(), (const unsigned char *)data.c_str(), (unsigned char *)encode, rsa_pub_key, RSA_PKCS1_PADDING);
        std::string result_data;
        if (ret > 0)
        {
            result_data = std::string(encode, ret);
        }
        delete[] encode;
        RSA_free(rsa_pub_key);
        fclose(pub_key_file_handle);
        return result_data;
    }

    std::string OpenSSLUtility::DecodeRSA(const std::string &data)
    {
        const std::string private_pem_file = System::app_config_->rsa_private_key;

        FILE *key_file_handle = fopen(private_pem_file.c_str(), "rb");
        if (key_file_handle == nullptr)
        {
            std::string error_tip = "RSA private key file read failed: " + private_pem_file;
            std::runtime_error(error_tip.c_str());
            return "";
        }

        RSA *rsa_pri_key = RSA_new();
        if (PEM_read_RSAPrivateKey(key_file_handle, &rsa_pri_key, 0, 0) == NULL)
        {
            std::runtime_error("RSA private key read failed! ");
            return "";
        }
        int key_size = RSA_size(rsa_pri_key);
        char *encode = new char[key_size + 1];
        int ret = RSA_private_decrypt(data.length(), (const unsigned char *)data.c_str(), (unsigned char *)encode, rsa_pri_key, RSA_PKCS1_PADDING);
        std::string result_data;
        if (ret > 0)
        {
            result_data = std::string(encode, ret);
        }
        delete[] encode;
        RSA_free(rsa_pri_key);
        fclose(key_file_handle);
        return result_data;
    }
}