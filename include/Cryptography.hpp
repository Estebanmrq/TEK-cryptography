/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** Cryptography
*/

#ifndef CRIPTOGRAPHY_HPP_
    #define CRIPTOGRAPHY_HPP_
    #include <map>
    #include <string>
    #include <vector>
    #include <functional>

/**
 * @brief The Cryptography namespace contains all classes and functions to handle cryptography methods
 * 
 */
namespace Cryptography {

    /**
     * @brief The Cryptography class is used to handle all cryptography methods and is the root class of the program
     * 
     */
    class Cryptography {
        public:
            /**
             * @brief The success return code
             * 
             */
            static const int EXIT_SUCCESS_CODE = 0;

            /**
             * @brief The failure return code
             * 
             */
            static const int EXIT_FAILURE_CODE = 84;
        public:
            /**
             * @brief Construct a new Cryptography object
             * 
             * @param args The args pass to the program
             */
            Cryptography(std::vector<std::string> args) : _args(args) {};
    
            /**
             * @brief Construct a new Cryptography object
             * 
             * @param args The args pass to the program
             * @param input The input to crypt
             */
            Cryptography(std::vector<std::string> args, std::string const &input) : _args(args), _input(input) {};

            /**
             * @brief Destroy the Cryptography object
             * 
             */
            ~Cryptography() = default;


            /**
             * @brief Run the program
             * 
             */
            void run();

            /**
             * @brief Display the help
             * 
             */
            void help();


            /**
             * @brief Exception class for Cryptography
             * 
             */
            class CriptographyException : public std::exception {
                public:
                    /**
                     * @brief Construct a new Criptography Exception object
                     * 
                     * @param message The message to display
                     */
                    CriptographyException(std::string const &message) : _message("Cryptography Error: " + message) {};
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
             * @brief Set the flags pass to the program
             * 
             */
            void _setFlags();

            /**
             * @brief Set the input of the program
             * 
             */
            void _setInput();


            /**
             * @brief The XOR method
             * 
             */
            void _xor();

            /**
             * @brief The AES method
             * 
             */
            void _aes();

            /**
             * @brief The RSA method
             * 
             */
            void _rsa();

            /**
             * @brief The PGP_AES method
             * 
             */
            void _pgp_aes();

            /**
             * @brief The PGP_XOR method
             * 
             */
            void _pgp_xor();


            /**
             * 
             * @brief All the cryptography methods and their flags
             * 
             */
            const std::map<std::string, std::function<void()>> CRYPTO_METHODS = {
                {"xor", [this]() {_xor();}},
                {"aes", [this]() {_aes();}},
                {"rsa", [this]() {_rsa();}},
                {"pgp-xor", [this]() {_pgp_xor();}},
                {"pgp-aes", [this]() {_pgp_aes();}},
            };

            /**
             * @brief The help file path
             * 
             */
            const std::string HELP_FILE_PATH = "docs/help.txt";

            /**
             * @brief The args pass to the program
             * 
             */
            std::vector<std::string> _args;

            /**
             * @brief The input of the program
             * 
             */
            std::string _input;

            /**
             * @brief The flags pass to the program
             * 
             */
            std::vector<std::string> _flags;
    };

}

#endif /* !CRIPTOGRAPHY_HPP_ */
