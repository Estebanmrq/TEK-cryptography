/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** SBox
*/

#ifndef SBOX_HPP_
    #define SBOX_HPP_
    #include <vector>
    #include <string>
    #include <exception>

namespace Cryptography {

    namespace AES {
        /**
         * @brief Static class that represents the SBox
         * 
         */
        class SBox {
            public:
                /**
                 * @brief Get the value of the SBox at the given index
                 * 
                 * @param ind The index
                 * @return unsigned char The value of the SBox at the given index
                 */
                static unsigned char get(unsigned char ind);

                /**
                 * @brief Get the inverse value of the SBox at the given index
                 * 
                 * @param ind The index
                 * @return unsigned char The inverse value of the SBox at the given index
                 */
                static unsigned char getInv(unsigned char ind);




                /**
                 * @brief The exception class for the SBox
                 * 
                 */
                class SBoxError : public std::exception {
                    public:
                        /**
                         * @brief Construct a new SBoxError object
                         * 
                         * @param message The message of the exception
                         */
                        SBoxError(std::string const &message) : _message("SBox Error: " + message) {};
                        /**
                         * @brief Destroy the SBoxError object
                         * 
                         */
                        ~SBoxError() noexcept override = default;
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
                 * @brief The SBox values
                 * 
                 */
                static const std::vector<unsigned char> _SBoxValues;
        };
    }

}

#endif /* !SBOX_HPP_ */
