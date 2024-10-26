/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** AES
*/

#ifndef AES_HPP_
    #define AES_HPP_
    #include "Key.hpp"

namespace Cryptography {

    /**
     * @brief The AES namespace contains the AES class which is used to encrypt and decrypt messages using the AES algorithm
     * 
     */
    namespace AES {

        class AES {
            private:
                /**
                 * @brief The nb word in a block, 4 words of 4 bytes
                 * 
                 */
                static const int SIZE_KEY = 4;
            public:
                /**
                 * @brief Construct a new AES object
                 * 
                 * @param key The key used to encrypt and decrypt the messages
                 */
                AES(std::string const &key) : _okey(key), _key(key) {_key.reverseLittleEndian(); _keys = keyExpension(_key, 11);};

                /**
                 * @brief Destroy the AES object
                 * 
                 */
                ~AES() = default;


                std::string const &getOkey() const { return _okey; };

                /**
                 * 
                 * @brief Get the Key object
                 * 
                 * @return Key<SIZE_KEY> The key used to encrypt and decrypt the messages
                 */
                Key<SIZE_KEY> getKey() const { return _key; };

                /**
                 * @brief Encrypt a message using the AES algorithm
                 * 
                 * @param message The message to encrypt
                 * @return std::string The encrypted message in hexadecimal in little endian
                 */
                std::string encrypt(std::string const &message);

                /**
                 * @brief Decrypt a message using the AES algorithm
                 * 
                 * @param message The message to decrypt
                 * @return std::string The decrypted message
                 */
                std::string decrypt(std::string const &message);



                /**
                 * @brief AESException is an exception class used to throw exceptions in the AES class
                 * 
                 */
                class AESException : public std::exception {
                    public:
                        /**
                         * @brief Construct a new AESException object
                         * 
                         * @param message The message to display when the exception is thrown
                         */
                        AESException(std::string const &message) : _message("AES Error: " + message) {};
                        /**
                         * @brief Get the message of the exception
                         * 
                         * @return const char* The message of the exception
                         */
                        const char *what() const noexcept override { return _message.c_str(); };
                    private:
                        /**
                         * @brief The message of the exception
                         * 
                         */
                        std::string _message;
                };
            private:
                /**
                 * @brief The original key
                 * 
                 */
                std::string const _okey;

                /**
                 * @brief The key used in the aes algorithm
                 * 
                 */
                Key<SIZE_KEY> _key;

                /**
                 * @brief The key expanded used in the aes algorithm
                 * 
                 */
                std::vector<Key<SIZE_KEY>> _keys;
        };

    }

}

#endif /* !AES_HPP_ */
