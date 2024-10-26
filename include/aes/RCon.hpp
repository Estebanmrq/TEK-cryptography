/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** RCon
*/

#ifndef RCON_HPP_
    #define RCON_HPP_
    #include <vector>
    #include <string>
    #include <exception>

namespace Cryptography {

    namespace AES {
        /**
         * @brief tatic class that represents the RCon
         * 
         */
        class RCon {
            public:
                /**
                 * @brief Get the values of the RCon at a given index
                 * 
                 * @param ind The index
                 * @return unsigned char The value of the RCon at the given index
                 */
                static unsigned char get(unsigned char ind);

                /**
                 * @brief The exception class for the RCon
                 * 
                 */
                class RConError : public std::exception {
                    public:
                        /**
                         * @brief Construct a new RConError object
                         * 
                         * @param message The message of the exception
                         */
                        RConError(std::string const &message) : _message("RCon Error: " + message) {};
                        /**
                         * @brief Destroy the RConError object
                         * 
                         */
                        ~RConError() noexcept override = default;
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
                 * @brief The values of the RCon
                 * 
                 */
                static const std::vector<unsigned char> _RConValues;
        };
    }

}

#endif /* !RCON_HPP_ */
