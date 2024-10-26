/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** RSAKey
*/

#ifndef RSAKEY_HPP_
    #define RSAKEY_HPP_
    #include <string>
    #include <gmpxx.h>

namespace Cryptography {

    namespace RSA {

        /**
         * @brief The RSAKey class is used to store the public and private key of the RSA algorithm
         * 
         */
        class RSAKey {
            public:
                /**
                 * @brief Construct a new RSAKey object empty
                 * 
                 */
                RSAKey() {};

                /**
                 * @brief Destroy the RSAKey object
                 * 
                 */
                ~RSAKey() = default;


                /**
                 * @brief Load the key from a string
                 * 
                 * @param key The key to load
                 */
                void load(std::string const &key);

                /**
                 * @brief Load the key from `f` (wich is the `e` or `d` value, depend if you store a private or public key) and n
                 * 
                 * @param f The `e` or `d` value
                 * @param n The n value
                 */
                void load(mpz_class const &f, mpz_class const &n);



                /**
                 * @brief Get the `f` value
                 * 
                 * @return const mpz_class& The `f` value 
                 */
                const mpz_class &getF() const { return _f; };

                /**
                 * @brief Get the `n` value
                 * 
                 * @return const mpz_class& The `n` value
                 */
                const mpz_class &getN() const { return _n; };

                /**
                 * @brief Get the key as a string
                 * 
                 * @return const std::string& The key as a string
                 */
                const std::string &getKey() const { return _key; };



                /**
                 * @brief Static function to convert a hexa string from little endian to big endian
                 * 
                 * @param hexa The hexa string to convert
                 * @return std::string The converted hexa string
                 */
                static std::string hexaBigEndianToLittleEndian(const std::string &hexa);
    


                /**
                 * @brief Exception class for RSAKey
                 * 
                 */
                class RSAKeyException : public std::exception {
                    public:
                        /**
                         * @brief Construct a new RSAKeyException object
                         * 
                         * @param message The message to display
                         */
                        RSAKeyException(std::string const &message) : _message("RSAKey Error: " + message) {};
                        /**
                         * @brief The message to display
                         * 
                         * @return const char* The message to display
                         */
                        const char *what() const noexcept override { return _message.c_str(); };
                    private:
                        /**
                         * @brief The message to display
                         * 
                         */
                        std::string _message;
                };
            private:
                /**
                 * @brief The `f` value
                 * 
                 */
                mpz_class _f;
    
                /**
                 * @brief The `n` value
                 * 
                 */
                mpz_class _n;

                /**
                 * @brief The key as a string
                 * 
                 */
                std::string _key;
                
        };

    }

}

#endif /* !RSAKEY_HPP_ */
