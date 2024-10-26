/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** RSA
*/

#ifndef RSA_HPP_
    #define RSA_HPP_
    #include <string>
    #include <vector>
    #include <gmpxx.h>
    #include <exception>
    #include "RSAKey.hpp"

    /**
     * @brief The Euleur indicator is used to calculate the encryption exponent
     * 
     */
    #define EULEUR_INDICATOR(p, q) ((p - 1) * (q - 1))

namespace Cryptography {

    /**
     * @brief The RSA namespace contains all classes and functions related to RSA encryption
     * 
     */
    namespace RSA {

        /**
         * @brief RSA class to handle RSA encryption and decryption and key generation
         * 
         */
        class RSA {
            public:
                /**
                 * @brief Construct a new RSA object
                 * 
                 */
                RSA() {};

                /**
                 * @brief Destroy the RSA object
                 * 
                 */
                ~RSA() = default;


                /**
                 * @brief Generate RSA keys
                 * 
                 * @param p The first prime number in hexa decimal, and little endian
                 * @param q The second prime number in hexa decimal, and little endian
                 */
                void generateKeys(std::string const &p, std::string const &q);

                /**
                 * @brief Encrypt a message
                 * 
                 * @param message The message to encrypt
                 * @return std::string The encrypted message in hexa decimal, and little endian
                 */
                std::string encrypt(std::string const &message, bool isHexa = false);

                /**
                 * @brief Decrypt a message
                 * 
                 * @param message The message to decrypt in hexa decimal, and little endian
                 * @return std::string The decrypted message
                 */
                std::string decrypt(std::string const &message);

                /**
                 * @brief Get the hexa decimal value of a message character
                 * 
                 * @param message The message character
                 * @return std::string The hexa decimal value of the message character
                 */
                static std::string messageToHexa(std::string const &message);

                /**
                 * @brief Get the message character from a hexa decimal value
                 * 
                 * @param message The hexa decimal value
                 * @return std::string The message character
                 */
                static std::string hexaToMessage(std::string const &message);

                /**
                 * @brief The public key
                 * 
                 */
                RSAKey publicKey;

                /**
                 * @brief The private key
                 * 
                 */
                RSAKey privateKey;


                /**
                 * @brief RSA Exception class
                 * 
                 */
                class RSAException : public std::exception {
                    public:
                        /**
                         * @brief Construct a new RSAException object
                         * 
                         * @param message The message to display
                         */
                        RSAException(std::string const &message) : _message("AES Error: " + message) {};
                        /**
                         * @brief Get the exception message
                         * 
                         * @return const char* The exception message
                         */
                        const char *what() const noexcept override { return _message.c_str(); };
                    private:
                        /**
                         * @brief The exception message
                         * 
                         */
                        std::string _message;
                };
            private:
                /**
                 * @brief A list of Fermat values
                 * 
                 */
                std::vector<mpz_class> FERMAT_VALUES = {3, 5, 17, 257, 65537};


                /**
                 * @brief Get the `plus grand commun diviseur` of two numbers
                 * 
                 * @param a The first number
                 * @param m The second number
                 * @param x The x result
                 * @param y The y result
                 * @return mpz_class The `plus grand commun diviseur` of the two numbers
                 */
                mpz_class _pgcd(mpz_class a, mpz_class m, mpz_class &x, mpz_class &y) const;

                /**
                 * @brief Get the encryption exponent
                 * 
                 * @param euleurInd The Euleur indicator
                 * @return mpz_class The encryption exponent
                 */
                mpz_class _encryptionExponent(mpz_class euleurInd) const;

                /**
                 * @brief Get the inversed modulo
                 * 
                 * @param a The first value
                 * @param m The second value
                 * @return mpz_class The inversed modulp
                 */
                mpz_class _modInverse(mpz_class a, mpz_class m) const;
        };

    }

}

#endif /* !RSA_HPP_ */
