#include "utility/openssl_utility.h"

namespace wanderer
{
    OpenSSLUtility::OpenSSLUtility(/* args */)
    {
    }

    OpenSSLUtility::~OpenSSLUtility()
    {
        // CRYPTO_cleanup_all_ex_data();
    }

    std::string OpenSSLUtility::EncryptRSA(const std::string &data)
    {
        // const std::string public_pem_file = System::app_config_->rsa_public_key;
        // FILE *pub_key_file_handle = fopen(public_pem_file.c_str(), "rb");
        // if (pub_key_file_handle == nullptr)
        // {
        //     std::string error_tip = "RSA public key file read failed: " + public_pem_file;
        //     std::runtime_error(error_tip.c_str());
        //     return "";
        // }
        BIO *bio_key = nullptr;
        RSA *rsa = nullptr;
        bio_key = BIO_new_mem_buf(rsa_public_key.c_str(), rsa_public_key.size());
        if (bio_key == nullptr)
        {
            LOG(FATAL) << "RSA BIO creation failed!";
        }

        // RSA *rsa_pub_key = RSA_new();

        // if (PEM_read_RSA_PUBKEY(pub_key_file_handle, &rsa_pub_key, 0, 0) == NULL)
        // {
        //     std::runtime_error("RSA public key read failed! ");
        //     return "";
        // }
        rsa = PEM_read_bio_RSA_PUBKEY(bio_key, nullptr, nullptr, nullptr);
        if (rsa == nullptr)
        {
            LOG(FATAL) << "RSA public key read failed!";
        }

        int key_size = RSA_size(rsa);
        char *encode = new char[key_size + 1];
        int ret = RSA_public_encrypt(data.length(), (const unsigned char *)data.c_str(), (unsigned char *)encode, rsa, RSA_PKCS1_PADDING);
        std::string result_data;
        if (ret > 0)
        {
            int ascii_base64_len;
            char *ascii_base64 = base64(encode, ret, &ascii_base64_len);
            result_data = std::string(ascii_base64, ascii_base64_len);
            // result_data = std::string(encode, ret);
        }
        LOG(INFO) << "EncryptRSA: " << data << " # " << result_data;
        delete[] encode;
        BIO_free(bio_key);
        RSA_free(rsa);
        // fclose(pub_key_file_handle);
        return result_data;
    }

    //Decrypt
    std::string OpenSSLUtility::DecodeRSA(const std::string &data)
    {
        // const std::string private_pem_file = System::app_config_->rsa_private_key;

        // FILE *key_file_handle = fopen(private_pem_file.c_str(), "rb");
        // if (key_file_handle == nullptr)
        // {
        //     std::string error_tip = "RSA private key file read failed: " + private_pem_file;
        //     std::runtime_error(error_tip.c_str());
        //     return "";
        // }

        // RSA *rsa_pri_key = RSA_new();
        // if (PEM_read_RSAPrivateKey(key_file_handle, &rsa_pri_key, 0, 0) == NULL)
        // {
        //     std::runtime_error("RSA private key read failed! ");
        //     return "";
        // }
        // int key_size = RSA_size(rsa_pri_key);
        // char *encode = new char[key_size + 1];
        // int ret = RSA_private_decrypt(data.length(), (const unsigned char *)data.c_str(), (unsigned char *)encode, rsa_pri_key, RSA_PKCS1_PADDING);
        // std::string result_data;
        // if (ret > 0)
        // {
        //     result_data = std::string(encode, ret);
        // }
        // delete[] encode;
        // RSA_free(rsa_pri_key);
        // fclose(key_file_handle);
        // return result_data;
        return data;
    }
}