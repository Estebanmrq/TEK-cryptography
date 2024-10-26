/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** PGPXOR
*/

#ifndef PGPXOR_HPP_
    #define PGPXOR_HPP_
    #include <tuple>
    #include "XOR.hpp"
    #include "RSA.hpp"

namespace Cryptography {

    namespace PGPXOR {

        class PGPXOR {
            public:

                /**
                 * @brief Construct a new PGP-XOR object
                 * 
                 * @param aeskey The key used to encrypt and decrypt the messages
                 */
                PGPXOR(std::string const &xorkey = "00") : _xor(xorkey) {};

                /**
                 * @brief Destroy the PGP-XOR object
                 * 
                 */
                ~PGPXOR() = default;

                /**
                 * @brief Encrypt a message using the XOR & RSA algorithm
                 * 
                 * @param message The message to encrypt
                 * @return std::string The encrypted message in hexadecimal in little endian
                 */
                std::tuple<std::string, std::string> encrypt(std::string const &message);

                /**
                 * @brief Decrypt a message using the XOR & RSA algorithm
                 * 
                 * @param message The message to decrypt
                 * @return std::string The decrypted message
                 */
                std::string decrypt(std::string const &message, std::string const &xorkey);

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
                XOR _xor;
        };

    }

}

#endif /* !PGPXOR_HPP_ */
