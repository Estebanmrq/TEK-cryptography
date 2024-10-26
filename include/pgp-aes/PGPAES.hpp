/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** PGPAES
*/

#ifndef PGPAES_HPP_
    #define PGPAES_HPP_
    #include <tuple>
    #include "AES.hpp"
    #include "RSA.hpp"

namespace Cryptography {

    namespace PGPAES {

        class PGPAES {
            public:

                /**
                 * @brief Construct a new PGP-AES object
                 * 
                 * @param aeskey The key used to encrypt and decrypt the messages
                 */
                PGPAES(std::string const &aeskey = "00000000000000000000000000000000") : _aes(aeskey) {};

                /**
                 * @brief Destroy the PGP-AES object
                 * 
                 */
                ~PGPAES() = default;

                /**
                 * @brief Encrypt a message using the AES & RSA algorithm
                 * 
                 * @param message The message to encrypt
                 * @return std::string The encrypted message in hexadecimal in little endian
                 */
                std::tuple<std::string, std::string> encrypt(std::string const &message);

                /**
                 * @brief Decrypt a message using the AES & RSA algorithm
                 * 
                 * @param message The message to decrypt
                 * @return std::string The decrypted message
                 */
                std::string decrypt(std::string const &message, std::string const &aeskey);

                /**
                 * @brief Constructor for the RSA object
                 * 
                 */
                RSA::RSA rsa;
            private:

                /**
                 * @brief Constructor for the AES object
                 * 
                 */
                AES::AES _aes;
        };

    }

}

#endif /* !PGPAES_HPP_ */
