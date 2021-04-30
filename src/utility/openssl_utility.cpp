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

    std::string OpenSSLUtility::EncryptRSA(const std::string data)
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
            LOG(FATAL) << "RSA public key read failed!"<<rsa_public_key;
        }

        int rsa_size = RSA_size(rsa);
        char *encode = new char[rsa_size + 1];
        int ret = RSA_public_encrypt(data.size(), (const unsigned char *)data.c_str(), (unsigned char *)encode, rsa, RSA_PKCS1_PADDING);
        std::string result_data;
        if (ret > 0)
        {
            int ascii_base64_len;
            char *ascii_base64 = base64(encode, ret, &ascii_base64_len);
            result_data = std::string(ascii_base64, ascii_base64_len);
            delete ascii_base64;
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
    std::string OpenSSLUtility::DecryptRSA(const std::string data)
    {
        BIO *bio_key = nullptr;
        RSA *rsa = nullptr;
        bio_key = BIO_new_mem_buf(rsa_private_key.c_str(), rsa_private_key.size());
        if (bio_key == nullptr)
        {
            LOG(FATAL) << "RSA BIO creation failed!";
        }
        
        rsa = PEM_read_bio_RSAPrivateKey(bio_key, nullptr, nullptr, nullptr);
        if (rsa == nullptr)
        {
            LOG(FATAL) << "RSA prvaite key read failed!";
        }
        int rsa_size = RSA_size(rsa);
        char *decode = new char[rsa_size + 1];

        //unbase64
        int binary_base64_len;
        const unsigned char *binary_base64 = unbase64((const char *)data.c_str(), data.size(), &binary_base64_len);
        //decrypt
        int ret = RSA_private_decrypt(binary_base64_len, binary_base64, (unsigned char *)decode, rsa, RSA_PKCS1_PADDING);
        std::string result_data;
        if (ret > 0)
        {
            result_data = std::string(decode, ret);
        }
        LOG(INFO) << "DecryptRSA: " << data << " # " << result_data;
        delete binary_base64;
        delete[] decode;
        BIO_free(bio_key);
        RSA_free(rsa);
        return result_data;
    }

    void OpenSSLUtility::RandSecretKey(char *secret_key, int size)
    {
        unsigned char*rand_bytes = new unsigned char[size];
        if (!RAND_bytes(rand_bytes, size))
        {
            LOG(FATAL) << "OpenSSL failed to generate a random key!";
        }
        int ascii_base64_len;
        char *ascii_base64 = base64(rand_bytes, size, &ascii_base64_len);
        std::memcpy(secret_key, ascii_base64, size);
        delete[] rand_bytes;
        delete ascii_base64;
    }

    //AES加密
    std::string OpenSSLUtility::EncryptAES(const std::string &data, const std::string &key)
    {
        AES_KEY aes_key;
        int key_size = key.size();
        if (AES_set_encrypt_key((const unsigned char*)key.c_str(), key_size * 8, &aes_key) < 0)
        {
            LOG(FATAL) << "AES encrypt key creation failed！ ";
        }
        int in_size = data.length() + 4;
        int out_size = in_size + (key_size - (in_size % key_size));
        unsigned char*out_data = new unsigned char[out_size];
        unsigned char*in_data = new unsigned char[out_size];
        Int2CharPointer((char *)in_data, data.size());
        std::memcpy(in_data + 4, (const unsigned char*)data.c_str(), in_size);
        for (size_t i = in_size; i < out_size; i++)
        {
            in_data[i] = 0;
        }
        int index = 0;
        unsigned char*buffer = new unsigned char[key_size];
        while (index < out_size)
        {
            AES_cbc_encrypt(in_data + index, out_data + index, key_size, &aes_key, buffer, AES_ENCRYPT);
            index += key_size;
        }

        int ascii_base64_len;
        char *ascii_base64 = base64(out_data, out_size, &ascii_base64_len);
        std::string result_data(ascii_base64, ascii_base64_len);

        LOG(INFO) << "EncryptAES: " << data << " # " << result_data;

        delete ascii_base64;
        delete[] buffer;
        delete[] in_data;
        delete[] out_data;

        return result_data;
    }

    //AES解密
    std::string OpenSSLUtility::DecryptAES(const std::string &data, const std::string &key)
    {
        AES_KEY aes_key;
        int key_size = key.size();
        if (AES_set_decrypt_key((const unsigned char*)key.c_str(), key_size * 8, &aes_key) < 0)
        {
            LOG(FATAL) << "AES decrypt key creation failed！ ";
        }

        //unbase64
        int binary_base64_len;
        unsigned char*binary_base64 = unbase64((const char *)data.c_str(), data.size(), &binary_base64_len);
        //Decrypt
        unsigned char*out_data = new unsigned char[binary_base64_len];
        int index = 0;
        unsigned char*buffer = new unsigned char[key_size];
        while (index < binary_base64_len)
        {
            AES_cbc_encrypt(binary_base64 + index, out_data + index, key_size, &aes_key, buffer, AES_DECRYPT);
            index += key_size;
        }
        int out_size = CharPointer2Int((const char *)out_data);
        std::string result_data = std::string((const char *)(out_data + 4));

        LOG(INFO) << "DecryptAES: " << data << " # " << result_data;

        delete binary_base64;
        delete[] buffer;
        delete[] out_data;

        return result_data;
    }

    std::string OpenSSLUtility::Md5(const std::string &data)
    {
        unsigned char*md5_data = new unsigned char[16];
        MD5((const unsigned char*)data.c_str(), data.size(), md5_data);
        int ascii_base64_len;
        char *ascii_base64 = base64(md5_data, 16, &ascii_base64_len);
        std::string result_data(ascii_base64, ascii_base64_len);
        delete ascii_base64;
        delete[] md5_data;
        LOG(INFO) << "Md5: " << data << " # " << result_data;
        return result_data;
    }

}